
#include "class_loadrer/class_loader.h"

#include "fstream"
#include "format"
#include "vm/resolver.h"
#include "bytecode/interpreter.h"
#include "bytecode/native.h"

BootstrapClassLoader::BootstrapClassLoader() {
    m_heap = Heap::getInstance();
}


JClass BootstrapClassLoader::loadClass(const std::string& classPath) {
    ClassFile *classFile = new ClassFile;
    if (m_jarFile != NULL) {
        struct zip_stat stat{};
        zip_stat(m_jarFile, classPath.data(), ZIP_FL_UNCHANGED, &stat);
        auto *file = zip_fopen(m_jarFile, classPath.data(),ZIP_FL_UNCHANGED);
        if (file == NULL) {
            std::cerr << std::format("Class not found: {}\n", classPath) ;
            exit(1);
        }
        ClassFileStream clStream(file,stat.size);
        ClassFileParser classFileParser(clStream);
        classFileParser.parseClassFile(*classFile);
    } else {
        std::ifstream file(classPath);
        if (!file.is_open()) {
            std::cerr << std::format("Class not found: {}\n", classPath) ;
            exit(1);
        }
        ClassFileStream clStream(file);
        ClassFileParser classFileParser(clStream);
        classFileParser.parseClassFile(*classFile);
    }




    JClass jClass(*classFile);


    //todo write resolver for symbolic links
//    auto &clInfo = classFile->getConstant<ClassInfoConst>(classFile->thisClass);
    ConstPoolList &constPool = classFile->constantPool;
    auto &clInfo = Resolver::getConstant<ClassInfoConst>(constPool, classFile->thisClass);
    auto &jClassName = Resolver::resolveNameIndex(clInfo, constPool);
    auto &superClass = Resolver::getConstant<ClassInfoConst>(constPool, classFile->superClass);
    auto &parent = Resolver::resolveNameIndex(superClass, constPool);
    auto &declaredVars = jClass.getDeclaredFields();
    jClass.setParent(parent);
    for (int i = 0; i < classFile->fieldsCount; ++i) {
        auto &field = classFile->fields[i];

        auto &fieldName = Resolver::resolveNameIndex(field, constPool);
        auto &descriptor = Resolver::resolveDescriptor(field, constPool);
        std::string fieldDescriptor = std::format("{}:{}", fieldName, descriptor);
        JavaValue javaValue = JavaValue::createByType(static_cast<JAVA_DATA_TYPE>(*descriptor.data()));
        JField jField;
        jField.value = javaValue;
        jField.isStatic = field.accessFlags & FIELD_ACC_FLAGS::ACC_STATIC;
        jField.name = fieldDescriptor;
        declaredVars[fieldDescriptor] = jField;//TODO handle refs and arrays
        //            std::cout << fieldDescriptor << "\n";
    }

    for (int i = 0; i < classFile->methodsCount; ++i) {
        MethodInfo &methodInfo = classFile->methods[i];
        auto &methodName = Resolver::resolveNameIndex(methodInfo, constPool);
        auto &descriptor = Resolver::resolveDescriptor(methodInfo, constPool);

        std::string methodFullName = std::format("{}.{}:{}", jClassName, methodName, descriptor);
        for (int j = 0; j < methodInfo.attributesCount; ++j) {
            auto &attr = *methodInfo.attributes[j];
            ATTRIBUTE_TYPE attributeType = Resolver::resolveAttrType(constPool,attr.attributeNameIndex);

            if (attributeType == ATTRIBUTE_TYPE::CODE_AT) {
                auto &code = Resolver::getAttribute<CodeAttribute>(methodInfo.attributes,j);
                MethodData methodData = {.codeAttribute = code, .isNative = static_cast<bool>((methodInfo.accessFlags & 0x0100))};
                methodData.argCount = Resolver::getArgCount(descriptor);
                methodData.name = methodName;
                methodData.descriptor = descriptor;
                methodData.className = jClassName;
                loadMethodLocals(methodData,constPool);
                m_heap->getMethodArea().methodMap.insert({methodFullName, methodData});
            }
        }
//        std::cout << "method name " << methodFullName <<"\n";
    }

    m_heap->getJClassTable().insert({jClassName, jClass});

    Interpreter::execClInit(jClass);

    return jClass;
}

void BootstrapClassLoader::loadInternalClasses(JAVA_DATA_TYPE javaDataType, std::string name) {
    ClassFile emptyCl;
    JClass jClass(true, emptyCl, name);
    JavaValue javaValue = JavaValue::createByType(javaDataType);
    jClass.setInternalType(javaValue);
    m_heap->getJClassTable().insert({name, jClass});
}

//todo this is really bad delete later
void BootstrapClassLoader::loadNative() {
    ClassFile emptyCl;
    for (auto &it : nativeClasFields) {

        std::string clName = it.first;
        JClass jClass(true, emptyCl, clName);
        for (auto &fieldName : it.second) {
//            std::string fieldDescriptor = std::format("{}.{}" , clName, fieldName);
            JavaValue javaValue = JavaValue::createByType(JAVA_DATA_TYPE::CHAR_JDT);
            auto &staticVars = jClass.getDeclaredFields();
            JField jField;
            jField.name = fieldName;
            jField.value = javaValue;
            staticVars[fieldName] = jField;
        }
        m_heap->getJClassTable().insert({clName, jClass});
    }

    //todo add all primitive types
    CodeAttribute emptyCode;
    for (auto &it : nativeClasMethods) {
        std::string clName = it.first;
        for (auto &methodName : it.second) {
            std::string methodFullName = std::format("{}.{}", clName, methodName);

            MethodData methodData = {.codeAttribute = emptyCode, .isNative = true};
            m_heap->getMethodArea().methodMap.insert({methodFullName, methodData});
        }
    }
}

void BootstrapClassLoader::setJarFile(zip *jarFile) {
    m_jarFile = jarFile;
}

void BootstrapClassLoader::loadMethodLocals(MethodData &methodData, ConstPoolList &constPool) {
    AttributesList &attributesList = methodData.codeAttribute.attributes;
    for (int i = 0; i < methodData.codeAttribute.attributesCount; ++i) {
        if (attributesList[i]->attributeType == ATTRIBUTE_TYPE::LocalVariableTable_AT) {
            auto &localVars = Resolver::getAttribute<LocalVariableTableAttribute>(attributesList,i);
            methodData.localVarsType = std::vector<JAVA_DATA_TYPE>(methodData.codeAttribute.maxLocals);
            for (auto &entry: localVars.localVariableTable) {
                std::string &descriptor = Resolver::resovleUTF8str(constPool, entry.descriptorIndex);
                methodData.localVarsType[entry.index] = static_cast<JAVA_DATA_TYPE>(descriptor.at(0));
            }
        }
    }
}



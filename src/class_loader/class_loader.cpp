
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
    loadMethods(classFile,jClassName);

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

    CodeAttribute emptyCode;
    for (auto &it : nativeClasMethods) {
        std::string clName = it.first;
        for (auto &methodName : it.second) {
            std::string methodFullName = std::format("{}.{}", clName, methodName);

            MethodData methodData = {.codeAttribute = &emptyCode, .isNative = true};
            methodData.className = clName;
            methodData.name = methodName;
            m_heap->getMethodArea().methodMap.insert({methodFullName, methodData});
        }
    }
}

void BootstrapClassLoader::setJarFile(zip *jarFile) {
    m_jarFile = jarFile;
}

void BootstrapClassLoader::loadMethodLocals(MethodData &methodData, ConstPoolList &constPool) {
    AttributesList &attributesList = methodData.codeAttribute->attributes;
    if (methodData.isNative) {
        methodData.localVarsType = Resolver::parseMethodArgTypes(methodData.descriptor);
        return;
    }
    for (int i = 0; i < methodData.codeAttribute->attributesCount; ++i) {
        if (attributesList[i]->attributeType == ATTRIBUTE_TYPE::LocalVariableTable_AT) {
            auto &localVars = Resolver::getAttribute<LocalVariableTableAttribute>(attributesList,i);
            methodData.localVarsType = std::vector<JAVA_DATA_TYPE>(methodData.codeAttribute->maxLocals);
            for (auto &entry: localVars.localVariableTable) {
                std::string &descriptor = Resolver::resovleUTF8str(constPool, entry.descriptorIndex);
                methodData.localVarsType[entry.index] = static_cast<JAVA_DATA_TYPE>(descriptor.at(0));
            }
        }
    }
}

void BootstrapClassLoader::loadMethodAnnotations(MethodData &methodData, ClassFile &classFile, MethodInfo &methodInfo) {
    RuntimeVisibleAnnotationsAttribute annotationsAttribute;
    bool isFind = false;

    for (int i = 0; i < methodInfo.attributesCount; ++i) {
        if (methodInfo.attributes[i]->attributeType == ATTRIBUTE_TYPE::RUNTIME_VISIBLE_ANNOTATIONS_AT) {
            isFind = true;
            annotationsAttribute = Resolver::getAttribute<RuntimeVisibleAnnotationsAttribute>(methodInfo.attributes,i);
        }
    }

    if (!isFind) {
        return;
    }

    for (int i = 0; i < annotationsAttribute.numAnnotations; ++i) {
        Annotation annotation = annotationsAttribute.annotations[i];
        JAnnotation jAnnotation = loadAnnotation(annotation, classFile);
        methodData.annotations.emplace_back(jAnnotation);
    }
}

JAnnotation BootstrapClassLoader::loadAnnotation(Annotation &annotation, ClassFile &classFile) {
    JAnnotation jAnnotation;
    std::string className = Resolver::resovleUTF8str(classFile.constantPool, annotation.typeIndex);
    std::erase(className,'L');
    std::erase(className,';');
//    JClass &jClass = RuntimeArea::getInstance()->getClass(className);
    std::string simpleName;
    uint64_t pos = className.find_last_of('/');
    if (pos == std::string::npos) {
        simpleName = className;
    } else {
        simpleName = className.substr(pos + 1);
    }
    jAnnotation.name = className;
    jAnnotation.simpleName = simpleName;
//    jAnnotation.jClass = &jClass;
    jAnnotation.jClass = nullptr;
    for (int i = 0; i < annotation.numElementValuePairs; ++i) {
        JavaValue javaValue = Resolver::resolveElementValue(annotation.elementValuePairs[i], classFile);
        std::string paramName = Resolver::resovleUTF8str(classFile.constantPool, annotation.elementValuePairs[i].elementNameIndex);
        jAnnotation.params[paramName] = javaValue;
    }
    return jAnnotation;
}

void BootstrapClassLoader::loadMethods(ClassFile *classFile, std::string &jClassName) {
    ConstPoolList &constPool = classFile->constantPool;
    for (int i = 0; i < classFile->methodsCount; ++i) {
        MethodInfo &methodInfo = classFile->methods[i];
        auto &methodName = Resolver::resolveNameIndex(methodInfo, constPool);
        auto &descriptor = Resolver::resolveDescriptor(methodInfo, constPool);

        std::string methodFullName = std::format("{}.{}:{}", jClassName, methodName, descriptor);
        bool isNative = methodInfo.accessFlags & 0x0100;
        MethodData methodData = {.codeAttribute = nullptr, .isNative = isNative};
        methodData.isStatic = methodInfo.accessFlags & 0x0008;
        if (methodData.isNative && !methodData.isStatic) {
            std::cerr << "METHOD " << methodFullName << "MUST BE STATIC" << "\n";
            exit(-1);
        }
        for (int j = 0; j < methodInfo.attributesCount; ++j) {
            auto &attr = *methodInfo.attributes[j];
            ATTRIBUTE_TYPE attributeType = Resolver::resolveAttrType(constPool,attr.attributeNameIndex);

            if (attributeType == ATTRIBUTE_TYPE::CODE_AT) {
                auto &code = Resolver::getAttribute<CodeAttribute>(methodInfo.attributes,j);
                methodData.codeAttribute = &code;
            }
        }

        methodData.argCount = Resolver::getArgCount(descriptor);
        methodData.name = methodName;
        methodData.descriptor = descriptor;
        methodData.className = jClassName;
        //todo enum for acc flags of method

        methodData.isNative = methodInfo.accessFlags & 0x0100;
        methodData.returnType = Resolver::parseMethodReturn(descriptor);
        loadMethodAnnotations(methodData, *classFile, methodInfo);
        loadMethodLocals(methodData,constPool);
        if (!methodData.isStatic) {
            methodData.argCount++;
        }
        m_heap->getMethodArea().methodMap.insert({methodFullName, methodData});
//        std::cout << "method name " << methodFullName <<"\n";
    }
}







#include "class_loadrer/class_loader.h"

#include "fstream"
#include "format"
#include "vm/resolver.h"


BootstrapClassLoader::BootstrapClassLoader() {
    m_heap = Heap::getInstance();
}


JClass BootstrapClassLoader::loadClass(const std::string& classPath) {
    ClassFile *classFile = new ClassFile;
    std::ifstream file(classPath);
    if (!file.is_open()) {
        std::cerr << std::format("Class not found: {}\n", classPath) ;
        exit(1);
    }
    ClassFileStream clStream(file);
    ClassFileParser classFileParser(clStream);
    classFileParser.parseClassFile(*classFile);


    JClass jClass(*classFile);
    auto &staticVars = jClass.getStaticVars();

    //todo write resolver for symbolic links
//    auto &clInfo = classFile->getConstant<ClassInfoConst>(classFile->thisClass);
    ConstPoolList &constPool = classFile->constantPool;
    auto &clInfo = Resolver::getConstant<ClassInfoConst>(constPool, classFile->thisClass);
    auto &jClassName = Resolver::resolveNameIndex(clInfo, constPool);

    for (int i = 0; i < classFile->fieldsCount; ++i) {
        auto &field = classFile->fields[i];

        if (field.accessFlags & FIELD_ACC_FLAGS::ACC_STATIC) {
            auto &fieldName = Resolver::resolveNameIndex(field, constPool);
            auto &descriptor = Resolver::resolveDescriptor(field, constPool);

            std::string fieldDescriptor = std::format("{}.{}:{}",jClassName, fieldName, descriptor);
            JavaType type = JavaType::createByType(static_cast<JAVA_DATA_TYPE>(*descriptor.data()));
            staticVars[fieldDescriptor] = type;

            //TODO handle refs and arrays


            std::cout << fieldDescriptor << "\n";
        }
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
                MethodData methodData = {.codeAttribute = code};
                m_heap->getMethodArea().methodMap.insert({methodFullName, methodData});
            }
        }
        std::cout << "method name " << methodFullName <<"\n";
    }

    m_heap->getJClassTable().insert({jClassName, jClass});



    return jClass;
}



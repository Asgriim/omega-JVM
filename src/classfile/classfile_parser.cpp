#include "classfile/classfile_parser.h"

ClassFileParser::ClassFileParser(ClassFileStream &clStream) : m_clStream(clStream), m_attributeParser(clStream) {

}

void ClassFileParser::parseClassFile(ClassFile &classFile) {
    classFile.magic = m_clStream.readU4();
    classFile.minorVersion = m_clStream.readU2();
    classFile.majorVersion = m_clStream.readU2();
    classFile.constantPoolCount = m_clStream.readU2();

    parseConstPool(classFile);

    m_clStream >> classFile.accessFlags;
    m_clStream >> classFile.thisClass;
    m_clStream >> classFile.superClass;
    m_clStream >> classFile.interfacesCount;

    classFile.interfaces = std::make_unique<uint16_t[]>(classFile.interfacesCount);

    for (int i = 0; i < classFile.interfacesCount; ++i) {
        m_clStream >> classFile.interfaces[i];
    }

    m_clStream >> classFile.fieldsCount;

    classFile.fields = std::make_unique<FieldInfo[]>(classFile.fieldsCount);

    for (int i = 0; i < classFile.fieldsCount; ++i) {
        parseGenInfo(classFile, &classFile.fields[i]);
    }

    m_clStream >> classFile.methodsCount;

    classFile.methods = std::make_unique<MethodInfo[]>(classFile.methodsCount);

    for (int i = 0; i < classFile.methodsCount; ++i) {
        parseGenInfo(classFile, &classFile.methods[i]);
    }

    m_clStream >> classFile.attributesCount;
    classFile.attributes = AttributesList(classFile.attributesCount);
    m_attributeParser.parseAttributes(classFile,classFile.attributes,classFile.attributesCount);

}

void ClassFileParser::parseConstPool(ClassFile &classFile) {
    classFile.constantPool = ConstPoolList(classFile.constantPoolCount - 1);
    CONSTANT_POOL_TAG tag;
    for (int i = 0; i < classFile.constantPoolCount - 1; ++i) {
        tag = static_cast<CONSTANT_POOL_TAG>(m_clStream.readU1());
        switch (tag) {
            case CONSTANT_POOL_TAG::UTF8_CPT:
                readConstVal<Utf8InfoConst>(classFile.constantPool,i);
                break;
            case CONSTANT_POOL_TAG::INTEGER_CPT:
                readConstVal<IntegerConst>(classFile.constantPool,i);
                break;
            case CONSTANT_POOL_TAG::FLOAT_CPT:
                readConstVal<FloatConst>(classFile.constantPool,i);
                break;
            case CONSTANT_POOL_TAG::LONG_CPT:
                readConstVal<LongConst>(classFile.constantPool,i);
                break;
            case CONSTANT_POOL_TAG::DOUBLE_CPT:
                readConstVal<DoubleConst>(classFile.constantPool,i);
                break;
            case CONSTANT_POOL_TAG::CLASS_CPT:
                readConstVal<ClassInfoConst>(classFile.constantPool,i);
                break;
            case CONSTANT_POOL_TAG::STRING_CPT:
                readConstVal<StringInfoConst>(classFile.constantPool,i);
                break;
            case CONSTANT_POOL_TAG::FIELD_REF_CPT:
                readConstVal<FieldRefConst>(classFile.constantPool,i);
                break;
            case CONSTANT_POOL_TAG::METHOD_REF_CPT:
                readConstVal<MethodRefConst>(classFile.constantPool,i);
                break;
            case CONSTANT_POOL_TAG::INTERFACE_METHOD_REF_CPT:
                readConstVal<InterfaceMethRefConst>(classFile.constantPool,i);
                break;
            case CONSTANT_POOL_TAG::NAME_AND_TYPE_CPT:
                readConstVal<NameAndTypeConst>(classFile.constantPool,i);
                break;
            case CONSTANT_POOL_TAG::METHOD_HANDLE_CPT:
                readConstVal<MethodHandleConst>(classFile.constantPool,i);
                break;
            case CONSTANT_POOL_TAG::METHOD_TYPE_CPT:
                readConstVal<MethodTypeConst>(classFile.constantPool,i);
                break;
            case CONSTANT_POOL_TAG::DYNAMIC_CPT:
                readConstVal<DynamicConst>(classFile.constantPool,i);
                break;
            case CONSTANT_POOL_TAG::INVOKE_DYNAMIC_CPT:
                readConstVal<InvokeDynamicConst>(classFile.constantPool,i);
                break;
            case CONSTANT_POOL_TAG::MODULE_CPT:
                readConstVal<ModuleInfoConst>(classFile.constantPool,i);
                break;
            case CONSTANT_POOL_TAG::PACKAGE_CPT:
                readConstVal<PackageInfoConst>(classFile.constantPool,i);
                break;
        }
    }

}

void ClassFileParser::parseGenInfo(ClassFile &classFile, GeneralInfo *generalInfo) {
    m_clStream >> generalInfo->accessFlags;
    m_clStream >> generalInfo->nameIndex;
    m_clStream >> generalInfo->descriptorIndex;
    m_clStream >> generalInfo->attributesCount;
    generalInfo->attributes = AttributesList(generalInfo->attributesCount);
    m_attributeParser.parseAttributes(classFile, generalInfo->attributes, generalInfo->attributesCount);

}

#include "classfile/classfile_stream.h"

ClassFileStream::ClassFileStream(std::istream &is, int64_t buf_size) : m_is(is) {
    m_bufSize = buf_size;
    getFileLen();
}

ClassFileStream::ClassFileStream(zip_file *jarFile, uint64_t fileSize, int64_t buf_size) : m_is(std::cin) {
    m_jarFile = jarFile;
    m_bufSize = buf_size;
    m_endPos = fileSize - 1;
}


void ClassFileStream::allocBuf() {
    if (m_jarFile != NULL) {
        if (m_endPos - zip_ftell(m_jarFile) < m_bufSize) {
            m_bufSize = m_endPos - m_curPos;
        }
        m_buf = std::make_unique<char[]>(m_bufSize);
        zip_fread(m_jarFile, m_buf.get(), m_bufSize);
    } else {
        if (m_endPos - m_is.tellg() < m_bufSize) {
            m_bufSize = m_endPos - m_curPos;
        }
        m_buf = std::make_unique<char[]>(m_bufSize);
        m_is.read(m_buf.get(), m_bufSize);
    }

    m_curPos = 0;
}

void ClassFileStream::readBytes(uint8_t *target, size_t size) {
    for (int i = size - 1; i >= 0 ; i--) {
        target[i] = readU1();
    }
}

void ClassFileStream::readBytesLE(uint8_t *target, size_t size) {
    for (int i = 0; i < size; ++i) {
        target[i] = readU1();
    }

}

uint8_t ClassFileStream::readU1() {
    if (m_curPos >= m_bufSize || m_buf == nullptr) {
        allocBuf();
    }
    char out = m_buf[m_curPos];
    m_curPos++;
    return out;
}


uint16_t ClassFileStream::readU2() {
    uint16_t out = 0;
    readBytes((uint8_t*) &out, sizeof(out));
    return out;
}

uint32_t ClassFileStream::readU4() {
    uint32_t out = 0;
    readBytes((uint8_t*) &out, sizeof(out));
    return out;
}

uint64_t ClassFileStream::readU8() {
    uint64_t out = 0;
    readBytes((uint8_t*) &out, sizeof(out));
    return out;
}

bool ClassFileStream::isEOF() {
    return m_is.tellg() == m_endPos;
}

void ClassFileStream::getFileLen() {
    m_is.seekg(0, std::ios::end);
    m_endPos = m_is.tellg();
    m_is.seekg(0,std::ios::beg);
}

void ClassFileStream::readString(std::string &string, uint64_t len) {
//    auto *chars = new uint8_t[len + 1];
    for (int i = 0; i < len; ++i) {
//        chars[i] = readU1();
        string.push_back(readU1());
    }
//    chars[len + 1] = 0;

//    string.assign(reinterpret_cast<const char *>(chars));
}



//hope that not get memory leak
ClassFileStream &ClassFileStream::operator>>(Utf8InfoConst &info) {
    info.tag = CONSTANT_POOL_TAG::UTF8_CPT;
    info.length = readU2();
    readString(info.bytes,info.length);
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(ClassInfoConst &info) {
    info.tag = CONSTANT_POOL_TAG::CLASS_CPT;
    info.nameIndex = readU2();
    return *this;
}


ClassFileStream &ClassFileStream::operator>>(FieldRefConst &info) {
    info.tag = CONSTANT_POOL_TAG::FIELD_REF_CPT;
    info.classIndex = readU2();
    info.nameAndTypeIndex = readU2();
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(MethodRefConst &info) {
    info.tag = CONSTANT_POOL_TAG::METHOD_REF_CPT;
    info.classIndex = readU2();
    info.nameAndTypeIndex = readU2();
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(InterfaceMethRefConst &info) {
    info.tag = CONSTANT_POOL_TAG::INTERFACE_METHOD_REF_CPT;
    info.classIndex = readU2();
    info.nameAndTypeIndex = readU2();
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(StringInfoConst &info) {
    info.tag = CONSTANT_POOL_TAG::STRING_CPT;
    info.stringInd = readU2();
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(IntegerConst &info) {
    info.tag = CONSTANT_POOL_TAG::INTEGER_CPT;
    info.bytes = readU4();
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(FloatConst &info) {
    info.tag = CONSTANT_POOL_TAG::FLOAT_CPT;
    info.bytes = readU4();
    return *this;
}


//todo потестить
ClassFileStream &ClassFileStream::operator>>(LongConst &info) {
    info.tag = CONSTANT_POOL_TAG::LONG_CPT;
    info.highBytes = readU4();
    info.lowBytes = readU4();
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(DoubleConst &info) {
    info.tag = CONSTANT_POOL_TAG::DOUBLE_CPT;
    info.highBytes = readU4();
    info.lowBytes = readU4();
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(NameAndTypeConst &info) {
    info.tag = CONSTANT_POOL_TAG::NAME_AND_TYPE_CPT;
    info.nameIndex = readU2();
    info.descriptorIndex = readU2();
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(MethodHandleConst &info) {
    info.tag = CONSTANT_POOL_TAG::METHOD_HANDLE_CPT;
    info.referenceKind = readU1();
    info.referenceInd = readU2();
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(MethodTypeConst &info) {
    info.tag = CONSTANT_POOL_TAG::METHOD_TYPE_CPT;
    info.descriptorInd = readU2();
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(DynamicConst &info) {
    info.tag = CONSTANT_POOL_TAG::DYNAMIC_CPT;
    info.bootstrapMethodAttrInd = readU2();
    info.nameAndTypeIndex = readU2();
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(InvokeDynamicConst &info) {
    info.tag = CONSTANT_POOL_TAG::INVOKE_DYNAMIC_CPT;
    info.bootstrapMethodAttrInd = readU2();
    info.nameAndTypeIndex = readU2();
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(ModuleInfoConst &info) {
    info.tag = CONSTANT_POOL_TAG::MODULE_CPT;
    info.nameIndex = readU2();
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(PackageInfoConst &info) {
    info.tag = CONSTANT_POOL_TAG::PACKAGE_CPT;
    info.nameIndex = readU2();
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(uint8_t &uint) {
    uint = readU1();
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(uint16_t &uint) {
    uint = readU2();
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(uint32_t &uint) {
    uint = readU4();
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(uint64_t &uint) {
    uint = readU8();
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(BootstrapMethodsAttribute &attribute) {
    attribute.attributeType = BOOTSTRAP_METHODS_AT;
    attribute.numBootstrapMethods = readU2();
    attribute.bootstrapMethods = std::vector<BootstrapMethodEntry>(attribute.numBootstrapMethods);
    for (int i = 0; i < attribute.numBootstrapMethods; ++i) {
        BootstrapMethodEntry &entry = attribute.bootstrapMethods[i];
        entry.bootstrapMethodRef = readU2();
        entry.numBootstrapArguments =  readU2();
        entry.bootstrapArguments = std::make_unique<uint16_t[]>(entry.numBootstrapArguments);
        for (int j = 0; j < entry.numBootstrapArguments; ++j) {
            entry.bootstrapArguments[i] = readU2();
        }
    }
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(UnknownAttr &attribute) {
    attribute.attributeType = UNKNOWN_AT;
    attribute.info = std::make_unique<uint8_t[]>(attribute.attributeLength);
    readBytes(attribute.info.get(),attribute.attributeLength);
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(CodeAttribute &attribute) {
    attribute.attributeType = CODE_AT;
    attribute.maxStack = readU2();
    attribute.maxLocals = readU2();
    attribute.codeLength = readU4();
    attribute.code = std::make_unique<uint8_t[]>(attribute.codeLength);
    readBytesLE(attribute.code.get(), attribute.codeLength);
    attribute.exceptionTableLength = readU2();
    attribute.exceptionTable = std::vector<ExceptionTableEntry>(attribute.exceptionTableLength);
    for (int i = 0; i < attribute.exceptionTableLength; ++i) {
        ExceptionTableEntry &entry = attribute.exceptionTable[i];
        entry.startPc = readU2();
        entry.endPc = readU2();
        entry.handlerPc = readU2();
        entry.catchType = readU2();
    }

    attribute.attributesCount = readU2();
    attribute.attributes = AttributesList(attribute.attributesCount);

    return *this;
}

ClassFileStream &ClassFileStream::operator>>(LocalVariableTableAttribute &attribute) {
    attribute.localVariableTableLength = readU2();
    attribute.attributeType = LocalVariableTable_AT;
    for (int i = 0; i < attribute.localVariableTableLength; ++i) {
        LocalVariableEntry entry{};
        entry.startPc = readU2();
        entry.index = readU2();
        entry.nameIndex = readU2();
        entry.descriptorIndex = readU2();
        entry.index = readU2();
        attribute.localVariableTable.emplace_back(entry);
    }
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(RuntimeVisibleAnnotationsAttribute &attribute) {
    attribute.numAnnotations = readU2();
    attribute.attributeType = RUNTIME_VISIBLE_ANNOTATIONS_AT;
    for (int i = 0; i < attribute.numAnnotations; ++i) {
        Annotation annotation{};
        *this >> annotation;
        attribute.annotations.emplace_back(annotation);
    }
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(Annotation &annotation) {
    annotation.typeIndex = readU2();
    annotation.numElementValuePairs = readU2();
    for (int i = 0; i < annotation.numElementValuePairs; ++i) {
        ElementValuePair elementValuePair{};
        *this >> elementValuePair;
        annotation.elementValuePairs.emplace_back(elementValuePair);
    }
    return *this;
}

ClassFileStream &ClassFileStream::operator>>(ElementValuePair &valuePair) {
    valuePair.elementNameIndex = readU2();
    ElementValue elementValue{};
    elementValue.tag = readU1();
    Value *value;
    switch (elementValue.tag) {
        case 'e': {
            auto *constPtr = new EnumConstValue();
            constPtr->typeNameIndex = readU2();
            constPtr->constNameIndex = readU2();
            value = constPtr;
            break;
        }
        case 'c': {
            auto *constPtr = new ClassInfoValue();
            constPtr->classInfoIndex = readU2();
            value = constPtr;
            break;
        }
        case '[': {
            std::cerr << "ARRAYS NOT IMPLEMENTED IN ANNOTATIONS\n";
            exit(-1);
        }
        case '@': {
            std::cerr << "NESTESD ANNOTATIONS NOT IMPLEMENTED\n";
            exit(-1);
        }
        default: {
            auto *constPtr = new ConstValue();
            constPtr->constValueIndex = readU2();
            value = constPtr;
            break;
        }
    }
    elementValue.value = value;
    valuePair.value = elementValue;
    return *this;
}
















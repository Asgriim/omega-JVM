
#include "classfile.h"
#include "binary_io.h"

std::istream &operator>>(std::istream &is, ClassFile &classFile) {

    read_big_endian(is, (char*)&classFile.magic, sizeof(classFile.magic));
    read_big_endian(is, (char*)&classFile.minorVersion, sizeof(classFile.minorVersion));
    read_big_endian(is, (char*)&classFile.majorVersion, sizeof(classFile.majorVersion));
    read_big_endian(is, (char*)&classFile.constantPoolCount, sizeof(classFile.constantPoolCount));

    classFile.constantPool = std::make_unique<CpInfo[]>(classFile.constantPoolCount - 1);

    for (int i = 0; i < classFile.constantPoolCount - 1; ++i) {
        is >> classFile.constantPool[i];
    }

    read_big_endian(is, (char*)&classFile.accessFlags, sizeof(classFile.accessFlags));
    read_big_endian(is, (char*)&classFile.thisClass, sizeof(classFile.thisClass));
    read_big_endian(is, (char*)&classFile.superClass, sizeof(classFile.superClass));
    read_big_endian(is, (char*)&classFile.interfacesCount, sizeof(classFile.interfacesCount));

    classFile.interfaces = std::make_unique<uint16_t[]>(classFile.interfacesCount);

    read_big_endian(is, (char*)classFile.interfaces.get(), sizeof(uint16_t) * classFile.interfacesCount);
    read_big_endian(is, (char*)&classFile.fieldsCount, sizeof(classFile.fieldsCount));

    classFile.fields = std::make_unique<FieldInfo[]>(classFile.fieldsCount);
    for (int i = 0; i < classFile.fieldsCount; ++i) {
        is >> classFile.fields[i];
    }

    read_big_endian(is , (char*)&classFile.methods_count, sizeof(classFile.methods_count));

    classFile.methods = std::make_unique<MethodInfo[]>(classFile.methods_count);

    for (int i = 0; i < classFile.methods_count; ++i) {
        is >> classFile.methods[i];
    }

    read_big_endian(is, (char*)&classFile.attributesCount, sizeof(classFile.attributesCount));

    classFile.attributes = std::make_unique<AttributeInfo[]>(classFile.attributesCount);

    for (int i = 0; i < classFile.attributesCount; ++i) {
        is >> classFile.attributes[i];
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const FieldInfo &info) {
    os << "accessFlags: " << info.accessFlags << " nameIndex: " << info.nameIndex << " descriptorIndex: "
       << info.descriptorIndex << " attributesCount: " << info.attributesCount ;
    return os;
}

std::istream &operator>>(std::istream &is, FieldInfo &fieldInfo) {

    read_big_endian(is, (char*)&fieldInfo.accessFlags, sizeof(fieldInfo.accessFlags));
    read_big_endian(is, (char*)&fieldInfo.nameIndex, sizeof(fieldInfo.nameIndex));
    read_big_endian(is, (char*)&fieldInfo.descriptorIndex, sizeof(fieldInfo.descriptorIndex));
    read_big_endian(is, (char*)&fieldInfo.attributesCount, sizeof(fieldInfo.attributesCount));

    fieldInfo.attributes = std::make_unique<AttributeInfo[]>(fieldInfo.attributesCount);

    for (int i = 0; i < fieldInfo.attributesCount; ++i) {
        is >> fieldInfo.attributes[i];
    }
    return is;
}

std::istream &operator>>(std::istream &is, MethodInfo &methodInfo) {
    read_big_endian(is, (char*)&methodInfo.accessFlags, sizeof (methodInfo.accessFlags));
    read_big_endian(is, (char*)&methodInfo.nameIndex, sizeof (methodInfo.nameIndex));
    read_big_endian(is, (char*)&methodInfo.descriptorIndex, sizeof (methodInfo.descriptorIndex));
    read_big_endian(is, (char*)&methodInfo.attributesCount, sizeof (methodInfo.attributesCount));

    methodInfo.attributes = std::make_unique<AttributeInfo[]>(methodInfo.attributesCount);

    for (int i = 0; i < methodInfo.attributesCount; ++i) {
        is >> methodInfo.attributes[i];
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const MethodInfo &info) {
    os << "accessFlags: " << info.accessFlags << " nameIndex: " << info.nameIndex << " descriptorIndex: "
       << info.descriptorIndex << " attributesCount: " << info.attributesCount;
    return os;
}

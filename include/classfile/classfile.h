

#ifndef OMEGA_JVM_CLASSFILE_H
#define OMEGA_JVM_CLASSFILE_H

#include "constant_pool.h"
#include "attributes.h"
#include <iostream>
//TODO implenet acces flags for classs, attr field etc



class FieldInfo {
    public:
        friend std::ostream &operator<<(std::ostream &os, const FieldInfo &info);
        friend std::istream &operator>>(std::istream  &is, FieldInfo &fieldInfo);

        uint16_t accessFlags;
        uint16_t nameIndex;
        uint16_t descriptorIndex;
        uint16_t attributesCount;
        std::unique_ptr<AttributeInfo[]> attributes;
};

class MethodInfo {
    public:
        friend std::istream &operator>>(std::istream  &is, MethodInfo &methodInfo);

        friend std::ostream &operator<<(std::ostream &os, const MethodInfo &info);

    uint16_t accessFlags;
        uint16_t nameIndex;
        uint16_t descriptorIndex;
        uint16_t attributesCount;
        std::unique_ptr<AttributeInfo[]> attributes;
};

//todo подумать над реализацией раии и массивов
//todo raii убрать конструкторы копирования
class ClassFile {

    friend std::istream& operator>> (std::istream &is, ClassFile &dt);
    //todo убрать публик
    public:
        uint32_t magic;
        uint16_t minorVersion;
        uint16_t majorVersion;
        uint16_t constantPoolCount;
        std::unique_ptr<CpInfo[]> constantPool;
        uint16_t accessFlags;
        uint16_t thisClass;
        uint16_t superClass;
        uint16_t interfacesCount;
        std::unique_ptr<uint16_t[]> interfaces;
        uint16_t fieldsCount;
        std::unique_ptr<FieldInfo[]> fields;
        uint16_t methods_count;
        std::unique_ptr<MethodInfo[]> methods;
        uint16_t attributesCount;
        std::unique_ptr<AttributeInfo[]> attributes;
};


//todo дописать поля
#endif //OMEGA_JVM_CLASSFILE_H

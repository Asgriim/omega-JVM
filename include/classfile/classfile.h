

#ifndef OMEGA_JVM_CLASSFILE_H
#define OMEGA_JVM_CLASSFILE_H

#include "constant_pool.h"
#include "attributes.h"
#include <iostream>
//TODO implenet acces flags for classs, attr field etc


typedef std::vector<std::unique_ptr<CpInfo>> ConstPoolList;


enum FIELD_ACC_FLAGS{
    ACC_PUBLIC_FAF    = 0x0001,
    ACC_PRIVATE_FAF   = 0x0002,
    ACC_PROTECTED_FAF = 0x0004,
    ACC_STATIC        = 0x0008,
    ACC_FINAL         = 0x0010,
    ACC_VOLATILE      = 0x0040,
    ACC_TRANSIENT     = 0x0080,
    ACC_SYNTHETIC     = 0x1000,
    ACC_ENUM          = 0x4000,
};

enum FIELD_DESCRIPTOR : char {

};

struct GeneralInfo {
    virtual ~GeneralInfo() = default;

    uint16_t accessFlags;
    uint16_t nameIndex;
    uint16_t descriptorIndex;
    uint16_t attributesCount;
    AttributesList attributes;
};



// necessary?
struct FieldInfo : public GeneralInfo{
};

class MethodInfo : public GeneralInfo{
};

//todo подумать над реализацией раии и массивов
//todo raii убрать конструкторы копирования
struct ClassFile {


    //TODO: delete later
    //constants starts from 1
//    template<class T>
//    T& getConstant(uint64_t ind) {
//        return *(dynamic_cast<T*>(constantPool[ind - 1].get()));
//    }
//
//    template<class T>
//    static T& getAttribute(AttributesList attributes, uint64_t ind) {
//        return *(dynamic_cast<T*>(attributes[ind - 1].get()));
//    }

    uint32_t magic;
    uint16_t minorVersion;
    uint16_t majorVersion;
    uint16_t constantPoolCount;
    ConstPoolList constantPool;
    uint16_t accessFlags;
    uint16_t thisClass;
    uint16_t superClass;
    uint16_t interfacesCount;
    std::unique_ptr<uint16_t[]> interfaces;
    uint16_t fieldsCount;
    std::unique_ptr<FieldInfo[]> fields;
    uint16_t methodsCount;
    std::unique_ptr<MethodInfo[]> methods;
    uint16_t attributesCount;
    AttributesList attributes;
};


//todo дописать поля
#endif //OMEGA_JVM_CLASSFILE_H

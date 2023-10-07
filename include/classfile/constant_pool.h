

#ifndef OMEGA_JVM_CONSTANT_POOL_H
#define OMEGA_JVM_CONSTANT_POOL_H

#include <cstdint>
#include <vector>
#include <string>
#include <memory>


enum class CONSTANT_POOL_TAG : uint8_t {
    UTF8_CPT                 = 1,
    INTEGER_CPT              = 3,
    FLOAT_CPT                = 4,
    LONG_CPT                 = 5,
    DOUBLE_CPT               = 6,
    CLASS_CPT                = 7,
    STRING_CPT               = 8,
    FIELD_REF_CPT            = 9,
    METHOD_REF_CPT           = 10,
    INTERFACE_METHOD_REF_CPT = 11,
    NAME_AND_TYPE_CPT        = 12,
    METHOD_HANDLE_CPT        = 15,
    METHOD_TYPE_CPT          = 16,
    DYNAMIC_CPT              = 17,
    INVOKE_DYNAMIC_CPT       = 18,
    MODULE_CPT               = 19,
    PACKAGE_CPT              = 20
};

class CpInfo {

    friend std::istream& operator>> (std::istream &is, CpInfo &cpInfo);

    public:
        CONSTANT_POOL_TAG tag;
        std::unique_ptr<uint8_t[]> info;
};

//todo подумать нужно ли оно

class ClassInfoConstant {
    public:
        CONSTANT_POOL_TAG tag;
        uint16_t nameIndex;
};

class Utf8InfoConstant {
    CONSTANT_POOL_TAG tag;
    uint16_t length;
    std::string bytes;
};

//todo добавлять по необходимости
#endif //OMEGA_JVM_CONSTANT_POOL_H

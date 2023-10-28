

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

struct CpInfo {
    virtual ~CpInfo() = default;
    CONSTANT_POOL_TAG tag;
};

//todo подумать нужно ли оно

struct ClassInfoConst : public CpInfo{
    uint16_t nameIndex;
};

//todo UTF8 support.....
struct Utf8InfoConst : public CpInfo {
    uint16_t length;
    std::string bytes;
};

struct RefInfoConst : public CpInfo {
    uint16_t classIndex;
    uint16_t nameAndTypeIndex;
};

struct FieldRefConst : public RefInfoConst {

};

struct MethodRefConst : public RefInfoConst {

};

struct InterfaceMethRefConst : public RefInfoConst {

};

struct StringInfoConst : public CpInfo {
    uint16_t stringInd;
};

struct IntegerConst : public CpInfo {
    uint32_t bytes;
};

struct FloatConst : public CpInfo {
    uint32_t bytes;
};

struct LongConst : public CpInfo {
    uint32_t highBytes;
    uint32_t lowBytes;
};

struct DoubleConst : public CpInfo {
    uint32_t highBytes;
    uint32_t lowBytes;
};

struct NameAndTypeConst : public CpInfo {
    uint16_t nameIndex;
    uint16_t descriptorIndex;
};

struct MethodHandleConst : public CpInfo {
    uint8_t referenceKind;
    uint16_t referenceInd;
};


struct MethodTypeConst : public CpInfo {
    uint16_t descriptorInd;
};

struct DynamicConst : public CpInfo {
    uint16_t bootstrapMethodAttrInd;
    uint16_t nameAndTypeIndex;
};

struct InvokeDynamicConst : public DynamicConst {

};

struct ModuleInfoConst : CpInfo {
    uint16_t nameInd;
};

struct PackageInfoConst : ModuleInfoConst {

};


#endif //OMEGA_JVM_CONSTANT_POOL_H

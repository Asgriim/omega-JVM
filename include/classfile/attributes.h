

#ifndef OMEGA_JVM_ATTRIBUTES_H
#define OMEGA_JVM_ATTRIBUTES_H
#include <cstdint>
#include <memory>
#include <ostream>
#include <vector>
#include <unordered_map>



//----------------------------------------------------------------------------------------------------------
/** todo Seven attributes are critical to correct interpretation of the class file by the Java Virtual Machine:

    ConstantValue

    Code

    StackMapTable

    BootstrapMethods

    NestHost

    NestMembers

    PermittedSubclasses
 *
 *
 */
//----------------------------------------------------------------------------------------------------------

//todo 30 attrs in specs
enum ATTRIBUTE_TYPE {
    CODE_AT,
    BOOTSTRAP_METHODS_AT,
    LocalVariableTable_AT,
    METHOD_PARAMETERS_AT,
    //todo delete when implemnt all
    UNKNOWN_AT
};

static std::unordered_map<std::string, ATTRIBUTE_TYPE> attr_map {
        {"Code",CODE_AT},
        {"BootstrapMethods",BOOTSTRAP_METHODS_AT},
        {"LocalVariableTable", LocalVariableTable_AT},
        {"MethodParameters", METHOD_PARAMETERS_AT}
};

struct AttributeInfo {

    virtual ~AttributeInfo() = default;
    ATTRIBUTE_TYPE attributeType;
    uint16_t attributeNameIndex;
    uint32_t attributeLength;
};

typedef std::vector<std::unique_ptr<AttributeInfo>> AttributesList;

struct UnknownAttr : public AttributeInfo {
    std::unique_ptr<uint8_t[]> info;
};


struct ExceptionTableEntry {
    uint16_t startPc;
    uint16_t endPc;
    uint16_t handlerPc;
    uint16_t catchType;
};

struct CodeAttribute : public AttributeInfo {
    uint16_t maxStack;
    uint16_t maxLocals;
    uint32_t codeLength;
    std::unique_ptr<uint8_t[]> code;
    uint16_t exceptionTableLength;
    std::vector<ExceptionTableEntry> exceptionTable;
    uint16_t attributesCount;
    AttributesList attributes;
};

struct BootstrapMethodEntry {
    uint16_t bootstrapMethodRef;
    uint16_t numBootstrapArguments;
    std::unique_ptr<uint16_t[]> bootstrapArguments;
};

struct BootstrapMethodsAttribute : public AttributeInfo {
    uint16_t numBootstrapMethods;
    std::vector<BootstrapMethodEntry> bootstrapMethods;
};

struct LocalVariableEntry {
    uint16_t startPc;
    uint16_t length;
    uint16_t nameIndex;
    uint16_t descriptorIndex;
    uint16_t index;
};

struct LocalVariableTableAttribute : public AttributeInfo {
    uint16_t localVariableTableLength;
    std::vector<LocalVariableEntry> localVariableTable;
};

struct MethodParameterEntry {
    uint16_t nameIndex;
    uint16_t access_flags;
};

struct MethodParametersAttribute : public AttributeInfo {
    uint8_t parameters_count;
    std::vector<MethodParameterEntry> parameters;
};




#endif //OMEGA_JVM_ATTRIBUTES_H

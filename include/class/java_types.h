

#ifndef OMEGA_JVM_JAVA_TYPES_H
#define OMEGA_JVM_JAVA_TYPES_H

#include "cstdint"
#include "classfile/constant_pool.h"

class JClass;
struct JField;

typedef std::unordered_map<std::string, JField> DeclaredFields;

enum JAVA_DATA_TYPE : char {
    BOOL_JDT   = 'Z',
    BYTE_JDT   = 'B',
    CHAR_JDT   = 'C',
    SHORT_JDT  = 'S',
    INT_JDT    = 'I',
    FLOAT_JDT  = 'F',
    REF_JDT    = 'L',
    REF_ARR    = '[',
    LONG_JDT   = 'J',
    DOUBLE_JDT = 'D',
    VOID_JDT   = 'V',
    STRING_CONST
};

enum JARR_TYPE {
    T_BOOLEAN = 4,
    T_CHAR    = 5,
    T_FLOAT   = 6,
    T_DOUBLE  = 7,
    T_BYTE    = 8,
    T_SHORT   = 9,
    T_INT     = 10,
    T_LONG    = 11
};

struct JArray {
    JARR_TYPE type;
    void *array;
    uint32_t length;
};

struct ObjectInstance {
    JClass *type;
    DeclaredFields objFields;
};

//std::variant not usable here
union DataContent {
    bool jBool;
    int8_t jbyte;
    char jChar;
    int16_t jShort;
    int32_t jInt;
    float jFloat;
    RefInfoConst *refInfo;
    uint32_t jRetAddr;
    int64_t jLong;
    double jDouble;
    const std::string *string;
    ObjectInstance *jobj;
    JArray *jArray;
};

struct JavaValue {

    static JavaValue createByType(JAVA_DATA_TYPE type) {
        JavaValue javaType{};
        javaType.javaDataType = type;
        DataContent content{};
        switch (type) {

            case BOOL_JDT:
                content.jBool = false;
                break;
            case BYTE_JDT:
                content.jbyte = 0;
                break;
            case CHAR_JDT:
                content.jChar = 0;
                break;
            case SHORT_JDT:
                content.jShort = 0;
                break;
            case INT_JDT:
                content.jInt = 0;
                break;
            case FLOAT_JDT:
                content.jFloat = 0.0;
                break;
            case REF_JDT:
                content.jobj = nullptr;
                break;
            case REF_ARR: {
                content.jArray = nullptr;
                break;
            }
            case LONG_JDT:
                content.jLong = 0;
                break;
            case DOUBLE_JDT:
                content.jDouble = 0.0;
                break;
            case STRING_CONST:
                break;
        }
        javaType.data = content;
        return javaType;
    };
    JAVA_DATA_TYPE javaDataType;
    DataContent data;

};

struct JAnnotation {
    std::string name;
    std::string simpleName;
    JClass *jClass;
    std::unordered_map<std::string, JavaValue> params;
};


#endif //OMEGA_JVM_JAVA_TYPES_H

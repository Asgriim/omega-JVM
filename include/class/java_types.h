

#ifndef OMEGA_JVM_JAVA_TYPES_H
#define OMEGA_JVM_JAVA_TYPES_H

#include "cstdint"
#include "classfile/constant_pool.h"

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
    DOUBLE_JDT = 'D'
};

//todo reference implement
//std::variant not usable here
union DataContent {
    bool jBool;
    int8_t jbyte;
    uint16_t jChar;
    int16_t jShort;
    int32_t jInt;
    float jFloat;
    RefInfoConst *refInfo;
    uint32_t jRetAddr;
    int64_t jLong;
    double jDouble;
};

struct JavaType {

    static JavaType createByType(JAVA_DATA_TYPE type) {
        JavaType javaType{};
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
                //TODO damn man
                break;
            case REF_ARR:
                break;
            case LONG_JDT:
                content.jLong = 0;
                break;
            case DOUBLE_JDT:
                content.jDouble = 0.0;
                break;
        }
        javaType.data = content;
        return javaType;
    };

    JAVA_DATA_TYPE javaDataType;
    DataContent data;

};



#endif //OMEGA_JVM_JAVA_TYPES_H

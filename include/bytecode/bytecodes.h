

#ifndef OMEGA_JVM_BYTECODES_H
#define OMEGA_JVM_BYTECODES_H

#include "cstdint"

//Why? Why I live? Help?


enum BYTECODE : uint8_t {
    LDC            = 0x12,
    INVOKE_VIRTUAL = 0xB6,
    RETURN         = 0xB1,
    ACONST_NULL    = 0x1,
    ALOAD          = 0x19,
    ALOAD_N        = 0x2A,
    ANEW_ARRAY     = 0xBD,
    ARETURN        = 0xB0,
    ARRAY_LENGTH   = 0xBE,
    ASTORE         = 0x3A,
    //TODO *_N BYTECODES HANDLES SPECIAL
    ASTORE_N       = 0x4B,
    ATHROW         = 0xbf,
    BALOAD         = 0x33,
    BASTORE        = 0x54,
    BIPUSH         = 0x10,
    CALOAD         = 0x34,
    DADD           = 0x63,
    DALOAD         = 0x31,
    DASTORE        = 0x52,
    DCMPG          = 0x98,
    DCMPL          = 0x97,
    DCONST_0       = 0x0e,
    DCONST_1       = 0x0f,
    DDIV           = 0x6f,
    DLOAD          = 0x18,
    DLOAD_N        = 0x26,
    DMUL           = 0x6b,
    DNEG           = 0x77,
    DREM           = 0x73,
    DRETURN        = 0xaf,
    DSTORE         = 0x39,
    DSTORE_N       = 0x47,
    DSUB           = 0x67,
    DUP            = 0x59,
    FADD           = 0x62,
    GETSTATIC      = 0xb2,
    GOTO           = 0xa7,
};
#endif //OMEGA_JVM_BYTECODES_H

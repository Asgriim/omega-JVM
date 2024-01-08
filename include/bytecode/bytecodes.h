

#ifndef OMEGA_JVM_BYTECODES_H
#define OMEGA_JVM_BYTECODES_H

#include "cstdint"

//Why? Why I live? Help?


enum BYTECODE : uint8_t {
    GET_STATIC = 0xB2,
    LDC = 0x12,
    INVOKE_VIRTUAL = 0xB6,
    RETURN = 0xB1
};
#endif //OMEGA_JVM_BYTECODES_H

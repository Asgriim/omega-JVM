

#ifndef OMEGA_JVM_FRAME_H
#define OMEGA_JVM_FRAME_H

#include "classfile/classfile.h"
#include <stack>

//TODO: REWRITE ALL THIS FRAME LATER

struct Frame {
    ClassFile &classFile;
    CodeAttribute &code;
    std::stack<void*> operandStack;
};
#endif //OMEGA_JVM_FRAME_H

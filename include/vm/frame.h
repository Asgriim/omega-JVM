

#ifndef OMEGA_JVM_FRAME_H
#define OMEGA_JVM_FRAME_H

#include "class/j_class.h"
#include <stack>
#include "runtime/runtime_area.h"
//TODO: REWRITE ALL THIS FRAME LATER

struct Frame {
    Frame(CodeAttribute &code, RuntimeCP &runtimeCp, RuntimeArea *runtimeArea) : methodBytecode(code), runtimeCp(runtimeCp),
                                                                                 runtimeArea(runtimeArea) {}

    CodeAttribute &methodBytecode;
    RuntimeCP &runtimeCp;
    RuntimeArea *runtimeArea;
    std::stack<JavaType> operandStack;
    uint32_t pc = 0;
};
#endif //OMEGA_JVM_FRAME_H

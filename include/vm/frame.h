

#ifndef OMEGA_JVM_FRAME_H
#define OMEGA_JVM_FRAME_H

#include "class/j_class.h"
#include <stack>
#include "runtime/runtime_area.h"
//TODO: REWRITE ALL THIS FRAME LATER

struct Frame {
    Frame(CodeAttribute &code, RuntimeCP &runtimeCp) : methodBytecode(code), runtimeCp(runtimeCp){}

    CodeAttribute &methodBytecode;
    RuntimeCP &runtimeCp;
    std::stack<JavaValue> operandStack;
    std::vector<JavaValue> locals;
    uint32_t pc = 0;
};
#endif //OMEGA_JVM_FRAME_H

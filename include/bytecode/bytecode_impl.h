

#ifndef OMEGA_JVM_BYTECODE_IMPL_H
#define OMEGA_JVM_BYTECODE_IMPL_H

#include "bytecodes.h"
#include "unordered_map"
#include "vm/frame.h"
#include "functional"



namespace jbcf {
    void getstatic(Frame &frame, std::stack<Frame> &stack);

    void ldc(Frame &frame, std::stack<Frame> &stack);

    void invokevirtual(Frame &frame, std::stack<Frame> &stack) ;

    void jreturn(Frame &frame, std::stack<Frame> &stack);
}




#endif //OMEGA_JVM_BYTECODE_IMPL_H

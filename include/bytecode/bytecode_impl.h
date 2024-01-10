

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

    void iconst_m1(Frame &frame, std::stack<Frame> &stack);

    void iconst_0(Frame &frame, std::stack<Frame> &stack);

    void iconst_1(Frame &frame, std::stack<Frame> &stack);

    void iconst_2(Frame &frame, std::stack<Frame> &stack);

    void iconst_3(Frame &frame, std::stack<Frame> &stack);

    void iconst_4(Frame &frame, std::stack<Frame> &stack);

    void iconst_5(Frame &frame, std::stack<Frame> &stack);

    void putstatic(Frame &frame, std::stack<Frame> &stack);

    void bipush(Frame &frame, std::stack<Frame> &stack);

    void invokestatic(Frame &frame, std::stack<Frame> &stack);

    void iadd(Frame &frame, std::stack<Frame> &stack);

    void ireturn(Frame &frame, std::stack<Frame> &stack);

    void pop(Frame &frame, std::stack<Frame> &stack);
}




#endif //OMEGA_JVM_BYTECODE_IMPL_H

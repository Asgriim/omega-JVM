

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

    void newarray(Frame &frame, std::stack<Frame> &stack);

    void aload_n(Frame &frame, std::stack<Frame> &stack, uint32_t n);

    void aload_0(Frame &frame, std::stack<Frame> &stack);

    void aload_1(Frame &frame, std::stack<Frame> &stack);

    void aload_2(Frame &frame, std::stack<Frame> &stack);

    void aload_3(Frame &frame, std::stack<Frame> &stack);

    void aload(Frame &frame, std::stack<Frame> &stack);

    void astore_n(Frame &frame, std::stack<Frame> &stack, uint32_t n);

    void astore(Frame &frame, std::stack<Frame> &stack);

    void astore_0(Frame &frame, std::stack<Frame> &stack);

    void astore_1(Frame &frame, std::stack<Frame> &stack);

    void astore_2(Frame &frame, std::stack<Frame> &stack);

    void astore_3(Frame &frame, std::stack<Frame> &stack);

    void iastore(Frame &frame, std::stack<Frame> &stack);

    void iaload(Frame &frame, std::stack<Frame> &stack);

    void jnew(Frame &frame, std::stack<Frame> &stack);

    void dup(Frame &frame, std::stack<Frame> &stack);

    void sipush(Frame &frame, std::stack<Frame> &stack);

    void invokespecial(Frame &frame, std::stack<Frame> &stack);

    void putfield(Frame &frame, std::stack<Frame> &stack);

    void getfield(Frame &frame, std::stack<Frame> &stack);

    void castore(Frame &frame, std::stack<Frame> &stack);

}




#endif //OMEGA_JVM_BYTECODE_IMPL_H

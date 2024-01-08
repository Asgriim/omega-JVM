#include "bytecode/bytecode_impl.h"

namespace jbcf {

    void getstatic(Frame &frame, std::stack<Frame> &stack) {
        std::cout << "getstatic";
        stack.pop();
    }

    void ldc(Frame &frame, std::stack<Frame> &stack) {

    }

    void invokevirtual(Frame &frame, std::stack<Frame> &stack) {

    }

    void jreturn(Frame &frame, std::stack<Frame> &stack){

    }
}

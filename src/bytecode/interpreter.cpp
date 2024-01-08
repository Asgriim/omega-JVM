#include "bytecode/interpreter.h"
#include "iostream"


//pain
ByteOpMap Interpreter::m_byteOpMap = {
        {BYTECODE::GET_STATIC, jbcf::getstatic},
        {BYTECODE::LDC, jbcf::ldc},
        {BYTECODE::INVOKE_VIRTUAL, jbcf::invokevirtual},
        {BYTECODE::RETURN, jbcf::jreturn}
};

void Interpreter::execute(BYTECODE code, Frame &frame, std::stack<Frame> &stack) {
    auto it = m_byteOpMap.find(code);

    if (it == m_byteOpMap.end()) {
        std::cerr << "ILLEGAL INSTRUCTION";
        exit(-1);
    }

    it->second(frame, stack);
}

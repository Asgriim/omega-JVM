
#include "bytecode/interpreter.h"
#include "iostream"
#include "bytecode/native.h"
#include <format>

//pain
ByteOpMap Interpreter::m_byteOpMap = {
        {BYTECODE::GETSTATIC, jbcf::getstatic},
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

void Interpreter::execNative(std::string &methodFullName, Frame &frame, std::stack<Frame> &stack) {
    if (nativeMap.contains(methodFullName)) {
        nativeMap.find(methodFullName)->second(frame, stack);
    }

    std::cerr << std::format("METHOD NOT FOUND: {}\n", methodFullName);
}

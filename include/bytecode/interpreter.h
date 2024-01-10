

#ifndef OMEGA_JVM_INTERPRETER_H
#define OMEGA_JVM_INTERPRETER_H

#include "bytecode_impl.h"

typedef std::unordered_map<BYTECODE, std::function<void(Frame &, std::stack<Frame> &)>> ByteOpMap;

class Interpreter {
    public:
        static void execute(BYTECODE code, Frame &frame, std::stack<Frame> &stack);
        static void execNative(std::string &methodFullName, Frame &frame, std::stack<Frame> &stack);
        static void execClInit(JClass &jClass);
    private:
        static ByteOpMap m_byteOpMap;
    };
#endif //OMEGA_JVM_INTERPRETER_H

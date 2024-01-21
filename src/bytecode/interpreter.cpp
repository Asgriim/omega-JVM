
#include "bytecode/interpreter.h"
#include "iostream"
#include "bytecode/native.h"
#include <format>
#include "vm/vm.h"

//pain
ByteOpMap Interpreter::m_byteOpMap = {
        {BYTECODE::GETSTATIC, jbcf::getstatic},
        {BYTECODE::LDC, jbcf::ldc},
        {BYTECODE::INVOKE_VIRTUAL, jbcf::invokevirtual},
        {BYTECODE::RETURN, jbcf::jreturn},
        {BYTECODE::ICONST_M1, jbcf::iconst_m1},
        {BYTECODE::ICONST_0, jbcf::iconst_0},
        {BYTECODE::ICONST_1, jbcf::iconst_1},
        {BYTECODE::ICONST_2, jbcf::iconst_2},
        {BYTECODE::ICONST_3, jbcf::iconst_3},
        {BYTECODE::ICONST_4, jbcf::iconst_4},
        {BYTECODE::ICONST_5, jbcf::iconst_5},
        {BYTECODE::PUTSTATIC, jbcf::putstatic},
        {BYTECODE::BIPUSH, jbcf::bipush},
        {BYTECODE::INVOKESTATIC, jbcf::invokestatic},
        {BYTECODE::IADD, jbcf::iadd},
        {BYTECODE::IRETURN, jbcf::ireturn},
        {BYTECODE::POP, jbcf::pop},
        {BYTECODE::NEWARRAY, jbcf::newarray},
        {BYTECODE::ALOAD, jbcf::aload},
        {BYTECODE::ALOAD_0, jbcf::aload_0},
        {BYTECODE::ALOAD_1, jbcf::aload_1},
        {BYTECODE::ALOAD_2, jbcf::aload_2},
        {BYTECODE::ALOAD_3, jbcf::aload_3},
        {BYTECODE::ASTORE, jbcf::astore},
        {BYTECODE::ASTORE_0, jbcf::astore_0},
        {BYTECODE::ASTORE_1, jbcf::astore_1},
        {BYTECODE::ASTORE_2, jbcf::astore_2},
        {BYTECODE::ASTORE_3, jbcf::astore_3},
        {BYTECODE::ILOAD, jbcf::aload},
        {BYTECODE::ILOAD_0, jbcf::aload_0},
        {BYTECODE::ILOAD_1, jbcf::aload_1},
        {BYTECODE::ILOAD_2, jbcf::aload_2},
        {BYTECODE::ILOAD_3, jbcf::aload_3},
        {BYTECODE::IASTORE, jbcf::iastore},
        {BYTECODE::IALOAD, jbcf::iaload},
        {BYTECODE::NEW, jbcf::jnew},
        {BYTECODE::DUP, jbcf::dup},
        {BYTECODE::SIPUSH, jbcf::sipush},
        {BYTECODE::INVOKESPECIAL, jbcf::invokespecial},
        {BYTECODE::PUTFIELD, jbcf::putfield},
        {BYTECODE::GETFIELD, jbcf::getfield},
};

void Interpreter::execute(BYTECODE code, Frame &frame, std::stack<Frame> &stack) {
    auto it = m_byteOpMap.find(code);

    if (it == m_byteOpMap.end()) {
        int a = code;
        std::cerr << "ILLEGAL INSTRUCTION 0x" << std::hex << a;
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

void Interpreter::execClInit(JClass &jClass) {
    RuntimeArea *runtimeArea = RuntimeArea::getInstance();
    if (!runtimeArea->isClInitExist(jClass.getClassName())) {
        return;
    }
    MethodData methodData = runtimeArea->getMethod(jClass.getClassName() + ".<clinit>:()V");
    Frame frame(methodData.codeAttribute, jClass.getRuntimeCp());
    auto *vm = VM::getInstatance();
    vm->execFrame(frame);
}

Frame& Interpreter::createFrame(RuntimeCP &runtimeCp, MethodData &methodData, std::stack<Frame> &frameStack) {
    Frame frame(methodData.codeAttribute, runtimeCp);
    frameStack.push(frame);
    auto &ref = frameStack.top();
    for (auto &type : methodData.localVarsType) {
        ref.locals.emplace_back(JavaValue::createByType(type));
    }
    return ref;
}

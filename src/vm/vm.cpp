#include "vm/vm.h"
#include "bytecode/interpreter.h"

VM::VM() {
    m_runtimeArea = RuntimeArea::getInstance();
    m_stack = new std::stack<Frame>;
}

void VM::init() {

}

void VM::init(const std::vector<std::string> &classFiles) {
    //init runtime area -> load all classes -> load methods
    for (auto &classFile : classFiles) {
        m_runtimeArea->loadClass(classFile);
    }
    JClass &mainCl = m_runtimeArea->getMainClass();

    MethodData &method = m_runtimeArea->getMethod(mainCl.getClassName() + ".main:([Ljava/lang/String;)V");

    Frame frame(method.codeAttribute,
                mainCl.getRuntimeCp(),
                m_runtimeArea);

    m_stack->push(frame);
}

void VM::start() {
    while (!m_stack->empty()) {
        Frame &frame = m_stack->top();
        uint32_t pc = frame.pc;
        auto code = static_cast<BYTECODE>(frame.methodBytecode.code[pc]);
        Interpreter::execute(code, frame, *m_stack);
    }
    exit(0);
}



#include "vm/vm.h"

void VM::testMain(CodeAttribute &mainMethod, ClassFile &classFile) {
    Frame frame = {.classFile = classFile, .code = mainMethod};
    m_stack.push(frame);
    execFrame();
}

void VM::execFrame() {
    Frame &frame = m_stack.top();
    CodeAttribute &code = frame.code;
    uint32_t pc = 0;
    while (pc < code.codeLength) {
        uint8_t opCode = code.code[pc];
        switch (opCode) {
            case 0xb2: {
                pc += 2;
                break;
            }
            case 0x12: {
                pc += 1;
                auto strInf =  frame.classFile.getConstant<StringInfoConst>(code.code[pc]);
                auto *str =  new std::string(frame.classFile.getConstant<Utf8InfoConst>(strInf.stringInd).bytes);
                frame.operandStack.push((void*)str);
                break;
            }
            case 0xb6: {
                std::string *s = (std::string*)frame.operandStack.top();
                std::cout << *s << "\n";
                break;
            }
        }
        pc++;
    }
}

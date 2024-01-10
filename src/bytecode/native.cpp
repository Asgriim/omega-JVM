#include "bytecode/native.h"

namespace native {
    void println_str(Frame &frame, std::stack<Frame> &stack) {
        JavaType javaType = frame.operandStack.top();

        switch (javaType.javaDataType) {

            case BOOL_JDT: {
                std::cout << javaType.data.jBool << "\n";
                break;
            }
            case BYTE_JDT: {
                std::cout << javaType.data.jbyte << "\n";
                break;
            }
            case CHAR_JDT: {
                std::cout << javaType.data.jChar << "\n";
                break;
            }
            case SHORT_JDT: {
                std::cout << javaType.data.jShort << "\n";
                break;
            }
            case INT_JDT: {
                std::cout << javaType.data.jInt << "\n";
                break;
            }
            case FLOAT_JDT: {
                std::cout << javaType.data.jFloat << "\n";
                break;
            }
            case REF_JDT:
                break;
            case REF_ARR:
                break;
            case LONG_JDT: {
                std::cout << javaType.data.jLong << "\n";
                break;
            }
            case DOUBLE_JDT: {
                std::cout << javaType.data.jDouble << "\n";
                break;
            }
            case STRING_CONST: {
                std::cout << *javaType.data.string << "\n";
                break;
            }
        }
        frame.operandStack.pop();
        frame.operandStack.pop();
    }
}
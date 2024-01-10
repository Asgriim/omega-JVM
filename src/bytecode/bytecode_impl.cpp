#include "bytecode/bytecode_impl.h"
#include "bytecode/native.h"


namespace jbcf {

    void getstatic(Frame &frame, std::stack<Frame> &stack) {
        frame.pc++;
        uint16_t index = frame.methodBytecode.code[frame.pc] << 8;
        frame.pc++;
        index |= frame.methodBytecode.code[frame.pc];
        std::string fieldName = Resolver::resoveFieldFullName(frame.runtimeCp.getConstPool(),index);
        JavaType &javaType = RuntimeArea::getInstance()->getField(fieldName);
//        JavaType javaType;
//        javaType.javaDataType = JAVA_DATA_TYPE::REF_JDT;
//        javaType.data.refInfo = &fieldRef;
        frame.operandStack.push(javaType);
    }

    void ldc(Frame &frame, std::stack<Frame> &stack) {
        frame.pc++;
        uint8_t index = frame.methodBytecode.code[frame.pc] ;
        auto &item = frame.runtimeCp.getConstant<CpInfo>(index);
        JavaType javaType;
        switch (item.tag) {

            case CONSTANT_POOL_TAG::UTF8_CPT: {
                javaType.javaDataType = JAVA_DATA_TYPE::STRING_CONST;
                javaType.data.string = &frame.runtimeCp.getConstant<Utf8InfoConst>(index).bytes;
                break;
            }

            case CONSTANT_POOL_TAG::INTEGER_CPT: {
                javaType.javaDataType = JAVA_DATA_TYPE::INT_JDT;
                javaType.data.jInt = frame.runtimeCp.getConstant<IntegerConst>(index).bytes;
                break;
            }

            case CONSTANT_POOL_TAG::FLOAT_CPT: {
                javaType.javaDataType = JAVA_DATA_TYPE::FLOAT_JDT;
                javaType.data.jFloat = frame.runtimeCp.getConstant<FloatConst>(index).bytes;
                break;
            }

            case CONSTANT_POOL_TAG::LONG_CPT: {
                javaType.javaDataType = JAVA_DATA_TYPE::LONG_JDT;
                auto &longConst = frame.runtimeCp.getConstant<LongConst>(index);
                int64_t l = longConst.highBytes;
                l <<= 32;
                l |= longConst.lowBytes;
                javaType.data.jLong = l;
                break;
            }

            case CONSTANT_POOL_TAG::DOUBLE_CPT: {
                //todo double handle
                std::cout << "double\n";
                std::exit(-1);
//                javaType.javaDataType = JAVA_DATA_TYPE::DOUBLE_JDT;
//                auto &doubleConst = frame.runtimeCp.getConstant<DoubleConst>(index);
//                double d = doubleConst.highBytes << 32;
//                d |= doubleConst.lowBytes;
//                javaType.data.jDouble = d;
                break;
            }

            case CONSTANT_POOL_TAG::CLASS_CPT:
                abort();
                break;
            case CONSTANT_POOL_TAG::STRING_CPT: {
                javaType.javaDataType = JAVA_DATA_TYPE::STRING_CONST;
                javaType.data.string = &Resolver::resolveString(frame.runtimeCp.getConstPool(),index);
                break;
            }

            case CONSTANT_POOL_TAG::FIELD_REF_CPT:
                abort();
                break;
            case CONSTANT_POOL_TAG::METHOD_REF_CPT:
                abort();
                break;
            case CONSTANT_POOL_TAG::INTERFACE_METHOD_REF_CPT:
                abort();
                break;
            case CONSTANT_POOL_TAG::NAME_AND_TYPE_CPT:
                abort();
                break;
            case CONSTANT_POOL_TAG::METHOD_HANDLE_CPT:
                abort();
                break;
            case CONSTANT_POOL_TAG::METHOD_TYPE_CPT:
                abort();
                break;
            case CONSTANT_POOL_TAG::DYNAMIC_CPT:
                abort();
                break;
            case CONSTANT_POOL_TAG::INVOKE_DYNAMIC_CPT:
                abort();
                break;
            case CONSTANT_POOL_TAG::MODULE_CPT:
                abort();
                break;
            case CONSTANT_POOL_TAG::PACKAGE_CPT:
                abort();
                break;
        }
        frame.operandStack.push(javaType);
    }

    void invokevirtual(Frame &frame, std::stack<Frame> &stack) {

        //resolve method -> if native -> execute -> else create new frame
        frame.pc++;
        uint16_t index = frame.methodBytecode.code[frame.pc] << 8;
        frame.pc++;
        index |= frame.methodBytecode.code[frame.pc];
        std::string methodFullName = Resolver::resolveMethodFullName(
                frame.runtimeCp.getConstPool(),
                index
                );

//        std::cout << methodFullName << "\n";
        RuntimeArea *runtimeArea = RuntimeArea::getInstance();
        MethodData &methodData = runtimeArea->getMethod(methodFullName);

        if (methodData.isNative) {
            nativeMap.find(methodFullName)->second(frame, stack);
            return;
        }
    }

    void jreturn(Frame &frame, std::stack<Frame> &stack){
        if (!stack.empty()) {
            stack.pop();
        }
    }

    void iconst_m1(Frame &frame, std::stack<Frame> &stack) {
        JavaType javaType = JavaType::createByType(JAVA_DATA_TYPE::INT_JDT);
        javaType.data.jInt = -1;
        frame.operandStack.push(javaType);
    }

    void iconst_0(Frame &frame, std::stack<Frame> &stack) {
        JavaType javaType = JavaType::createByType(JAVA_DATA_TYPE::INT_JDT);
        javaType.data.jInt = 0;
        frame.operandStack.push(javaType);
    }

    void iconst_1(Frame &frame, std::stack<Frame> &stack) {
        JavaType javaType = JavaType::createByType(JAVA_DATA_TYPE::INT_JDT);
        javaType.data.jInt = 1;
        frame.operandStack.push(javaType);
    }

    void iconst_2(Frame &frame, std::stack<Frame> &stack) {
        JavaType javaType = JavaType::createByType(JAVA_DATA_TYPE::INT_JDT);
        javaType.data.jInt = 2;
        frame.operandStack.push(javaType);
    }

    void iconst_3(Frame &frame, std::stack<Frame> &stack) {
        JavaType javaType = JavaType::createByType(JAVA_DATA_TYPE::INT_JDT);
        javaType.data.jInt = 3;
        frame.operandStack.push(javaType);
    }

    void iconst_4(Frame &frame, std::stack<Frame> &stack) {
        JavaType javaType = JavaType::createByType(JAVA_DATA_TYPE::INT_JDT);
        javaType.data.jInt = 4;
        frame.operandStack.push(javaType);
    }

    void iconst_5(Frame &frame, std::stack<Frame> &stack) {
        JavaType javaType = JavaType::createByType(JAVA_DATA_TYPE::INT_JDT);
        javaType.data.jInt = 5;
        frame.operandStack.push(javaType);
    }

    void putstatic(Frame &frame, std::stack<Frame> &stack) {
        frame.pc++;
        uint16_t index = frame.methodBytecode.code[frame.pc] << 8;
        frame.pc++;
        index |= frame.methodBytecode.code[frame.pc];
        std::string fieldFullName = Resolver::resoveFieldFullName(frame.runtimeCp.getConstPool(),index);
        RuntimeArea *runtimeArea = RuntimeArea::getInstance();
        JavaType &javaType = runtimeArea->getField(fieldFullName);
        switch (javaType.javaDataType) {

            case BOOL_JDT:
                break;
            case BYTE_JDT:
                break;
            case CHAR_JDT:
                break;
            case SHORT_JDT:
                break;
            case INT_JDT: {
                javaType.data.jInt = frame.operandStack.top().data.jInt;
                break;
            }

            case FLOAT_JDT:
                break;
            case REF_JDT:
                break;
            case REF_ARR:
                break;
            case LONG_JDT:
                break;
            case DOUBLE_JDT:
                break;
            case STRING_CONST:
                break;
        }
        frame.operandStack.pop();
    }

    void bipush(Frame &frame, std::stack<Frame> &stack) {
        frame.pc++;
        uint8_t byte = frame.methodBytecode.code[frame.pc];
        JavaType javaType = JavaType::createByType(JAVA_DATA_TYPE::INT_JDT);
        javaType.data.jInt = byte;
    }

    void invokestatic(Frame &frame, std::stack<Frame> &stack) {
        frame.pc++;
        uint16_t index = frame.methodBytecode.code[frame.pc] << 8;
        frame.pc++;
        index |= frame.methodBytecode.code[frame.pc];
        std::string methodName = Resolver::resolveMethodFullName(frame.runtimeCp.getConstPool(),index);
        RuntimeArea *runtimeArea = RuntimeArea::getInstance();
        MethodData &methodData = runtimeArea->getMethod(methodName);

        if (methodData.isNative) {
            nativeMap.find(methodName)->second(frame, stack);
            return;
        }
        JClass &jclass = runtimeArea->getClass(methodName.substr(0,methodName.find('.')));
        Frame newFrame(methodData.codeAttribute, jclass.getRuntimeCp());
        newFrame.operandStack = frame.operandStack;
        stack.push(newFrame);
    }

    void iadd(Frame &frame, std::stack<Frame> &stack) {
        JavaType &op1 = frame.operandStack.top();
        frame.operandStack.pop();
        JavaType &op2 = frame.operandStack.top();
        frame.operandStack.pop();
        JavaType resType = JavaType::createByType(JAVA_DATA_TYPE::INT_JDT);
        resType.data.jInt = op1.data.jInt + op2.data.jInt;
        frame.operandStack.push(resType);
    }

    void ireturn(Frame &frame, std::stack<Frame> &stack) {
        if (!stack.empty()) {
            stack.pop();
            auto &i = frame.operandStack.top();
            frame.operandStack.pop();
            stack.top().operandStack.push(i);
        }
    }

    void pop(Frame &frame, std::stack<Frame> &stack) {
        frame.operandStack.pop();
    }

}

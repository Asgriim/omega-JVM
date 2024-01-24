
#include "bytecode/interpreter.h"
#include "iostream"
#include "bytecode/native.h"
#include <format>
#include "vm/vm.h"
#include <dlfcn.h>
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
        {BYTECODE::CASTORE, jbcf::castore},
        {BYTECODE::ISTORE_0, jbcf::astore_0},
        {BYTECODE::ISTORE_1, jbcf::astore_1},
        {BYTECODE::ISTORE_2, jbcf::astore_2},
        {BYTECODE::ISTORE_3, jbcf::astore_3},
        {BYTECODE::ISTORE, jbcf::astore},
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
    Frame frame(*methodData.codeAttribute, jClass.getRuntimeCp());
    auto *vm = VM::getInstatance();
    vm->execFrame(frame);
}

Frame& Interpreter::createFrame(RuntimeCP &runtimeCp, MethodData &methodData, std::stack<Frame> &frameStack) {
    Frame frame(*methodData.codeAttribute, runtimeCp);
    frameStack.push(frame);
    auto &ref = frameStack.top();
    for (auto &type : methodData.localVarsType) {
        ref.locals.emplace_back(JavaValue::createByType(type));
    }
    return ref;
}

void fillVect(std::vector<char> &buff, char * ptr, int size) {
    for (int i = 0; i < size; ++i) {
        buff.emplace_back( ptr[i]);
    }
}
//I want to die
void Interpreter::platformInvoke(MethodData &methodData, Frame &frame, std::stack<Frame> &stack) {

    if (methodData.annotations.empty()) {
        std::cerr << "Dllimport ANNOTATION NOT FOUND IN " << methodData.name << '\n';
        exit(-1);
    }

    JAnnotation dllAnnotation{};
    bool find = false;
    for (int i = 0; i < methodData.annotations.size(); ++i) {
        dllAnnotation = methodData.annotations[i];
        if (dllAnnotation.simpleName == "DllImport") {
            find = true;
            break;
        }
    }

    if (!find) {
        std::cerr << "Dllimport ANNOTATION NOT FOUND IN " << methodData.name << '\n';
        exit(-1);
    }
    if (!dllAnnotation.params.contains("value")) {
        std::cerr << "Dllimport ANNOTATION NOT FOUND IN " << methodData.name << '\n';
        exit(-1);
    }
    const char* dll = dllAnnotation.params.find("value")->second.data.string->data();
    std::cout << "name " << dll << "\n";
    void *lib = dlopen(dll, RTLD_LAZY );
    if (lib == nullptr) {
        std::cerr << "DLL NOT FOUND " << dll << '\n';
        exit(-1);
    }
    void* target = dlsym(lib, methodData.name.data());
    if (target == nullptr) {
        std::cerr << "DLL FUNCTION NOT FOUND " << methodData.name << '\n';
        exit(-1);
    }
    int64_t result = 0;
    uint64_t off = 0;
    //now working without this
    void *arg0 = 0;
    void *arg1 = 0;
    void *arg2 = 0;
    void *arg3 = 0;
    void *arg4 = 0;
    void *arg5 = 0;

    std::vector<char> buff;
    int extraArgs = methodData.argCount - 6;

    for (int i = 0; i < extraArgs; ++i) {
        JavaValue javaValue = frame.operandStack.top();
        char *ptr;
        int szof = 0;
        switch (javaValue.javaDataType) {

            case BOOL_JDT:
                break;
            case BYTE_JDT:
                break;
            case CHAR_JDT:
                break;
            case SHORT_JDT:
                break;
            case INT_JDT:
                ptr = (char*)&javaValue.data.jInt;
                szof = sizeof(javaValue.data.jInt);
                break;
            case FLOAT_JDT:
                break;
            case REF_JDT:
                std::cerr << "REFS OF CLASSES NOT SUPPORTED \n";
                exit(-1);
            case REF_ARR:
                ptr = (char*)&javaValue.data.jArray->array;
                szof = sizeof(javaValue.data.jArray->array);
                break;
            case LONG_JDT:
                break;
            case DOUBLE_JDT:
                break;
            case VOID_JDT:
                break;
            case STRING_CONST:
                break;
        }
        fillVect(buff, ptr, szof);
        frame.operandStack.pop();
    }

    uint64_t size = buff.size() / 8;
    off = (size % 2) * 8;

    for (int i = methodData.argCount - 1; i >= 0 ; i--) {
        void *bufVoid = 0;
        JavaValue javaValue = frame.operandStack.top();
        switch (javaValue.javaDataType) {

            case BOOL_JDT:
                bufVoid = (void*)javaValue.data.jBool;
                break;
            case BYTE_JDT:
                bufVoid = (void*)javaValue.data.jbyte;
                break;
            case CHAR_JDT:
                bufVoid = (void*)javaValue.data.jChar;
                break;
            case SHORT_JDT:
                bufVoid = (void*)javaValue.data.jShort;
                break;
            case INT_JDT:
                bufVoid = (void*)javaValue.data.jInt;
                break;
            case FLOAT_JDT:
                break;
            case REF_JDT:
                std::cerr << "REFS OF CLASSES NOT SUPPORTED \n";
                exit(-1);
                break;
            case REF_ARR:
                bufVoid = javaValue.data.jArray->array;
                break;
            case LONG_JDT:
                break;
            case DOUBLE_JDT:
                break;
            case VOID_JDT:
                break;
            case STRING_CONST:
                break;
        }


        //void[] not working. Why? Bad luck maybe
        switch (i) {
            case 0: {
                arg0 = bufVoid;
                break;
            }
            case 1: {
                arg1 = bufVoid;
                break;
            }
            case 2: {
                arg2 = bufVoid;
                break;
            }
            case 3: {
                arg3 = bufVoid;
                break;
            }
            case 4: {
                arg4 = bufVoid;
                break;
            }
            case 5: {
                arg5 = bufVoid;
                break;
            }

        }
        frame.operandStack.pop();
    }

    asm("mov %[size], %%rcx\n"
        "test %%rcx, %%rcx\n"
        "jz prep\n"
        "mov %[buff], %%rax\n"
        "sub %[off], %%rsp\n"
        "loop_start:\n"
        "push (%%rax)\n"
        "mov (%%rax), %%r9\n"
        "add $8, %%rax\n"
        "dec %%rcx\n"
        "jnz loop_start\n"
        "prep: mov  %[arg0], %%rdi\n"
        "mov  %[arg1], %%rsi\n"
        "mov  %[arg2], %%rdx\n"
        "mov  %[arg3], %%rcx\n"
        "mov  %[arg4], %%r8\n"
        "mov  %[arg5], %%r9\n"

        "call %[target] \n"
        "add %[off], %%rsp\n"
        "mov  %%rax, %[result]\n"
            :
    [result] "=X" (result)
    :
    [arg0] "X" (arg0),
    [arg1] "X" (arg1),
    [arg2] "X" (arg2),
    [arg3] "X" (arg3),
    [arg4] "X" (arg4),
    [arg5] "X" (arg5),
    [off] "X" (off),
    [size] "X" (size),
    [buff] "r" (buff.data()),
    [target] "X" (target)
    );

    JavaValue retVal = JavaValue::createByType(methodData.returnType);
    switch (retVal.javaDataType) {

        case BOOL_JDT: {
            retVal.data.jBool = result;
            break;
        }

        case BYTE_JDT: {
            retVal.data.jbyte = result;
            break;
        }

        case CHAR_JDT: {
            retVal.data.jChar = result;
            break;
        }

        case SHORT_JDT: {
            retVal.data.jShort = result;
            break;
        }

        case INT_JDT: {
            retVal.data.jInt = result;
            break;
        }

        case FLOAT_JDT:
            break;
        case REF_JDT: {
            std::cerr << "REFS OF CLASSES NOT SUPPORTED \n";
            exit(-1);
            break;
        }

        case REF_ARR: {
            JArray *arr = new JArray();
            arr->array = (void *)result;
            retVal.data.jArray = arr;
            break;
        }

        case LONG_JDT:
            break;
        case DOUBLE_JDT:
            break;
        case VOID_JDT:
            break;
        case STRING_CONST:
            break;
    }
    frame.operandStack.push(retVal);
}

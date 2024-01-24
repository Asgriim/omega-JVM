#include <dlfcn.h>

#include <gnu/lib-names.h>
#include "iostream"
#include "runtime/heap.h"
#include "vm/frame.h"

#include <asm/ptrace.h>
#include "stdio.h"
#include "cstdint"
extern "C" void pin(void *ptr);
asm(R"(
.globl pin
    .type pin, @function
    pin:
    call %rdi
    ret
)");

struct Registers {
    void *rdi;
    void *rsi;
    void *rdx;
    void *rcx;
    void *r8;
    void *r9;

};

void test() {
    pt_regs regs;
    regs.rcx = 1;

//    write(0,"as",2);

    void *a = dlopen("libc.so.6", RTLD_LAZY );
    if (a == NULL) {
        std::cout << "penis";
        exit(-1);
    }

    void* target = dlsym(a, "printf");
    char *error;
    if ((error = dlerror()) != NULL) {
        std::cout << "kek";
        exit(-1);
    }
//    int (*f)(int, char *, unsigned int);
//    f = dlsym(a, "write");;
    void *asdas = dlsym(a, "exit");
//    pin(asdas);

    int64_t result;
    char * zalupa = "asdasd %s %s %s %s %s %s %s\n";
    uint64_t off = 8;
//    write(2, zalupa, 4);
    uint x = 42;
    char *a1 = "a1";
    char *a2 = "a2";
    char *a3 = "a3";
    char *a4 = "a4";
    char *a5 = "a5";
    char *a6 = "a6123123";
    char *a7 = "a7";
    regs.rdi = reinterpret_cast<unsigned long>(zalupa);
    regs.rsi = reinterpret_cast<unsigned long>(a1);
    regs.rdx = reinterpret_cast<unsigned long>(a2);
    regs.rcx = reinterpret_cast<unsigned long>(a3);
    regs.r8 = reinterpret_cast<unsigned long>(a4);
    regs.r9 = (unsigned long )(a5);
    int fd = 1;
    int len = 4;
    char *beb = "kek\n";
    void *arg0 = zalupa;
    void *arg1 = a1;
    void *arg2 = a2;
    void *arg3 = a3;
    void *arg4 = a4;
    void *arg5 = a5;
    printf("123 %s %s %s %s %s %s %s \n",a1,a2,a3,a4,a5,a6,a7,a6,a7);

    char* args[6];
    args[0] = zalupa;
    args[1] = a1;
    args[2] = a2;
    args[3] = "a3";
    args[4] = a4;
    args[5] = a5;

    std::vector<char> buff;
    uint64_t addr = (uint64_t)a6;
    std::cout << "addr a6 " << std::hex << addr << "\n";
    char *ptr = (char*)&(a6);
    std::cout << "addr a6 ";
    for (int i = 0; i < sizeof(addr); ++i) {
        buff.emplace_back( ptr[i]);
        std::cout << std::hex << (0xFF & buff[i]) << "\n";
    }
    std::cout << "\n";
    addr = (uint64_t)a7;
    ptr = (char*)&(a7);
    for (int i = 0; i < sizeof(addr); ++i) {
        buff.emplace_back( ptr[i]);
        std::cout << std::hex << (0xFF & buff[i]) << "\n";
    }
    uint64_t size = buff.size() / 8;
    off = (size % 2) * 8;

//    asm("sub $0x8, %%rsp\n"
//        "mov %[buff], %%rax\n"
//            "push %%rax\n"
//        "mov  %[arg0], %%rdi\n"
//        "mov  %[arg1], %%rsi\n"
//        "mov  %[arg2], %%rdx\n"
//        "mov  %[arg3], %%rcx\n"
//        "mov  %[arg4], %%r8\n"
//        "mov  %[arg5], %%r9\n"
//
//        "call %[target] \n"
//        "mov  %%rax, %[result]\n"
//        "add $0x10, %%rsp\n"
//    :
//        [result] "=X" (result)
//    :
//        [arg0] "X" (arg0),
//        [arg1] "X" (arg1),
//        [arg2] "X" (arg2),
//        [arg3] "X" (arg3),
//        [arg4] "X" (arg4),
//        [arg5] "X" (arg5),
//        [off] "X" (off),
//        [buff] "r" (a6),
//        [target] "X" (target)
//
//    );




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

    std::cout << "result call " << result << "\n";
//    std::cout << buff.data() << "\n";
    exit(0);
}

int main(int argc, char *argv[]) {
    test();
//    void *a = dlopen(LIBC_SO, RTLD_LAZY);
//
//    if (a == NULL) {
//        std::cout << "kek";
//    }
//    // incoming
//    MethodData *methodData;
//    Frame *frame;
//
//    void* target = dlsym(a, methodData->name);
//
//    // prepare callsite state
//    char *buff = new char[methodData->argCount * 8]; // vector of bytes
//    pt_regs regs;
//    int64_t result;
//
//    int off;
//    for (int i = 0; i < methodData->argCount; i++ ) {
//        JavaValue value = frame->operandStack.top();
//        frame->operandStack.pop();
//        JClass argType = methodData->localVarsType[i];
//        if (argType.isCompatibleByAssignmentFrom(value)) {
//            switch (argType.internalType) { // marshall parameter from managed form to native
//                case BOOL_JDT:
//                    break;
//                case BYTE_JDT:
//                    break;
//                case CHAR_JDT:
//                    break;
//                case SHORT_JDT:
//                    break;
//                case INT_JDT:
//                    *(int32_t *) (buff + (off += 4)) = value.data.jInt;
//                    break;
//                case FLOAT_JDT:
//                    break;
//                case REF_JDT:
//                    break;
//                case REF_ARR:
//                    break;
//                case LONG_JDT:
//                    break;
//                case DOUBLE_JDT:
//                    break;
//                case STRING_CONST:
//                    break;
//            }
//        }
//    }
//
//    // apply callsite info to the machine state and perform actual native call
//    asm("sub  %[off], %%rsp\n\t"
//        "mov  %%ecx, %[off]\n\t"
//        "mov  %%rsi, %[buff]\n\t"
//        "mov  %%rdi, %%rsp\n\t"
//        "cld\n\t"
//        "rep movsb\n\t"
//        "mov  %%rcx, %[rcx]\n\t"
//        "call %[target]\n\t"
//        "mov  %%rax, %[result]\n\t"
//        "add  %[off], %%rsp\n\t"
//        :[off] "=&r" (off),
//        [buff] "=&r" (buff),
//        [rcx] "=&r" (regs.rcx),
//        [target] "=&r" (target),
//        [result] "=&m" (result)
//    );
//
//    // TODO marshall out-parameters back from native form to managed form
//
//    // TODO push result value if method return type is not Void
//    // frame->operandStack.push(...);
//
//
//    return 0;
}

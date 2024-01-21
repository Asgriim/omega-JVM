#include <dlfcn.h>

#include <gnu/lib-names.h>
#include "iostream"
#include "runtime/heap.h"
#include "vm/frame.h"

#include <asm/ptrace.h>

int main(int argc, char *argv[]) {
    void *a = dlopen(LIBC_SO, RTLD_LAZY);

    if (a == NULL) {
        std::cout << "kek";
    }
    // incoming
    MethodData *methodData;
    Frame *frame;

    void* target = dlsym(a, methodData->name);

    // prepare callsite state
    char *buff = new char[methodData->argCount * 8]; // vector of bytes
    pt_regs regs;
    int64_t result;

    int off;
    for (int i = 0; i < methodData->argCount; i++ ) {
        JavaValue value = frame->operandStack.top();
        frame->operandStack.pop();
        JClass argType = methodData->localVarsType[i];
        if (argType.isCompatibleByAssignmentFrom(value)) {
            switch (argType.internalType) { // marshall parameter from managed form to native
                case BOOL_JDT:
                    break;
                case BYTE_JDT:
                    break;
                case CHAR_JDT:
                    break;
                case SHORT_JDT:
                    break;
                case INT_JDT:
                    *(int32_t *) (buff + (off += 4)) = value.data.jInt;
                    break;
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
        }
    }

    // apply callsite info to the machine state and perform actual native call
    asm("sub  %[off], %%rsp\n\t"
        "mov  %%ecx, %[off]\n\t"
        "mov  %%rsi, %[buff]\n\t"
        "mov  %%rdi, %%rsp\n\t"
        "cld\n\t"
        "rep movsb\n\t"
        "mov  %%rcx, %[rcx]\n\t"
        "call %[target]\n\t"
        "mov  %%rax, %[result]\n\t"
        "add  %[off], %%rsp\n\t"
        :[off] "=&r" (off),
        [buff] "=&r" (buff),
        [rcx] "=&r" (regs.rcx),
        [target] "=&r" (target),
        [result] "=&m" (result)
    );

    // TODO marshall out-parameters back from native form to managed form

    // TODO push result value if method return type is not Void
    // frame->operandStack.push(...);
    

    return 0;
}

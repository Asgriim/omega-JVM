

#ifndef OMEGA_JVM_VM_H
#define OMEGA_JVM_VM_H


#include <stack>
#include "frame.h"


// TODO: this is test implement, rewrite later
class VM {
    public:

        // well...
        void testMain(CodeAttribute &mainMethod, ClassFile & classFile);
        void execFrame();
    private:
        std::stack<Frame> m_stack;
        uint64_t m_stackSize = 100;
};
#endif //OMEGA_JVM_VM_H

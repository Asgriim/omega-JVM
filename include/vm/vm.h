

#ifndef OMEGA_JVM_VM_H
#define OMEGA_JVM_VM_H


#include <stack>
#include "frame.h"
#include "runtime/runtime_area.h"
#include "zip.h"
// TODO: this is test implement, rewrite later
class VM {
    public:
        VM();

        void start();

        //if get classFiles from CLI
        void init(const std::vector<std::string> &classFiles);
        //todo implement jar files
        void init(zip *jarFile);
        std::string getMainClassFromManifest(zip *jarFile);
    private:
        RuntimeArea *m_runtimeArea;
        //todo rewrite on smart ptr
        std::stack<Frame> *m_stack;
        uint64_t m_stackSize = 100;
};
#endif //OMEGA_JVM_VM_H

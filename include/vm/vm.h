

#ifndef OMEGA_JVM_VM_H
#define OMEGA_JVM_VM_H


#include <stack>
#include "frame.h"
#include "runtime/runtime_area.h"
#include "zip.h"
// TODO: this is test implement, rewrite later
class VM {
    public:


        void start();
        void execFrame(Frame &frame);

        static VM* getInstatance(){
            if (m_instance == nullptr) {
                m_instance = new VM();
            }
            return m_instance;
        };

        //if get classFiles from CLI
        void init(const std::vector<std::string> &classFiles);

        void init(zip *jarFile);

        std::string getMainClassFromManifest(zip *jarFile);

        std::stack<Frame> *getStack() const;

private:
        VM();
        static VM *m_instance;
        RuntimeArea *m_runtimeArea;
        //todo rewrite on smart ptr
        std::stack<Frame> *m_stack;
        uint64_t m_stackSize = 100;
};
#endif //OMEGA_JVM_VM_H



#ifndef OMEGA_JVM_RUNTIME_CP_H
#define OMEGA_JVM_RUNTIME_CP_H
#include "classfile/classfile.h"


//TODO: OPTIMIZE LATER
class RuntimeCP {
    public:
        explicit RuntimeCP(ConstPoolList &constPool) : m_constPool(constPool) {}

        ConstPoolList &getConstPool() {
            return m_constPool;
        }

    private:
            ConstPoolList &m_constPool;

};

#endif //OMEGA_JVM_RUNTIME_CP_H



#ifndef OMEGA_JVM_RUNTIME_CP_H
#define OMEGA_JVM_RUNTIME_CP_H
#include "classfile/classfile.h"


//TODO: OPTIMIZE LATER
class RuntimeCP {
    public:
        explicit RuntimeCP(ConstPoolList &constPool) : m_constPool(constPool) {}

        template<class T>
        T& getConstant(uint64_t ind) {
            return *(dynamic_cast<T*>(m_constPool[ind - 1].get()));
        }

    private:
        ConstPoolList &m_constPool;

};

#endif //OMEGA_JVM_RUNTIME_CP_H



#ifndef OMEGA_JVM_CLASS_LOADER_H
#define OMEGA_JVM_CLASS_LOADER_H

#include "classfile/classfile_parser.h"
#include "class/j_class.h"
#include "runtime/heap.h"

class BootstrapClassLoader {
    public:
        BootstrapClassLoader();

    JClass loadClass(const std::string& classPath);
    private:
        Heap *m_heap;
};

#endif //OMEGA_JVM_CLASS_LOADER_H

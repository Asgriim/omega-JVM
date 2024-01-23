

#ifndef OMEGA_JVM_CLASS_LOADER_H
#define OMEGA_JVM_CLASS_LOADER_H

#include "classfile/classfile_parser.h"
#include "class/j_class.h"
#include "runtime/heap.h"
#include "zip.h"

class BootstrapClassLoader {
    public:
        BootstrapClassLoader();

        JClass loadClass(const std::string& classPath);
        void loadNative();
        void loadMethodLocals(MethodData &methodData, ConstPoolList &constPool);
        void setJarFile(zip *jarFile);
        void loadInternalClasses(JAVA_DATA_TYPE javaDataType, std::string name);
        void loadMethodAnnotations(MethodData &methodData, ClassFile &classFile, MethodInfo &methodInfo);
        JAnnotation loadAnnotation(Annotation &annotation, ClassFile &classFile);
        void loadMethods(ClassFile *classFile, std::string &jClassName);

private:
        Heap *m_heap;
        zip *m_jarFile = NULL;
};

#endif //OMEGA_JVM_CLASS_LOADER_H

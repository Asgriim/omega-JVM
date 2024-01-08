

#ifndef OMEGA_JVM_RUNTIME_AREA_H
#define OMEGA_JVM_RUNTIME_AREA_H


#include "class_loadrer/class_loader.h"

class RuntimeArea {
    public:
        RuntimeArea(RuntimeArea &other) = delete;

        void operator=(const RuntimeArea &) = delete;

        static RuntimeArea* getInstance() {
            if (m_instance == nullptr) {
                m_instance = new RuntimeArea();
            }
            return m_instance;
        };

        void loadClass(const std::string& classPath);

        JClass& getClass(const std::string& className);

        MethodData& getMethod(const std::string& methodName);

        JClass& getMainClass();

    private:
        RuntimeArea();

        static RuntimeArea *m_instance;
        Heap *m_heap;
        BootstrapClassLoader m_bootstrapClassLoader;
};
#endif //OMEGA_JVM_RUNTIME_AREA_H

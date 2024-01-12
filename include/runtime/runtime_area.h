

#ifndef OMEGA_JVM_RUNTIME_AREA_H
#define OMEGA_JVM_RUNTIME_AREA_H


#include "class_loadrer/class_loader.h"
#include "zip.h"
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

        void loadNative();

        JClass& getClass(const std::string& className);

        MethodData& getMethod(const std::string& methodName);

        JClass& getMainClass();

        JavaValue& getField(const std::string& fieldName);

        bool isClInitExist(const std::string &clName) {
            return m_heap->getMethodArea().methodMap.contains(clName + ".<clinit>:()V");
        };

        zip *getJarFile() const {
            return m_jarFile;
        }

        void setJarFile(zip *JarFile) {
            m_jarFile = JarFile;
            m_jar = true;
        }

        bool isJar() const;

private:
            RuntimeArea();
            zip *m_jarFile;
            bool m_jar;
            static RuntimeArea *m_instance;
            Heap *m_heap;
            BootstrapClassLoader m_bootstrapClassLoader;
};
#endif //OMEGA_JVM_RUNTIME_AREA_H

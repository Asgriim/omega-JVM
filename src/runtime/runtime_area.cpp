#include "runtime/runtime_area.h"
#include "format"


RuntimeArea * RuntimeArea::m_instance = nullptr;

RuntimeArea::RuntimeArea() {
    m_heap = Heap::getInstance();
}



void RuntimeArea::loadClass(const std::string &classPath) {
    if (m_jar) {
        m_bootstrapClassLoader.setJarFile(m_jarFile);
    }
    m_bootstrapClassLoader.loadClass(classPath + ".class");
}

JClass& RuntimeArea::getMainClass() {

    for (auto & it : m_heap->getMethodArea().methodMap) {
        if (it.first.find("main:([Ljava/lang/String;)V") != std::string::npos) {
            auto className = it.first.substr(0, it.first.find("."));
            return m_heap->getJClassTable().find(className)->second;
        }
    }

    std::cerr << "MAIN METHOD NOT FOUND \n";
    exit(-1);
    //cant get here
    abort();
}

MethodData &RuntimeArea::getMethod(const std::string &methodName) {

    if (m_jar && !m_heap->getMethodArea().methodMap.contains(methodName)) {
        auto clName = methodName.substr(0, methodName.find("."));
        loadClass(clName);
    }

    auto it = m_heap->getMethodArea().methodMap.find(methodName);

    if (it != m_heap->getMethodArea().methodMap.end()) {
        return it->second;
    }


    std::cerr << std::format("METHOD NOT FOUND: {} \n", methodName);
    exit(-1);
    //can't get here
    abort();
}

void RuntimeArea::loadNative() {
    m_bootstrapClassLoader.loadNative();
}

bool RuntimeArea::isJar() const {
    return m_jar;
}

JClass &RuntimeArea::getClass(const std::string &className) {

    if (m_jar && !m_heap->getJClassTable().contains(className)) {
        loadClass(className);
    }

    auto it = m_heap->getJClassTable().find(className);

    if (it != m_heap->getJClassTable().end()) {
        return it->second;
    }

    std::cerr << std::format("CLASS NOT FOUND: {} \n", className);
    exit(-1);
    //can't get here
    abort();
}

JavaType &RuntimeArea::getField(const std::string &fieldName) {
    if (m_jar && !m_heap->getFieldTable().contains(fieldName)) {
        loadClass(fieldName.substr(0,fieldName.find('.')));
    }

    auto it = m_heap->getFieldTable().find(fieldName);
    if (it != m_heap->getFieldTable().end()) {
        return it->second;
    }

    std::cerr << std::format("field NOT FOUND: {} \n", fieldName);
    exit(-1);
}








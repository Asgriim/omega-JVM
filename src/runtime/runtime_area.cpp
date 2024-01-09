#include "runtime/runtime_area.h"
#include "format"


RuntimeArea * RuntimeArea::m_instance = nullptr;

RuntimeArea::RuntimeArea() {
    m_heap = Heap::getInstance();
}



void RuntimeArea::loadClass(const std::string &classPath) {
    m_bootstrapClassLoader.loadClass(classPath);
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






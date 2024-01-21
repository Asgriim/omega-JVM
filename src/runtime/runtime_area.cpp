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

MethodData& RuntimeArea::lookUpMethod(JClass &jClass, const std::string &methodName) {
    std::string mFullName = jClass.getClassName() + "." + methodName;
    if (m_heap->getMethodArea().methodMap.contains(mFullName)) {
        return m_heap->getMethodArea().methodMap.find(mFullName)->second;
    } else {
        JClass &parent = getClass(jClass.getParent());

        if (parent.isNative() && !m_heap->getMethodArea().methodMap.contains(parent.getClassName() + "." + methodName)) {
            std::cerr << std::format("METHOD NOT FOUND: {} \n", methodName);
            exit(-1);
            //can't get here
            abort();
        }
        return lookUpMethod(parent, methodName);
    }
};

MethodData &RuntimeArea::getMethod(const std::string &methodName) {
    auto clName = methodName.substr(0, methodName.find("."));
    auto methodDesc = methodName.substr(methodName.find(".") + 1, methodName.length());
//    if (m_jar && !m_heap->getJClassTable().contains(clName)) {
//        loadClass(clName);
//    }

    JClass &jClass = getClass(clName);

    return lookUpMethod(jClass, methodDesc);

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



JField& RuntimeArea::lookUpField(JClass &jClass, const std::string &fieldName) {
    std::string mFullName = jClass.getClassName() + "." + fieldName;
    if (jClass.getDeclaredFields().contains(fieldName)) {
        return jClass.getDeclaredFields().find(fieldName)->second;
    } else {
        JClass &parent = getClass(jClass.getParent());

        if (parent.isNative() && !parent.getDeclaredFields().contains(fieldName)) {
            std::cerr << std::format(" NOT FOUND: {} \n", fieldName);
            exit(-1);
            //can't get here
            abort();
        }
        return lookUpField(parent, fieldName);
    }
};


JField& RuntimeArea::getField(const std::string &fieldName) {
    auto clName = fieldName.substr(0, fieldName.find("."));
    auto fieldDesc = fieldName.substr(fieldName.find(".") + 1, fieldName.length());

    JClass &jClass = getClass(clName);
    return lookUpField(jClass, fieldDesc);

}








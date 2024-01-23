

#ifndef OMEGA_JVM_HEAP_H
#define OMEGA_JVM_HEAP_H

#include <unordered_map>
#include "classfile/attributes.h"
#include "class/j_class.h"


//todo think about implementation

struct MethodData {
    CodeAttribute *codeAttribute;
    std::vector<JAVA_DATA_TYPE> localVarsType;
    bool isNative = false;
    bool isStatic = false;
    uint32_t argCount;
    std::string className;
    std::string name;
    std::string descriptor;
    JAVA_DATA_TYPE returnType;
    std::vector<JAnnotation> annotations;
};

struct MethodArea {
    //
    std::unordered_map<std::string, MethodData> methodMap;
};

class Heap {

    public:
        Heap(Heap &other) = delete;
        void operator=(const Heap &) = delete;

        static Heap* getInstance() {
            if (m_instance == nullptr) {
                m_instance = new Heap();
            }
            return m_instance;
        }

        MethodArea& getMethodArea(){
            return *m_methodArea;
        }

        std::unordered_map<std::string, JClass>& getJClassTable() {
            return *m_JClassTable;
        }

//        std::unordered_map<std::string, JavaValue>& getFieldTable() {
//            return *m_FieldTable;
//        }

private:
        Heap() {
            m_methodArea = new MethodArea();
            m_JClassTable = new std::unordered_map<std::string, JClass>;
//            m_FieldTable =  new std::unordered_map<std::string, JavaValue>;
        }

        static Heap *m_instance;
        MethodArea *m_methodArea;
        std::unordered_map<std::string, JClass> *m_JClassTable;
//        std::unordered_map<std::string, JavaValue> *m_FieldTable;
};
#endif //OMEGA_JVM_HEAP_H

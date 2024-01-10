

#ifndef OMEGA_JVM_HEAP_H
#define OMEGA_JVM_HEAP_H

#include <unordered_map>
#include "classfile/attributes.h"
#include "class/j_class.h"


//todo think about implementation

struct MethodData {
    CodeAttribute &codeAttribute;
    bool isNative = false;
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

        std::unordered_map<std::string, JavaType>& getFieldTable() {
            return *m_FieldTable;
        }

private:
        Heap() {
            m_methodArea = new MethodArea();
            m_JClassTable = new std::unordered_map<std::string, JClass>;
            m_FieldTable =  new std::unordered_map<std::string, JavaType>;
        }

        static Heap *m_instance;
        MethodArea *m_methodArea;
        std::unordered_map<std::string, JClass> *m_JClassTable;
        std::unordered_map<std::string, JavaType> *m_FieldTable;
};
#endif //OMEGA_JVM_HEAP_H



#ifndef OMEGA_JVM_J_CLASS_H
#define OMEGA_JVM_J_CLASS_H

#include "classfile/classfile.h"
#include "java_types.h"
#include "unordered_map"
#include "runtime/runtime_CP.h"
#include "vm/resolver.h"

//typedef std::unordered_map<std::string, JavaValue> VariablesTable;
struct JField {
    std::string name;
    JavaValue value;
    bool isStatic;
};

typedef std::unordered_map<std::string, JField> DeclaredFields;


//todo not fully implemented
class JClass {

    public:
        explicit JClass(ClassFile &classFile) : m_classFile(classFile), m_runtimeCp(classFile.constantPool)  {
            auto &clInfo = Resolver::getConstant<ClassInfoConst>(classFile.constantPool, classFile.thisClass);
            m_className = Resolver::resolveNameIndex(clInfo, classFile.constantPool);
        }

        JClass(bool isNative, ClassFile &classFile, std::string className ) : m_isNative(isNative), m_classFile(classFile), m_runtimeCp(classFile.constantPool) {
            m_className = className;
        }

        ClassFile &getClassFile() {
                return m_classFile;
        }

        RuntimeCP &getRuntimeCp() {
            return m_runtimeCp;
        }

        const std::string &getClassName() {
            return m_className;
        }


        bool isCompatibleByAssignmentFrom(JavaValue value) {

            return true; // TODO
        }

        void setInternalType(JavaValue internalType) {
            m_internalType = internalType;
        }

        void setParent(std::string parent) {
            m_parent = parent;
        }

        std::string& getParent() {
            return m_parent;
        }

        bool isNative(){
            return m_isNative;
        }

        DeclaredFields& getDeclaredFields(){
            return m_declaredFields;
        }

    private:
            bool m_isNative = false;
            ClassFile &m_classFile;
            std::string m_className;
            RuntimeCP m_runtimeCp;
            JavaValue m_internalType;
            DeclaredFields m_declaredFields;
            std::string m_parent;
//            VariablesTable m_staticVars;
};
#endif //OMEGA_JVM_J_CLASS_H



#ifndef OMEGA_JVM_J_CLASS_H
#define OMEGA_JVM_J_CLASS_H

#include "classfile/classfile.h"
#include "java_types.h"
#include "unordered_map"
#include "runtime/runtime_CP.h"
#include "vm/resolver.h"

typedef std::unordered_map<std::string, JavaType> VariablesTable;

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

        VariablesTable & getStaticVars() {
            return m_staticVars;
        }

        RuntimeCP &getRuntimeCp() {
            return m_runtimeCp;
        }

        const std::string &getClassName() {
            return m_className;
        }

    private:
            bool m_isNative = false;
            ClassFile &m_classFile;
            std::string m_className;
            RuntimeCP m_runtimeCp;
            VariablesTable m_staticVars;
};
#endif //OMEGA_JVM_J_CLASS_H

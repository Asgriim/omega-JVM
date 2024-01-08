

#ifndef OMEGA_JVM_RESOLVER_H
#define OMEGA_JVM_RESOLVER_H

#include "classfile/classfile.h"
#include "runtime/runtime_CP.h"
#include "unordered_map"


//todo 30 attrs :(
static std::unordered_map<std::string, ATTRIBUTE_TYPE> attr_map {
        {"Code",CODE_AT},
        {"BootstrapMethods",BOOTSTRAP_METHODS_AT}
};

class Resolver {
    public:




        //constants starts from 1
        template<class T>
        static T& getConstant(ConstPoolList &constPool,uint64_t ind) {
            return *(dynamic_cast<T*>(constPool[ind - 1].get()));
        }

        template<class T>
        static T& getAttribute(AttributesList &attributes, uint64_t ind) {
            return *(dynamic_cast<T*>(attributes[ind].get()));
        }


        template<typename T>
        static std::string & resolveDescriptor(T &t, ConstPoolList &constPool) {
            uint16_t ind = t.descriptorIndex;
            auto &utfStr = getConstant<Utf8InfoConst>(constPool, ind);
    //            auto &utfStr = constPool.getConstant<Utf8InfoConst>(ind);
            return utfStr.bytes;
        };

        template<typename T>
        static std::string & resolveNameIndex(T &t, ConstPoolList &constPool) {
            uint16_t ind = t.nameIndex;
            auto &utfStr = getConstant<Utf8InfoConst>(constPool, ind);
//            auto &utfStr = constPool.getConstant<Utf8InfoConst>(ind);
            return utfStr.bytes;
        };

        static ATTRIBUTE_TYPE resolveAttrType(ConstPoolList &constPool, uint16_t attributeNameIndex) {
            auto utf8Const = getConstant<Utf8InfoConst>(constPool, attributeNameIndex);
//            auto utf8Const = classFile.getConstant<Utf8InfoConst>(attributeNameIndex);
            if (attr_map.find(utf8Const.bytes) != attr_map.end()) {
                return attr_map.find(utf8Const.bytes)->second;
            } else {
                return UNKNOWN_AT;
            }
        }



};
#endif //OMEGA_JVM_RESOLVER_H

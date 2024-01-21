

#ifndef OMEGA_JVM_RESOLVER_H
#define OMEGA_JVM_RESOLVER_H

#include "classfile/classfile.h"
#include "runtime/runtime_CP.h"
#include "unordered_map"
#include <format>
#include "vector"
//todo 30 attrs :(


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

        static std::string& resovleUTF8str(ConstPoolList &constPool,uint16_t ind) {
            auto &utfStr = getConstant<Utf8InfoConst>(constPool, ind);
            return utfStr.bytes;
        }

        static std::string& resolveString(ConstPoolList &constPool,uint16_t ind) {
            uint16_t strInd = getConstant<StringInfoConst>(constPool, ind).stringInd;
            return getConstant<Utf8InfoConst>(constPool, strInd).bytes;
        }

        static std::string resolveMethodFullName(ConstPoolList &constPool, uint16_t ind) {
            auto &ref = getConstant<MethodRefConst>(constPool, ind);
            auto &cl = getConstant<ClassInfoConst>(constPool, ref.classIndex);
            std::string &clName = resolveNameIndex(cl, constPool);
            auto &nameAndType = getConstant<NameAndTypeConst>(constPool, ref.nameAndTypeIndex);
            std::string &mName = resolveNameIndex(nameAndType, constPool);
            std::string descriptor = resovleUTF8str(constPool, nameAndType.descriptorIndex);
            return std::format("{}.{}:{}", clName, mName, descriptor);
        }

        static std::string resolveNameAndType(ConstPoolList &constPool, uint16_t ind) {
            auto &nameAndType = getConstant<NameAndTypeConst>(constPool, ind);
            std::string &name = resolveNameIndex(nameAndType,constPool);
            std::string &descriptor = resovleUTF8str(constPool, nameAndType.descriptorIndex);
            return std::format("{}:{}",name, descriptor);
        }

        static std::string resoveFieldFullName(ConstPoolList &constPool, uint16_t ind) {
            if (ind == 13) {

            }
            auto &fieldRef = getConstant<FieldRefConst>(constPool, ind);
            auto &cl = getConstant<ClassInfoConst>(constPool, fieldRef.classIndex);
            std::string &clName = resolveNameIndex(cl, constPool);
            auto nameAndType = resolveNameAndType(constPool,fieldRef.nameAndTypeIndex);
            std::erase(nameAndType,';');
            return std::format("{}.{}", clName, nameAndType);
        }

        static uint32_t getArgCount(std::string &descriptor) {
            size_t i = 1;
            uint32_t count = 0;
            char c = descriptor.at(i);
            while (c != ')') {
                if (c == 'L') {
                    while (c != ';') {
                        i++;
                        c = descriptor.at(i);
                    }
                }
                if (c == '[') {
                    while (c == '[') {
                        i++;
                        c = descriptor.at(i);
                    }
                }
                count++;
                i++;
                c = descriptor.at(i);
            }
            return count;
        }

};
#endif //OMEGA_JVM_RESOLVER_H



#ifndef OMEGA_JVM_ATTRIBUTE_PARSER_H
#define OMEGA_JVM_ATTRIBUTE_PARSER_H

#include <unordered_map>
#include "classfile.h"
#include "classfile_stream.h"


//todo 30 attrs :(
static std::unordered_map<std::string, ATTRIBUTE_TYPE> attr_map {
    {"Code",CODE_AT},
    {"BootstrapMethods",BOOTSTRAP_METHODS_AT}
};

class AttributeParser {
    public:
        explicit AttributeParser(ClassFileStream &classFileStream) : m_clStream(classFileStream) {}


        static ATTRIBUTE_TYPE resolveAttrType(ClassFile &classFile, uint16_t attributeNameIndex) {
            auto utf8Const = classFile.getConstant<Utf8InfoConst>(attributeNameIndex);
            if (attr_map.find(utf8Const.bytes) != attr_map.end()) {
                return attr_map.find(utf8Const.bytes)->second;
            } else {
                return UNKNOWN_AT;
            }
        }

        void parseAttributes(ClassFile &classFile, AttributesList &attributes, uint16_t attributeCount);

        template<class T>
        T& readAttribute(AttributesList &attributes, uint16_t ind, uint16_t  attributeNameIndex, uint32_t attributeLength) {
            T *attr = new T;
            attr->attributeNameIndex = attributeNameIndex;
            attr->attributeLength = attributeLength;
            m_clStream >> *attr;
            attributes[ind].reset(attr);
            return *attr;
        }



    private:
        ClassFileStream &m_clStream;
};

#endif //OMEGA_JVM_ATTRIBUTE_PARSER_H

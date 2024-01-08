

#ifndef OMEGA_JVM_ATTRIBUTE_PARSER_H
#define OMEGA_JVM_ATTRIBUTE_PARSER_H

#include <unordered_map>
#include "classfile.h"
#include "classfile_stream.h"
#include "vm/resolver.h"



class AttributeParser {
    public:
        explicit AttributeParser(ClassFileStream &classFileStream) : m_clStream(classFileStream) {}


        static ATTRIBUTE_TYPE resolveAttrType(ClassFile &classFile, uint16_t attributeNameIndex) {
            return Resolver::resolveAttrType(classFile.constantPool, attributeNameIndex);
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

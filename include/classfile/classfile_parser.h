

#ifndef OMEGA_JVM_CLASSFILE_PARSER_H
#define OMEGA_JVM_CLASSFILE_PARSER_H

#include "classfile_stream.h"
#include "classfile.h"
#include "attribute_parser.h"

class ClassFileParser {
    public:
        explicit ClassFileParser(ClassFileStream &clStream);

        virtual ~ClassFileParser() = default;

        void parseClassFile(ClassFile &classFile);

        void parseConstPool(ClassFile &classFile);

        void parseGenInfo(ClassFile &classFile, GeneralInfo *generalInfo);

        template<class T>
        void readConstVal(ConstPoolList &constPool, size_t ind) {
            T *t = new T();
            m_clStream >> *t;
            constPool[ind].reset(t);
        }

    private:
        ClassFileStream &m_clStream;
        AttributeParser m_attributeParser;
};

#endif //OMEGA_JVM_CLASSFILE_PARSER_H

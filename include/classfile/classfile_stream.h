

#ifndef OMEGA_JVM_CLASSFILE_STREAM_H
#define OMEGA_JVM_CLASSFILE_STREAM_H

#include <iostream>
#include <istream>
#include <memory>
#include <cstdint>
#include "classfile.h"

class ClassFileStream {

    public:
        ClassFileStream(std::istream &is, int64_t buf_size = 2048);

        virtual ~ClassFileStream() = default;

        uint8_t readU1();

        uint16_t readU2();

        uint32_t readU4();

        uint64_t readU8();

        void readString(std::string &string, uint64_t len);

        bool isEOF();

        void readBytes(uint8_t* target, size_t size);

        void readBytesLE(uint8_t* target, size_t size);
        //todo реализовать seek_g()
        template<typename T>
        T read() {
            T out;
            readBytes((uint8_t*)&out,sizeof (T));
            return out;
        };

        ClassFileStream &operator>>(uint8_t &uint);

        ClassFileStream &operator>>(uint16_t &uint);

        ClassFileStream &operator>>(uint32_t &uint);

        ClassFileStream &operator>>(uint64_t &uint);

        // pain....
        ClassFileStream &operator>>(Utf8InfoConst &info);

        ClassFileStream &operator>>(ClassInfoConst &info);

        ClassFileStream &operator>>(FieldRefConst &info);

        ClassFileStream &operator>>(MethodRefConst &info);

        ClassFileStream &operator>>(InterfaceMethRefConst &info);

        ClassFileStream &operator>>(StringInfoConst &info);

        ClassFileStream &operator>>(IntegerConst &info);

        ClassFileStream &operator>>(FloatConst &info);

        ClassFileStream &operator>>(LongConst &info);

        ClassFileStream &operator>>(DoubleConst &info);

        ClassFileStream &operator>>(NameAndTypeConst &info);

        ClassFileStream &operator>>(MethodHandleConst &info);

        ClassFileStream &operator>>(MethodTypeConst &info);

        ClassFileStream &operator>>(DynamicConst &info);

        ClassFileStream &operator>>(InvokeDynamicConst &info);

        ClassFileStream &operator>>(ModuleInfoConst &info);

        ClassFileStream &operator>>(PackageInfoConst &info);

        ClassFileStream &operator>>(CodeAttribute &attribute);

        ClassFileStream &operator>>(BootstrapMethodsAttribute &attribute);

    ClassFileStream &operator>>(UnknownAttr &attribute);
    private:
        void allocBuf();
        void getFileLen();

        std::istream &m_is;
        int64_t m_curPos = 0;
        int64_t m_endPos = 0;
        uint64_t m_bufSize = 2048;
        std::unique_ptr<char[]> m_buf = nullptr;

};
#endif //OMEGA_JVM_CLASSFILE_STREAM_H

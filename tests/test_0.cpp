
#include "classfile/classfile.h"
#include <fstream>
#include <iostream>
#include "util/binary_io.h"
#include "classfile/classfile_stream.h"
#include "classfile/classfile_parser.h"


char* cpToStr(CONSTANT_POOL_TAG tag) {
    switch (tag) {

        case CONSTANT_POOL_TAG::UTF8_CPT:
            return "UTF8";
        case CONSTANT_POOL_TAG::INTEGER_CPT:
            return "INTEGER";
        case CONSTANT_POOL_TAG::FLOAT_CPT:
            return "FLOAT";
        case CONSTANT_POOL_TAG::LONG_CPT:
            return "LONG";
        case CONSTANT_POOL_TAG::DOUBLE_CPT:
            return "DOUBLE";
        case CONSTANT_POOL_TAG::CLASS_CPT:
            return "Class";
        case CONSTANT_POOL_TAG::STRING_CPT:
            return "String";;
        case CONSTANT_POOL_TAG::FIELD_REF_CPT:
            return "FieldRef";
        case CONSTANT_POOL_TAG::METHOD_REF_CPT:
            return "MethodRef";
        case CONSTANT_POOL_TAG::INTERFACE_METHOD_REF_CPT:
            return "InterfaceMethodRef";
        case CONSTANT_POOL_TAG::NAME_AND_TYPE_CPT:
            return "NameAndType";
        case CONSTANT_POOL_TAG::METHOD_HANDLE_CPT:
            return "MethodHandle";
        case CONSTANT_POOL_TAG::METHOD_TYPE_CPT:
            return "MethodType";
        case CONSTANT_POOL_TAG::DYNAMIC_CPT:
            return "Dynamic";
        case CONSTANT_POOL_TAG::INVOKE_DYNAMIC_CPT:
            return "InvokeDynamic";
        case CONSTANT_POOL_TAG::MODULE_CPT:
            return "Module";
        case CONSTANT_POOL_TAG::PACKAGE_CPT:
            return "Package";
    }
}

void print_cpInf(CpInfo &cpInfo){
    std::cout << cpToStr(cpInfo.tag) << "\n";
}

void print_classfile(ClassFile &classFile) {
    std::cout << std::hex << classFile.magic << "\n";
    std::cout <<std::dec << classFile.minorVersion << "\n";
    std::cout << classFile.majorVersion << "\n";
    std::cout << classFile.constantPoolCount << "\n";
    for (int i = 1; i < classFile.constantPoolCount; ++i) {
        std::cout << "#" << i <<" = ";
        std::cout << cpToStr(classFile.constantPool[i - 1]->tag);
        if (classFile.constantPool[i - 1]->tag == CONSTANT_POOL_TAG::UTF8_CPT) {
            std::cout << "       " << classFile.getConstant<Utf8InfoConst>(i).bytes;
        }
        std::cout << "\n";
    }
    std::cout << "acc flags " << std::dec << classFile.accessFlags << "\n";
    std::cout << "this class " << classFile.thisClass << "\n";
    std::cout << "super class" << classFile.superClass << "\n";
    std::cout << "interf count " << classFile.interfacesCount << "\n";
    std::cout << "fields count " << classFile.fieldsCount << "\n";

    std::cout << "method count " << classFile.methodsCount << "\n";
    std::cout << "attr count " << classFile.attributesCount << "\n";
}


struct dest {
    dest() {
        std::cout << "dest created \n";
    }
    ~dest() {
        std::cout << "dest died\n";
    }
};

void strema_test(std::istream &is) {
    uint64_t sz = 8;
    ClassFileStream classFileStream(is);
    sz = classFileStream.read<uint64_t>();
    std::cout << std::hex << sz << "\n";
}


void test_ptr(){
    std::vector<dest> b;
    std::cout << "bebra";
    b = std::vector<dest>(2);

}

void test_ClassfilePars(std::istream &is) {
    ClassFileStream classFileStream(is);
    ClassFile classFile;
    ClassFileParser parser(classFileStream);
    parser.parseClassFile(classFile);
    print_classfile(classFile);
}

int main() {
    std::ifstream file;
    file.open("/home/asgrim/CLionProjects/omega-jvm/java_files/Aboba.class",std::ios::binary | std::ios::in);
    test_ClassfilePars(file);
}
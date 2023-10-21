
#include "classfile/classfile.h"
#include <fstream>
#include <iostream>
#include "util/binary_io.h"
void print_cpInf(CpInfo &cpInfo){
    std::cout  << "tag " << static_cast<int>(cpInfo.tag) << "\n";
}

void print_classfile(ClassFile &classFile) {
    std::cout << std::hex << classFile.magic << "\n";
    std::cout <<std::dec << classFile.minorVersion << "\n";
    std::cout << classFile.majorVersion << "\n";
    std::cout << classFile.constantPoolCount << "\n";
    for (int i = 0; i < classFile.constantPoolCount - 1; ++i) {
        print_cpInf(classFile.constantPool[i]);
    }
    std::cout << "acc flags " << std::hex << classFile.accessFlags << "\n";
    std::cout << "this class " << classFile.thisClass << "\n";
    std::cout << "super class" << classFile.superClass << "\n";
    std::cout << "interf count " << classFile.interfacesCount << "\n";
    std::cout << "fields count " << classFile.fieldsCount << "\n";

    for (int i = 0; i < classFile.fieldsCount; ++i) {
        std::cout << classFile.fields[i] << "\n";
    }

    std::cout << "method count " << classFile.methods_count << "\n";
    for (int i = 0; i < classFile.methods_count; ++i) {
        std::cout << classFile.methods[i] << "\n";
    }
    std::cout << "attr count " << classFile.attributesCount << "\n";
    for (int i = 0; i < classFile.attributesCount; ++i) {
        std::cout << classFile.attributes[i] << "\n";
    }
};



int main() {
    std::ifstream file;
    file.open("/home/asgrim/CLionProjects/omega-jvm/java_files/Aboba.class",std::ios::binary | std::ios::in);
    uint32_t tes = 0;
//    read_big_endian(file,(char*)&tes, sizeof(tes));
//    std::cout << std::hex << tes;
    ClassFile classFile;
    file >> classFile;
    print_classfile(classFile);
}
#include <iostream>
#include <fstream>
#include "classfile/classfile.h"
#include "classfile/classfile_parser.h"
#include "vm/vm.h"

void testHello() {
    std::ifstream file("/home/asgrim/CLionProjects/omega-JVM/java_files/Hello.class");
    ClassFileStream clStr(file);
    ClassFileParser parser(clStr);
    ClassFile classFile;
    parser.parseClassFile(classFile);
    VM vm;
//    for (int i = 0; i < classFile.methodsCount; ++i) {
//        std::cout << classFile.methods[i].nameIndex << "\n";
//        std::cout << classFile.methods[i].attributes[0].get()->attributeNameIndex << "\n";
//    }

    CodeAttribute &mainMethod = *dynamic_cast<CodeAttribute *>(classFile.methods[1].attributes[0].get());
    vm.testMain(mainMethod,classFile);

}

int main() {
    testHello();
    return 0;
}

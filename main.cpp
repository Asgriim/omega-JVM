#include <iostream>
#include "ostream"
#include "vm/vm.h"

#include <zip.h>
#include <algorithm>
#include "cstring"


int main(int argc, char *argv[]) {
    VM *vm = VM::getInstatance();
    if (argc < 2) {
        std::cerr << "No arguments passed\n";
        exit(-1);
    }
    if (std::strcmp(argv[1], "-jar") == 0) {
        if (argc > 2) {
            int err = 0;
            auto *zip = zip_open(argv[2], ZIP_RDONLY, &err);
            if (zip == NULL) {
                std::cerr << "JAR not found\n";
                exit(-1);
            }
            vm->init(zip);
        } else {
            std::cerr << "No jar passed\n";
            exit(-1);
        }

    } else {
        std::vector<std::string> classes;
        for (int i = 1; i < argc; ++i) {
            std::cout << std::format("{} \n",argv[i]);
            classes.emplace_back(argv[i]);
        }
        vm->init(classes);
    }
    vm->start();
    return 0;
}



#include "vm/vm.h"
#include "format"
#include <iostream>
#include "class_loadrer/class_loader.h"


void test(std::vector<std::string> classes) {
    VM vm;
    vm.init(classes);
    vm.start();
}

int main(int argc, char *argv[]) {
//    std::cout << std::format("{} \n",argv[0]);
    std::vector<std::string> classes;
    for (int i = 1; i < argc; ++i) {
        std::cout << std::format("{} \n",argv[i]);
        classes.emplace_back(argv[i]);
    }
    test(classes);

    return 0;
}
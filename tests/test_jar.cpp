#include "iostream"
#include "vm/vm.h"
#include <zip.h>

void testJar(int argc, char *argv[]){
    VM vm;
    int err;
    auto *zip = zip_open("/home/asgrim/IdeaProjects/testing/target/testing-1.0-SNAPSHOT-jar-with-dependencies.jar", ZIP_RDONLY, &err);
    vm.init(zip);
    vm.start();
}

int main(int argc, char *argv[]) {
    testJar(argc, argv);
    return 0;
}

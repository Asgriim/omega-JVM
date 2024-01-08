#include <iostream>
#include "istream"
#include "ostream"

void test(std::istream & istream,std::ostream & ostream) {
    ostream << "bebra\n";

}

int main(int argc, char *argv[]) {
    test(std::cin,std::cout);
    return 0;
}

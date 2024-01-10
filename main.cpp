#include <iostream>
#include "istream"
#include "ostream"

#include <zip.h>
#include <algorithm>

void test(std::istream & istream,std::ostream & ostream) {
   int err = 0;
   auto *zip = zip_open("/home/asgrim/CLionProjects/omega-JVM/java_files/testing-1.0-SNAPSHOT-jar-with-dependencies.jar", ZIP_RDONLY, &err);
   auto *file = zip_fopen(zip, "META-INF/MANIFEST.MF",ZIP_FL_UNCHANGED);
   struct zip_stat stat{};
   zip_stat(zip, "META-INF/MANIFEST.MF", ZIP_FL_UNCHANGED, &stat);
   char buf[160];
//    std::cout << zip_file_is_seekable(file) << "\n";
//    zip_fseek(file, 0, SEEK_END);


   zip_fread(file, buf, 159);
   std::cout << zip_ftell(file) << "\n";
   std::string s(buf);
//   s.replace(s.begin(),s.end(),"\r","");
    std::erase(s,'\r');
//    std::replace( s.begin(), s.end(), '\r', ' ');
//    std::cout << s;
    auto s1 = s.substr(s.find("Main"),s.length());
    auto s2 = s1.substr(0, s1.find('\n'));
    auto clName = s2.substr(s2.find(':') + 1, s2.length());
    std::erase(clName, ' ');
    std::replace(clName.begin(),clName.end(), '.','/');
    std::cout << clName << "\n";
}

int main(int argc, char *argv[]) {
    test(std::cin,std::cout);
    return 0;
}

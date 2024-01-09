

#ifndef OMEGA_JVM_NATIVE_H
#define OMEGA_JVM_NATIVE_H

#include <unordered_map>
#include <string>
#include <vector>
#include <functional>
#include "vm/frame.h"

//tdod add all printl and print
static std::unordered_map<std::string, std::vector<std::string>> nativeClasMethods = {
        {"java/io/PrintStream",
         {"println:(Ljava/lang/String;)V"}
        }
};

static std::unordered_map<std::string, std::vector<std::string>> nativeClasFields = {
        {"java/lang/System",
         {"out:Ljava/io/PrintStream"}
        }
};



namespace native {
    void println_str(Frame &frame, std::stack<Frame> &stack);
}


static std::unordered_map<std::string, std::function<void(Frame &, std::stack<Frame> &)>> nativeMap = {
        {"java/io/PrintStream.println:(Ljava/lang/String;)V", native::println_str}
};

#endif //OMEGA_JVM_NATIVE_H

#include "vm/vm.h"
#include "bytecode/interpreter.h"

VM * VM::m_instance = nullptr;

VM::VM() {
    m_runtimeArea = RuntimeArea::getInstance();
    m_stack = new std::stack<Frame>;
}

void VM::init(zip *jarFile) {
    //open jar -> search manifest -> validate manifest

    m_runtimeArea->setJarFile(jarFile);
    m_runtimeArea->loadNative();
    std::string mainClName = getMainClassFromManifest(jarFile);

    MethodData &method = m_runtimeArea->getMethod(mainClName + ".main:([Ljava/lang/String;)V");

    JClass &mainCl = m_runtimeArea->getClass(mainClName);

    Interpreter::createFrame(mainCl.getRuntimeCp(), method, *m_stack);
//    Frame frame(method.codeAttribute,
//                mainCl.getRuntimeCp());

//    frame.locals

//    m_stack->push(frame);

}

void VM::init(const std::vector<std::string> &classFiles) {
    //init runtime area -> load all classes -> load methods

    m_runtimeArea->loadNative();
    for (auto &classFile : classFiles) {
        m_runtimeArea->loadClass(classFile);
    }
    JClass &mainCl = m_runtimeArea->getMainClass();

    MethodData &method = m_runtimeArea->getMethod(mainCl.getClassName() + ".main:([Ljava/lang/String;)V");

    Interpreter::createFrame(mainCl.getRuntimeCp(), method, *m_stack);

}

void VM::start() {
    while (!m_stack->empty()) {
        Frame &frame = m_stack->top();
        uint32_t pc = frame.pc;
        auto code = static_cast<BYTECODE>(frame.methodBytecode.code[pc]);
        Interpreter::execute(code, frame, *m_stack);
        frame.pc++;
    }
    exit(0);
}

std::string VM::getMainClassFromManifest(zip *jarFile) {
    auto *file = zip_fopen(jarFile, "META-INF/MANIFEST.MF", ZIP_FL_UNCHANGED);
    if (file == NULL) {
        std::cerr << "MANIFEST NOT FOUND\n";
        exit(-1);
    }
    struct zip_stat stat{};
    zip_stat(jarFile, "META-INF/MANIFEST.MF", ZIP_FL_UNCHANGED, &stat);
    char *buf = new char [stat.size];
    zip_fread(file, buf, stat.size);
    std::string s(buf);
    std::erase(s,'\r');
    auto s1 = s.substr(s.find("Main"),s.length());
    auto s2 = s1.substr(0, s1.find('\n'));
    auto clName = s2.substr(s2.find(':') + 1, s2.length());
    std::erase(clName, ' ');
    std::replace(clName.begin(), clName.end(),'.','/');
    return clName;
}

std::stack<Frame> *VM::getStack() const {
    return m_stack;
}

void VM::execFrame(Frame &frame) {
    m_stack->push(frame);
    while (frame.pc < frame.methodBytecode.codeLength) {
        uint32_t pc = frame.pc;
        auto code = static_cast<BYTECODE>(frame.methodBytecode.code[pc]);
        Interpreter::execute(code, frame, *m_stack);
        frame.pc++;
    }
}



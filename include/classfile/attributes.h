

#ifndef OMEGA_JVM_ATTRIBUTES_H
#define OMEGA_JVM_ATTRIBUTES_H
#include <cstdint>
#include <memory>
#include <ostream>

class AttributeInfo {
public:
    friend std::istream &operator>>(std::istream  &is, AttributeInfo &attributeInfo);

    friend std::ostream &operator<<(std::ostream &os, const AttributeInfo &info);

    uint16_t attributeNameIndex;
    uint32_t attributeLength;
    std::unique_ptr<uint8_t[]> info;
};

#endif //OMEGA_JVM_ATTRIBUTES_H

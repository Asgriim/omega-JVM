
#include "attributes.h"
#include "binary_io.h"

std::istream &operator>>(std::istream &is, AttributeInfo &attributeInfo) {
    read_big_endian(is,(char*)&attributeInfo.attributeNameIndex, sizeof(attributeInfo.attributeNameIndex));
    read_big_endian(is,(char*)&attributeInfo.attributeLength, sizeof(attributeInfo.attributeLength));
    attributeInfo.info = std::make_unique<uint8_t[]>(attributeInfo.attributeLength);
    read_big_endian(is, (char*)attributeInfo.info.get(), attributeInfo.attributeLength * sizeof(uint8_t ));
    return is;
}

std::ostream &operator<<(std::ostream &os, const AttributeInfo &info) {
    os << "attributeNameIndex: " << info.attributeNameIndex << " attributeLength: " << info.attributeLength;
    return os;
}


#include "classfile/constant_pool.h"

#include <iostream>

//todo рефактор
//std::istream &operator>>(std::istream &is, CpInfo &cpInfo) {
//    is.read((char*) &cpInfo.tag, sizeof(cpInfo.tag));
//    uint16_t lenToRead = 0;
//
//    switch (cpInfo.tag) {
//        case CONSTANT_POOL_TAG::UTF8_CPT:
//            read_big_endian(is, (char*) &lenToRead, sizeof(lenToRead));
//            is.seekg((int)-sizeof(lenToRead),std::ios::cur);
//            lenToRead += sizeof(lenToRead);
//            break;
//        case CONSTANT_POOL_TAG::INTEGER_CPT:
//            lenToRead = 4;
//            break;
//        case CONSTANT_POOL_TAG::FLOAT_CPT:
//            lenToRead = 4;
//            break;
//        case CONSTANT_POOL_TAG::LONG_CPT:
//            lenToRead = 8;
//            break;
//        case CONSTANT_POOL_TAG::DOUBLE_CPT:
//            lenToRead = 8;
//            break;
//        case CONSTANT_POOL_TAG::CLASS_CPT:
//            lenToRead = 2;
//            break;
//        case CONSTANT_POOL_TAG::STRING_CPT:
//            lenToRead = 2;
//            break;
//        case CONSTANT_POOL_TAG::FIELD_REF_CPT:
//            lenToRead = 4;
//            break;
//        case CONSTANT_POOL_TAG::METHOD_REF_CPT:
//            lenToRead = 4;
//            break;
//        case CONSTANT_POOL_TAG::INTERFACE_METHOD_REF_CPT:
//            lenToRead = 4;
//            break;
//        case CONSTANT_POOL_TAG::NAME_AND_TYPE_CPT:
//            lenToRead = 4;
//            break;
//        case CONSTANT_POOL_TAG::METHOD_HANDLE_CPT:
//            lenToRead = 3;
//            break;
//        case CONSTANT_POOL_TAG::METHOD_TYPE_CPT:
//            lenToRead = 2;
//            break;
//        case CONSTANT_POOL_TAG::DYNAMIC_CPT:
//            lenToRead = 4;
//            break;
//        case CONSTANT_POOL_TAG::INVOKE_DYNAMIC_CPT:
//            lenToRead = 4;
//            break;
//        case CONSTANT_POOL_TAG::MODULE_CPT:
//            lenToRead = 2;
//            break;
//        case CONSTANT_POOL_TAG::PACKAGE_CPT:
//            lenToRead = 2;
//            break;
//    }
//
//    cpInfo.info = std::make_unique<uint8_t[]>(lenToRead);
//    read_big_endian(is, (char *)cpInfo.info.get(),lenToRead);
//    return is;
//}

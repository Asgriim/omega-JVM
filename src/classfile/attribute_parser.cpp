
#include "classfile/attribute_parser.h"


void AttributeParser::parseAttributes(ClassFile &classFile, AttributesList &attributes, uint16_t attributeCount) {
    for (int i = 0; i < attributeCount; ++i) {
        uint16_t attrNameInd = m_clStream.readU2();
        uint32_t attrLength = m_clStream.readU4();
        ATTRIBUTE_TYPE type =  resolveAttrType(classFile, attrNameInd);
        //todo add for every attr type
        switch (type) {

            case CODE_AT: {
                auto &codeAttr = readAttribute<CodeAttribute>(attributes, i, attrNameInd, attrLength);
                parseAttributes(classFile, codeAttr.attributes, codeAttr.attributesCount);
                break;
            }
            case BOOTSTRAP_METHODS_AT: {
                readAttribute<BootstrapMethodsAttribute>(attributes,i,attrNameInd,attrLength);
                break;
            }
            case UNKNOWN_AT: {
                readAttribute<UnknownAttr>(attributes,i,attrNameInd,attrLength);
                break;
            }
            case LocalVariableTable_AT: {
                readAttribute<LocalVariableTableAttribute>(attributes,i,attrNameInd,attrLength);
                break;
            }
        }
    }
}

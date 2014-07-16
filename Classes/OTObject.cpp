#include "OTObject.h"

USING_NS_OT

OTObject::OTObject()
{

}

OTObject::~OTObject(){
    
}

OT::OTType OTObject::getClassType()
{
    return this->classType;
}
void OTObject::setClassType(OT::OTType type)
{
    this->classType = type;
}
#include "OTEntity.h"

USING_NS_ENTITY

OTEntity::OTEntity()
{
	this->classType = OTENTITY;
}
OTEntity::~OTEntity()
{
}

OT::OTType OTEntity::getClassType()
{
    return this->classType;
}

void OTEntity::setClassType(OT::OTType type)
{
    this->classType = type;
}
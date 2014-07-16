#include "OTPerson.h"

USING_NS_ENTITY

OTPerson::OTPerson()
{
	this->classType = OTPERSON;
}

OTPerson::~OTPerson()
{
}

void OTPerson::save(OT::OTObjectBlob *state)
{
    
}
void OTPerson::load(OT::OTObjectBlob *state)
{
    
}

OT::OTType OTPerson::getClassType()
{
    return this->classType;
}
void OTPerson::setClassType(OT::OTType type)
{
    this->classType = type;
}
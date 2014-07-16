#include "OTElevatorCar.h"

USING_NS_ENTITY

OTElevatorCar::OTElevatorCar()
{
	this->classType = OTELEVATORCAR;
}

OTElevatorCar::~OTElevatorCar()
{
    
}

void OTElevatorCar::save(OT::OTObjectBlob *state)
{
    
}
void OTElevatorCar::load(OT::OTObjectBlob *state)
{
    
}

OT::OTType OTElevatorCar::getClassType()
{
    return this->getClassType();
}
void OTElevatorCar::setClassType(OT::OTType type)
{
    this->classType = type;
}
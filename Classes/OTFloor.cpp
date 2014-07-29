#include "OTFloor.h"

USING_NS_STRUCTURE

OTFloor::OTFloor(void)
{
	this->classType = OTFLOOR;
	this->eval = 0;
	this->rent = 1000;
	this->occupancy = 10;
}


OTFloor::~OTFloor(void)
{
}

OT::OTType OTFloor::getClassType()
{
    return classType;
}

void OTFloor::setClassType(OT::OTType type)
{
    this->classType = type;
}

void OTFloor::save(OT::OTObjectBlob *state)
{
    if(state != NULL){
	
        state->addData("classtype", &classType, D_INT, 1);
        state->addData("eval", &eval, D_FLOAT, 1);
        state->addData("rent", &rent, D_DOUBLE, 1);
        state->addData("occupancy", &occupancy, D_INT, 1);
        state->addData("positionx", &x, D_FLOAT, 1);
        state->addData("positiony", &y, D_FLOAT, 1);
        state->addData("width", &width, D_FLOAT, 1);
        state->addData("height", &height, D_FLOAT, 1);
        state->addData("hash", &hash, D_INT, 1);
    }
	
}
void OTFloor::load(OT::OTObjectBlob *state)
{
    if(state != NULL) {
        char nameBuff[50];
        this->classType = OTFLOOR;
    
        state->getData("eval",&eval);
        state->getData("rent",&rent);
        state->getData("occupancy",&occupancy);
        state->getData("name",&nameBuff);
        state->getData("positionx",&x);
        state->getData("positiony", &y);
        state->getData("width",&width);
        state->getData("height",&height);
        state->getData("hash",&hash);
    
    }
}


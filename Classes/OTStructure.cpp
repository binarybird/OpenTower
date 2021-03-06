#include "OTStructure.h"

USING_NS_STRUCTURE

OTStructure::OTStructure()
{
    this->classType = OTSTRUCTURE;
}

OTStructure::~OTStructure()
{

}

OT::OTType OTStructure::getClassType()
{
    return this->classType;
}
void OTStructure::setClassType(OT::OTType type)
{
    this->classType = type;
}

bool OTStructure::doesCollideWithStructure(OT::Structure::OTStructure *otherStructure)
{
	//easier to calc if at (0,0) - structure actually spawns anchored to the center, not at the lower left corner
	float thisCorrectedX = this->x - this->width/2;
	float thisCorrectedY = this->y - this->height/2;
	float otherCorrectedX = otherStructure->x - otherStructure->width/2;
	float otherCorrectedY = otherStructure->y - otherStructure->height/2;

    //theres a 1px overlap in the x,y coord (building celing, floor, walls) so we need bodge it a little
	bool xOverlap = valueInRange(thisCorrectedX, otherCorrectedX, otherCorrectedX + (otherStructure->width-1)) || valueInRange(otherCorrectedX, thisCorrectedX, thisCorrectedX + (this->width-1));

    bool yOverlap = valueInRange(thisCorrectedY, otherCorrectedY, otherCorrectedY + (otherStructure->height - 1)) || valueInRange(otherCorrectedY, thisCorrectedY, thisCorrectedY + (this->height-1));

	/*if(xOverlap && yOverlap){
		CCLOG("XOVER: %d YOVER: %d this->(%f,%f,%f,%f) other->(%f,%f,%f,%f)",xOverlap,yOverlap,thisCorrectedX,thisCorrectedY,this->width,this->height,otherCorrectedX,otherCorrectedY,otherStructure->width,otherStructure->height);
		CCLOG("RAW: this->(%f,%f), other->(%f,%f)",this->x,this->y,otherStructure->x,otherStructure->y);
	}*/
    
    return xOverlap && yOverlap;

}

bool OTStructure::valueInRange(int value, int min, int max)
{ 
	return (value >= min) && (value <= max); 
}
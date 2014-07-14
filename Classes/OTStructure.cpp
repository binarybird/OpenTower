#include "OTStructure.h"

USING_NS_STRUCTURE

OTStructure::OTStructure()
{
	this->structureType = SOFFICE;
}

void OTStructure::save(OT::OTObjectBlob *state)
{

}
void OTStructure::load(OT::OTObjectBlob *state)
{
    
}

bool OTStructure::doesCollideWithStructure(OT::Structure::OTStructure *otherStructure)
{
	//easier to calc if at (0,0) - structure actually spawns in the center
	float thisCorrectedX = this->x - this->width/2;
	float thisCorrectedY = this->y - this->height/2;
	float otherCorrectedX = otherStructure->x - otherStructure->width/2;
	float otherCorrectedY = otherStructure->y - otherStructure->height/2;

	bool xOverlap = valueInRange(thisCorrectedX, otherCorrectedX, otherCorrectedX + otherStructure->width) || valueInRange(otherCorrectedX, thisCorrectedX, thisCorrectedX + this->width);

    bool yOverlap = valueInRange(thisCorrectedY, otherCorrectedY, otherCorrectedY + otherStructure->height) || valueInRange(otherCorrectedY, thisCorrectedY, thisCorrectedY + this->height);

    CCLOG("XOVER: %d YOVER: %d this->(%f,%f,%f) other->(%f,%f,%f)",xOverlap,yOverlap,thisCorrectedX,thisCorrectedY,this->width,otherCorrectedX,otherCorrectedY,this->height);
    
    return xOverlap && yOverlap;

}

bool OTStructure::valueInRange(int value, int min, int max)
{ 
	return (value >= min) && (value <= max); 
}
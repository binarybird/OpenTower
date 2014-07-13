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

bool OTStructure::doesCollideWithStructure(OT::Structure::OTStructure otherStructure)
{

	bool xOverlap = valueInRange(this->x, otherStructure.x,  otherStructure.x + otherStructure.width) ||
		valueInRange( otherStructure.x, this->x, this->x + this->width);

    bool yOverlap = valueInRange(this->y, otherStructure.y, otherStructure.y + otherStructure.height) ||
                    valueInRange(otherStructure.y, this->y, this->y + this->height);

    return xOverlap && yOverlap;

}

bool OTStructure::valueInRange(int value, int min, int max)
{ 
	return (value >= min) && (value <= max); 
}
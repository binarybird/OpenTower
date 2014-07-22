#include "OTPoint.h"

USING_NS_OT

OT::OTPoint OTPoint::ZERO = OT::OTPoint(0,0);

OTPoint::OTPoint()
{
	this->x = 0;
	this->y = 0;

	this->classType = OTPOINT;
	
}

OTPoint::OTPoint(float x, float y)
{
	this->x = x;
	this->y = y;
	
	this->classType = OTPOINT;
}

OTPoint::~OTPoint()
{
}

bool OTPoint::operator==(const OT::OTPoint right)
{
    if(this->x == right.x)
        if(this->y == right.y)
            return true;
    
    return false;
}

bool OTPoint::operator!=(const OT::OTPoint right)
{
    return !(*this == right);
}

OT::OTType OTPoint::getClassType()
{
    return this->classType;
}
void OTPoint::setClassType(OT::OTType type)
{
    this->classType = type;
}

#include "OTPoint.h"

USING_NS_OT

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


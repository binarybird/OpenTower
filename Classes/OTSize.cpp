#include "OTSize.h"

USING_NS_OT

OTSize::OTSize()
{
	this->width = 0;
	this->height = 0;

	this->classType = OTSIZE;

}

OTSize::OTSize(float width, float height)
{
	this->width = width;
	this->height = height;

	this->classType = OTSIZE;
}

OTSize::~OTSize()
{
}


#ifndef __OpenTower__OTPoint__
#define __OpenTower__OTPoint__
#include "OTMacros.h"
#include "OTObject.h"

USING_NS_OT_BEGIN

class OTPoint : OT::OTObject
{
public:
	OTPoint();
	OTPoint(float x, float y);
	~OTPoint();

	float x;
	float y;
	
};

USING_NS_OT_END

#endif
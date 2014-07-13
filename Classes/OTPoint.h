#ifndef __OpenTower__OTPoint__
#define __OpenTower__OTPoint__
#include "OTMacros.h"

USING_NS_OT_BEGIN

class OTPoint
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
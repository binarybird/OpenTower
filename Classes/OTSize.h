#ifndef __OpenTower__OTSize__
#define __OpenTower__OTSize__
#include "OTMacros.h"
#include "OTObject.h"

USING_NS_OT_BEGIN

class OTSize : public OT::OTObject
{
public:
	OTSize();
	OTSize(float width, float height);
	~OTSize();

	float width;
	float height;

};

USING_NS_OT_END
#endif
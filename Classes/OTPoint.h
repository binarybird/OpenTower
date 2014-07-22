#ifndef __OpenTower__OTPoint__
#define __OpenTower__OTPoint__
#include "OTMacros.h"
#include "OTObject.h"

USING_NS_OT_BEGIN

class OTPoint : public OTObject
{
public:
	OTPoint();
	OTPoint(float x, float y);
	~OTPoint();

	float x;
	float y;
    
    virtual OT::OTType getClassType() override;
    virtual void setClassType(OT::OTType type) override;

	OT::OTType classType;
    
    static OT::OTPoint ZERO;
    
    bool operator==(const OT::OTPoint right);
    bool operator!=(const OT::OTPoint right);
	
};

USING_NS_OT_END

#endif
//
//  OTStructure.h
//  OpenTower
//

#ifndef __OpenTower__OTStructure__
#define __OpenTower__OTStructure__

#include "OTObject.h"
#include "OTSerializable.h"
#include "OTPoint.h"
#include "OTSize.h"

USING_NS_STRUCTURE_BEGIN

class OTStructure : public OT::OTObject, public OT::OTSerializable, public OT::OTPoint, public OT::OTSize{
public:
	OTStructure();
	~OTStructure();

	bool doesCollideWithStructure(OT::Structure::OTStructure *otherStructure);
    
    virtual OT::OTType getClassType() override;
    virtual void setClassType(OT::OTType type) override;

	int hash;
	double rent;
	int occupancy;
	float eval;
    
	OT::OTType classType;

private:
	bool valueInRange(int value, int min, int max);
};

USING_NS_STRUCTURE_END

#endif /* defined(__OpenTower__OTStructure__) */

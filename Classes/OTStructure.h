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

class OTStructure : public OT::OTObject, OT::OTSerializable, OT::OTPoint, OT::OTSize{
public:
	OTStructure();
    virtual void save(OT::OTObjectBlob *state);
	virtual void load(OT::OTObjectBlob *state);
	bool doesCollideWithStructure(OT::Structure::OTStructure* otherStructure);
	OT::OTType structureType;
private:
	bool valueInRange(int value, int min, int max);
};

USING_NS_STRUCTURE_END

#endif /* defined(__OpenTower__OTStructure__) */

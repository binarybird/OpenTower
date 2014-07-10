//
//  OTStructure.h
//  OpenTower
//

#ifndef __OpenTower__OTStructure__
#define __OpenTower__OTStructure__

#include "OTObject.h"
#include "OTSerializable.h"
#include "OTDrawable.h"

USING_NS_STRUCTURE_BEGIN

class OTStructure : public OTObject, OTSerializable, OTDrawable{
public:
    virtual void save(OT::OTObjectBlob *state);
	virtual void load(OT::OTObjectBlob *state);
    void animate(OTTime time);
    int type;
};

USING_NS_STRUCTURE_END

#endif /* defined(__OpenTower__OTStructure__) */

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
    void save(OTObjectBlob *state);
	void load(OTObjectBlob *state);
    void animate(OTTime time);
    int type;
};

USING_NS_STRUCTURE_END

#endif /* defined(__OpenTower__OTStructure__) */

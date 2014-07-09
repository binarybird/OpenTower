//
//  OTStructure.h
//  OpenTower
//

#ifndef __OpenTower__OTStructure__
#define __OpenTower__OTStructure__

#include "OTObject.h"
#include "OTSerializable.h"

USING_NS_STRUCTURE_BEGIN

class OTStructure : public OTObject, OTSerializable{
public:
    void save(OTObjectBlob *state);
	void load(OTObjectBlob *state);
    int type;
};

USING_NS_STRUCTURE_END

#endif /* defined(__OpenTower__OTStructure__) */

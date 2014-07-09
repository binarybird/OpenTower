//
//  OTEntity.h
//  OpenTower
//

#ifndef __OpenTower__OTEntity__
#define __OpenTower__OTEntity__

#include "OTObject.h"
#include "OTSerializable.h"

USING_NS_ENTITIY_BEGIN

class OTEntity : public OTObject, OTSerializable{
public:
    void save(OTObjectBlob *state);
    void load(OTObjectBlob *state);
    int type;
};

USING_NS_ENTITY_END

#endif /* defined(__OpenTower__OTEntity__) */
 
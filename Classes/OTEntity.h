//
//  OTEntity.h
//  OpenTower
//

#ifndef __OpenTower__OTEntity__
#define __OpenTower__OTEntity__

#include "OTObject.h"
#include "OTSerializable.h"
#include "OTObjectBlob.h"

USING_NS_ENTITY_BEGIN

class OTEntity : public OT::OTObject, OT::OTSerializable{
public:
    void save(OT::OTObjectBlob *state);
    void load(OT::OTObjectBlob *state);
    int type;
};

USING_NS_ENTITY_END

#endif /* defined(__OpenTower__OTEntity__) */
 
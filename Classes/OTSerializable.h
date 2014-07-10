//
//  OTSerializable.h
//  OpenTower
//

#ifndef __OpenTower__OTSerializable__
#define __OpenTower__OTSerializable__
#include "OTObjectBlob.h"
#include "OTMacros.h"

USING_NS_OT_BEGIN
class OTSerializable{
public:
    virtual void save(OTObjectBlob *state);
    virtual void load(OTObjectBlob *state);
};

USING_NS_OT_END

#endif /* defined(__OpenTower__OTSerializable__) */

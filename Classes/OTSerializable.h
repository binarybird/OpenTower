//
//  OTSerializable.h
//  OpenTower
//

#ifndef __OpenTower__OTSerializable__
#define __OpenTower__OTSerializable__

#include "OTObjectBlob.h"
#include "OTMacros.h"
#include "OTObject.h"

USING_NS_OT_BEGIN
class OTSerializable : public OT::OTObject{
public:
    virtual void save(OT::OTObjectBlob *state);
    virtual void load(OT::OTObjectBlob *state);

	OT::OTType classType;
};

USING_NS_OT_END

#endif /* defined(__OpenTower__OTSerializable__) */

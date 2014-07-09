//
//  OTDrawable.h
//  OpenTower
//
#ifndef __OpenTower__OTDrawable__
#define __OpenTower__OTDrawable__

#include "OTMacros.h"
#include "cocos2d.h"
#include "OTObject.h"

USING_NS_OT_BEGIN

class OTDrawable : public OTObject{
public:
    virtual void animate(OTTime time);
};

USING_NS_OT_END

#endif /* defined(__OpenTower__OTDrawable__) */

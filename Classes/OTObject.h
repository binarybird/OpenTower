//
//  OTObject.h
//  OpenTower
//

#ifndef __OpenTower__OTObject__
#define __OpenTower__OTObject__

#include "OTMacros.h"
#include <iostream>

USING_NS_OT_BEGIN

class OTObject
{
public:
    OTObject();
    ~OTObject();

	OT::OTType classType;
    
};

USING_NS_OT_END

#endif /* defined(__OpenTower__OTObject__) */ 

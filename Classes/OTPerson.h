//
//  OTPerson.h
//  OpenTower
//

#ifndef __OpenTower__OTPerson__
#define __OpenTower__OTPerson__

#include "OTEntity.h"

USING_NS_ENTITY_BEGIN

class OTPerson : public OTEntity{
public:
    void save(OTObjectBlob *state);
	void load(OTObjectBlob *state);
};

USING_NS_ENTITY_END

#endif /* defined(__OpenTower__OTPerson__) */

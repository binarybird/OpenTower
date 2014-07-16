//
//  OTPerson.h
//  OpenTower
//

#ifndef __OpenTower__OTPerson__
#define __OpenTower__OTPerson__
#include "OTObjectBlob.h"
#include "OTEntity.h"

USING_NS_ENTITY_BEGIN

class OTPerson : public  OT::Entity::OTEntity{
public:
	OTPerson();
	~OTPerson();
    void save(OT::OTObjectBlob *state);
	void load(OT::OTObjectBlob *state);
    
    virtual OT::OTType getClassType() override;
    virtual void setClassType(OT::OTType type) override;
	OT::OTType classType;
};

USING_NS_ENTITY_END

#endif /* defined(__OpenTower__OTPerson__) */

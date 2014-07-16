//
//  OTElevatorCar.h
//  OpenTower
//

#ifndef __OpenTower__OTElevatorCar__
#define __OpenTower__OTElevatorCar__

#include "OTEntity.h"

USING_NS_ENTITY_BEGIN

class OTElevatorCar : public OT::Entity::OTEntity{
public:
    OTElevatorCar();
	~OTElevatorCar();
    void save(OT::OTObjectBlob *state);
	void load(OT::OTObjectBlob *state);
    
    virtual OT::OTType getClassType() override;
    virtual void setClassType(OT::OTType type) override;
	OT::OTType classType;
};

USING_NS_ENTITY_END

#endif /* defined(__OpenTower__OTElevatorCar__) */

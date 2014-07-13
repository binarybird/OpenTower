//
//  OTElevatorCar.h
//  OpenTower
//

#ifndef __OpenTower__OTElevatorCar__
#define __OpenTower__OTElevatorCar__

#include "OTEntity.h"


USING_NS_ENTITY_BEGIN

class OTElevatorCar : public OT::OTEntity{
public:
    OTElevatorCar();
    void save(OT::OTObjectBlob *state);
	void load(OT::OTObjectBlob *state);
};

USING_NS_ENTITY_END

#endif /* defined(__OpenTower__OTElevatorCar__) */

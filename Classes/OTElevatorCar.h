//
//  OTElevatorCar.h
//  OpenTower
//

#ifndef __OpenTower__OTElevatorCar__
#define __OpenTower__OTElevatorCar__

#include "OTEntity.h"

USING_NS_ENTITY_BEGIN

class OTElevatorCar : public OTEntity{
public:
    OTElevatorCar();
    void save(OTObjectBlob *state);
	void load(OTObjectBlob *state);
};

USING_NS_ENTITY_END

#endif /* defined(__OpenTower__OTElevatorCar__) */

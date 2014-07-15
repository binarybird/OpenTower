//
//  OpenTower.h
//  OpenTower
//

#ifndef __OpenTower__OpenTower__
#define __OpenTower__OpenTower__

#include "OTMacros.h"
#include "OTStructure.h"
#include "OTEntity.h"
#include "OTPoint.h"
#include "OTSize.h"
#include "OTSerializer.h"

#include <iostream>
#include <stdio.h>
#include "cocos2d.h"

USING_NS_OT_BEGIN

class OpenTowerManager{
public:
    OpenTowerManager();
    ~OpenTowerManager();

	void init();
    void removeStructure(OT::OTPoint position);
	void getStructure(OT::OTPoint position);
	void update(float delta);
	void cleanup();
	void save();

	bool addStructure(OT::OTType type, OT::OTPoint position);
	bool doesCollideWithStructure(OT::Structure::OTStructure *structure);
    OT::OTSize getSizeForStructure(enum OT::OTType type);
    int hashPoint(OT::OTPoint vector);

	static OpenTowerManager* sharedTowerManager();

	bool didInit;
    OT::OTTime currentTimeOfDay;
    OT::OTQuarter currentQuarter;
    int currentDayOfMonth;
	double cash;

private:
    static OpenTowerManager* _tower;
	std::vector<OT::Structure::OTStructure*>* structureRegistry;
	std::vector<OT::Entity::OTEntity*>* entityRegistry;

	float sigmaTime;

};

USING_NS_OT_END

#endif /* defined(__OpenTower__OpenTower__) */

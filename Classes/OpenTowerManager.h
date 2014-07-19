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
#include "OTOffice.h"

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>



USING_NS_OT_BEGIN

class OpenTowerManager{
public:
    OpenTowerManager();
    ~OpenTowerManager();

    void removeStructure(OT::OTPoint position);
	void removeStructure(int hash);
	void removeStructureAtIndex(int idx);
	OT::Structure::OTStructure* getStructure(OT::OTPoint position);
	OT::Structure::OTStructure* getStructure(int hash);
	OT::Structure::OTStructure* getStructureAtIndex(int idx);
    
    bool addStructure(OT::OTType type, OT::OTPoint position);
	bool doesCollideWithStructure(OT::Structure::OTStructure *structure);
    
    void init();
	void update(float delta);
	void cleanup();
	bool save();//will save to this->loadTowerPath if it exists - returns false otherwise
	bool load();//will load from this->loadTowerPath - assumes loadTowerPath exists and is correct - returns false otherwise

    OT::OTSize getSizeForStructure(enum OT::OTType type);
    int hashPoint(OT::OTPoint vector);
	int getStructureCount();
	int getEntityCount();

	static OpenTowerManager* sharedTowerManager();

	bool didInit;
    OT::OTTime currentTimeOfDay;
    OT::OTQuarter currentQuarter;
    int currentDayOfMonth;
	double cash;
    
    bool didLoadTower;
    std::string loadTowerPath;

private:
    static OpenTowerManager* _tower;
	std::vector<OT::Structure::OTStructure*>* structureRegistry;
	std::vector<OT::Entity::OTEntity*>* entityRegistry;

	float sigmaTime;

};

USING_NS_OT_END

#endif /* defined(__OpenTower__OpenTower__) */

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

static OT::OTTime currentTimeOfDay;
static OT::OTQuarter currentQuarter;
static int currentDayOfMonth;

USING_NS_OT_BEGIN

class OpenTowerManager{
public:
    OpenTowerManager();
    ~OpenTowerManager();
    
    static OpenTowerManager* sharedTowerManager();

	void addStructure(OT::OTType type, OT::OTPoint position);
    void removeStructure(OT::OTPoint position);
	void getStructure(OT::OTPoint position);
	bool structureDoesCollide(OT::OTPoint structurePoint);
    
	void update(float delta);

private:
    static OpenTowerManager* _tower;

	float sigmaTime;
	
    
    static std::map<int, Structure::OTStructure> structureRegistry;
    static std::map<int, Entity::OTEntity> entityRegistry;

};

USING_NS_OT_END

#endif /* defined(__OpenTower__OpenTower__) */

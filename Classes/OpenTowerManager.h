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
#include <map>

USING_NS_OT_BEGIN

static OT::OTTime currentTimeOfDay;
static OT::OTQuarter currentQuarter;
static int currentDayOfMonth;

class OpenTowerManager{
public:
    OpenTowerManager();
    ~OpenTowerManager();
    
    static OpenTowerManager* sharedTowerManager();

	void addStructure(OT::OTType type, OT::OTPoint position);
    void removeStructure(OT::OTPoint position);
	void getStructure(OT::OTPoint position);
	bool structureDoesCollide(OT::OTPoint structurePoint);
    OT::OTSize getSizeForStructure(enum OT::OTType type);
    int hashPoint(OT::OTPoint vector);
    
	void update(float delta);

private:
    static OpenTowerManager* _tower;

	float sigmaTime;
	
    
    static std::map<int, OT::Structure::OTStructure> structureRegistry;
    static std::map<int, OT::Entity::OTEntity> entityRegistry;

};

USING_NS_OT_END

#endif /* defined(__OpenTower__OpenTower__) */

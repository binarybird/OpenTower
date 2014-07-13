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

	bool addStructure(OT::OTType type, OT::OTPoint position);
    void removeStructure(OT::OTPoint position);
	void getStructure(OT::OTPoint position);
	bool doesCollideWithStructure(OT::Structure::OTStructure structure);
    OT::OTSize getSizeForStructure(enum OT::OTType type);
    int hashPoint(OT::OTPoint vector);
    
	void update(float delta);

	static std::map<int, OT::Structure::OTStructure> structureRegistry;
    static std::map<int, OT::Entity::OTEntity> entityRegistry;

private:
    static OpenTowerManager* _tower;

	float sigmaTime;
	
    
    

};

USING_NS_OT_END

#endif /* defined(__OpenTower__OpenTower__) */

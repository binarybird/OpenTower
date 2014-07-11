//
//  OpenTower.h
//  OpenTower
//

#ifndef __OpenTower__OpenTower__
#define __OpenTower__OpenTower__

#include "OTMacros.h"
#include "cocos2d.h"
#include "OTStructure.h"
#include "OTEntity.h"


USING_NS_OT_BEGIN

class OpenTowerManager{
public:
    OpenTowerManager();
    ~OpenTowerManager();
    
    static OpenTowerManager* sharedTowerManager();
	static OTTime inGameTimeOfDay;
    
    void addStructure(OTType type, cocos2d::Vec2 position);
    void removeStructure(OTType type, cocos2d::Vec2 position);
    
	size_t hash(const char* str);

	void update(float delta);

private:
    static OpenTowerManager* _tower;
    
    static std::map<size_t, Structure::OTStructure> structureRegistry;
    static std::map<size_t, Entity::OTEntity> entityRegistry;

};

USING_NS_OT_END

#endif /* defined(__OpenTower__OpenTower__) */

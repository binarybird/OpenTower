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
    
    void addStructure(OTType type, cocos2d::Vec2 position);
    void removeStructure(OTType type, cocos2d::Vec2 position);
    
private:
    static OpenTowerManager* _tower;
    
    static std::map<cocos2d::Vec2, Structure::OTStructure> structureRegistry;
    static std::map<OTType, Entity::OTEntity> entityRegistry;
};

USING_NS_OT_END

#endif /* defined(__OpenTower__OpenTower__) */

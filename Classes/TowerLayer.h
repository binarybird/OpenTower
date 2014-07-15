//
//  MouseLayer.h
//  OpenTower
//

#ifndef __OpenTower__TowerLayer__
#define __OpenTower__TowerLayer__

#include "cocos2d.h"
#include "OTMacros.h"
#include "Resources.h"
#include "OTPoint.h"
#include "OpenTowerManager.h"


class TowerLayer : public cocos2d::Layer
{
public:
    ~TowerLayer();//we allocated and attached user data to child nodes! (child alllocations handled by cocos2dx)
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TowerLayer);

	void createObject(OT::OTType t, cocos2d::Vec2 location);
	void update(float delta);
    
    
protected:
    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags);
	void createSprite(StructureUserData* ud, std::string plist, std::string sheet, cocos2d::Vec2 location);
    std::vector<int> tagRegistry;
    
    //void debugLocation(cocos2d::Vec2 location,OT::OTType type);
    //struct debug{
    //    cocos2d::Vec2 origin;
    //    cocos2d::Vec2 max;
    //};
    //std::vector<debug> debugData;
};

#endif /* defined(__OpenTower__MouseLayer__) */

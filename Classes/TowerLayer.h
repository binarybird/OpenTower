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
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
        
    // implement the "static create()" method manually
    CREATE_FUNC(TowerLayer);

	void createObject(OT::OTType t, cocos2d::Vec2 location);
	void update(float delta);
protected:
    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags);
	void createSprite(StructureUserData* ud, std::string plist, std::string sheet, cocos2d::Vec2 location);
};

#endif /* defined(__OpenTower__MouseLayer__) */

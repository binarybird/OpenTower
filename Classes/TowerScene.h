#ifndef __TOWER_SCENE_H__
#define __TOWER_SCENE_H__

#include "cocos2d.h"
#include "MouseLayer.h"
#include "TowerLayer.h"
#include "ToolPanalLayer.h"
#include "MainMenuScene.h"
#include "Resources.h"

#include "OTMacros.h"
#include "OTSize.h"
#include "OTPoint.h"
#include "OpenTowerManager.h"

class Tower : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void toolPanalCallback(OT::OTType type);

	void onMouseMove(cocos2d::Event* _event);
	void onMouseUp(cocos2d::Event* _event);
	void onMouseDown(cocos2d::Event* _event);
	void onMouseScroll(cocos2d::Event* _event);

	void createStructure(cocos2d::Vec2 position);
	cocos2d::Vec2 convertFromTowerSceneToTowerLayer(cocos2d::Vec2 location);
    
    void update(float delta);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Tower);
private:
    void initMouse();
	void initTower();
	void initToolPanal();
    
    MouseLayer* _mouseLayer;
	TowerLayer* _towerLayer;
	ToolPanalLayer* _toolPanalLayer;

    OT::OTType _currentStructure;
    float _mouseYOffset;
    cocos2d::Size _currentStructureSize;
	bool _isMovingToolPanal;
	float _windowOffsetX;
	float _windowOffsetY;
};

#endif 
#ifndef __TOWER_SCENE_H__
#define __TOWER_SCENE_H__

#include "cocos2d.h"
#include "MouseLayer.h"
#include "OTMacros.h"

class Tower : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void onMouseMove(cocos2d::Event* _event);
	void onMouseUp(cocos2d::Event* _event);
	void onMouseDown(cocos2d::Event* _event);
	void onMouseScroll(cocos2d::Event* _event);
    
    void update(float delta);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Tower);
private:
    void initMouse();
    
    MouseLayer* _mouseLayer;
    OTType _currentStructure;
    float _mouseYOffset;
    cocos2d::Size _currentStructureSize;
};

#endif 
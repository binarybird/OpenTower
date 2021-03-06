#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "TowerScene.h"
#include "LoadTowerLayer.h"
#include "Resources.h"
#include <string>
#include "OpenTower.h"

class MainMenu : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuOpenTowerCallback(cocos2d::Ref* pSender);
    void menuLoadTowerCallback(cocos2d::Ref* pSender);
    void menuMultiplayerCallback(cocos2d::Ref* pSender);
    void menuOptionsCallback(cocos2d::Ref* pSender);
    void closeLoadLayer();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
    
    
    
    bool buttonLock;
};

#endif // __HELLOWORLD_SCENE_H__

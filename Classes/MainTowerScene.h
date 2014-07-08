#ifndef __MainTowerScene_SCENE_H__
#define __MainTowerScene_SCENE_H__

#include "cocos2d.h"

class MainTowerScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

	void generateMap();
    
    // implement the "static node()" method manually
    CREATE_FUNC(MainTowerScene);
};

#endif // __HELLOWORLD_SCENE_H__

#ifndef __LoadTower_LAYER_H__
#define __LoadTower_LAYER_H__

#include "cocos2d.h"
#include "Resources.h"


class LoadTowerLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void setMainMenu(cocos2d::Layer* scene);
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(LoadTowerLayer);
private:
    cocos2d::Layer* _menu;
    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags);
};
#endif
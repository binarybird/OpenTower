#ifndef __PANAL_LAYER_H__
#define __PANAL_LAYER_H__

#include "cocos2d.h"
#include "OTMacros.h"


class ToolPanalLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	void officeCallback(cocos2d::Ref* pSender);

	void setTowerScene(cocos2d::Layer* tower);
    
    // implement the "static create()" method manually
    CREATE_FUNC(ToolPanalLayer);
protected:
    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags);
    cocos2d::Layer* _tower;
};
#endif
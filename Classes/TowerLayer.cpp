#include "TowerLayer.h"

USING_NS_CC;

bool TowerLayer::init(){
    
    if ( !Layer::init() )
    {
        return false;
    }
    
	CCDirector::getInstance()->setDepthTest(true);
	this->setVertexZ(5);

     //|| CC_TARGET_PLATFORM == CC_PLATFORM_WINDOWS || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        auto sprite = Sprite::create("OT_skyline.png");
    #else
        auto sprite = Sprite::create("UI/OT_skyline.png");
    #endif
    
    sprite->setPosition(Vec2(0,0));
	this->addChild(sprite);
    
    return true;
}


void TowerLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{

}
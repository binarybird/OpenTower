#include "TowerLayer.h"

USING_NS_CC;

bool TowerLayer::init(){
    
    if ( !Layer::init() )
    {
        return false;
    }
    
	CCDirector::getInstance()->setDepthTest(true);
	this->setVertexZ(5);

	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("UI/OT_skyline.png");
    sprite->setPosition(Vec2(0,0));
	this->addChild(sprite);
    
    return true;
}


void TowerLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{

}
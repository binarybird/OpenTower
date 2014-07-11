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
	//this->addChild(sprite);
	this->scheduleUpdate();
    
    return true;
}

void TowerLayer::update(float delta){

    //READ from  OT::OpenTowerManager::sharedTowerManager()->inGameTimeOfDay, adjust sprites accordingly

	//TODO - how to store and manage sprites
	//map with OT::OpenTowerManager::sharedTowerManager()->hash() and sprite?
}

void TowerLayer::createObject(OTType t, Vec2 location)
{
	//create animated sprite here
	CCLog("");
}

void TowerLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    DrawPrimitives::drawSolidRect(Vec2(0,0),Vec2(10,10),Color4F::GRAY);
}
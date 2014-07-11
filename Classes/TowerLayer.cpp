#include "TowerLayer.h"

USING_NS_CC;

bool TowerLayer::init(){
    
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
	CCDirector::getInstance()->setDepthTest(true);
	this->setVertexZ(5);

     //|| CC_TARGET_PLATFORM == CC_PLATFORM_WINDOWS || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        auto sprite = Sprite::create("OT_skyline.png");
    #else
        auto sprite = Sprite::create("UI/OT_skyline.png");
    #endif
    
    sprite->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	this->addChild(sprite);
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
	auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("office.plist","office.png");
    
    Sprite* _sprite1 = Sprite::createWithSpriteFrameName("office_0_d_0.png");
    _sprite1->setPosition( location );
    addChild(_sprite1,100);
    
    Vector<SpriteFrame*> animFrames(15);
    
    char str[100] = {0};
    for(int i = 1; i < 5; i++)
    {
        sprintf(str, "office_0_d_%d.png", i);
        auto frame = cache->getSpriteFrameByName( str );
        animFrames.pushBack(frame);
    }
    
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
    _sprite1->runAction( RepeatForever::create( Animate::create(animation) ) );
}

void TowerLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    //DrawPrimitives::drawSolidRect(Vec2(0,0),Vec2(10,10),Color4F::GRAY);//debugging (0,0)
}
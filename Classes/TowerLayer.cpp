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

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto sprite = Sprite::create(BACKGROUND_SKYLINE);
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

void TowerLayer::createObject(OT::OTType t, Vec2 location)
{
	StructureUserData *ud;

	switch(t){
	case OT::SOFFICE :
		//TODO: randomize the kind of office spawned
		ud= new StructureUserData();
		ud->type = 1;
		ud->varient = 2;
		ud->startFrame = 0;
		ud->numFrames = OFFICE_1; 
		ud->format = SPRITE_OFFICE_FORMAT;
		this->createSprite(ud,SPRITE_OFFICE_PLIST, SPRITE_OFFICE_SHEET, location);
		break;
	default:
		break;
	}
}

void TowerLayer::createSprite(StructureUserData* ud, std::string plist, std::string sheet, cocos2d::Vec2 location)
{
	char frame[50] = {0};

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(plist,sheet);
    
	sprintf(frame, ud->format.c_str(), ud->type, ud->varient, ud->startFrame);

	CCLOG("Starting Frame: %s",frame);

    Sprite* _sprite1 = Sprite::createWithSpriteFrameName(frame);
    _sprite1->setPosition( location );
	_sprite1->setTag(OT::hashPoint(OT::OTPoint(location.x,location.y)));
	_sprite1->setUserData(ud);
    addChild(_sprite1,100);
    
    Vector<SpriteFrame*> animFrames(15);
    
	assert(ud->numFrames >= 1);

    char str[100] = {0};
	for(int i = 1; i < ud->numFrames-1; i++)
    {
		sprintf(str, ud->format.c_str(), ud->type, ud->varient, i);
        auto frame = cache->getSpriteFrameByName( str );
        animFrames.pushBack(frame);
    }
    
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
    _sprite1->runAction( RepeatForever::create( Animate::create(animation) ) );
}

void TowerLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    DrawPrimitives::drawSolidRect(Vec2(0,0),Vec2(10,10),Color4F::GRAY);//for debugging, draw a point at (0,0)
}
#include "TowerLayer.h"

USING_NS_CC;

TowerLayer::~TowerLayer()
{
	
    for(std::vector<int>::iterator it = tagRegistry.begin(); it != tagRegistry.end(); ++it)
	{
		delete (StructureUserData*)this->getChildByTag(*it)->getUserData();
	}

    tagRegistry.clear();
}

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
    
    CCLOG("DID INIT");
    
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
	case OT::OTOFFICE :
		//TODO: randomize the kind of office spawned
		ud= new StructureUserData();
		ud->type = 1;
		ud->varient = 2;
		ud->startFrame = 0;
		ud->numFrames = OFFICE_1; 
		ud->format = SPRITE_OFFICE_FORMAT;
		this->createSprite(ud,SPRITE_OFFICE_PLIST, SPRITE_OFFICE_SHEET, location);
        //debugLocation(location, t);
		break;
	default:
		break;
	}
}

//void TowerLayer::debugLocation(Vec2 location,OT::OTType type)
//{
//    debug d;
//    
//    float originX = location.x - OT::OpenTowerManager::sharedTowerManager()->getSizeForStructure(type).width/2;
//	float originY = location.y - OT::OpenTowerManager::sharedTowerManager()->getSizeForStructure(type).height/2;
//    float maxX = location.x + OT::OpenTowerManager::sharedTowerManager()->getSizeForStructure(type).width/2;
//    float maxY = location.y + OT::OpenTowerManager::sharedTowerManager()->getSizeForStructure(type).height/2;
//    
//    d.origin=Vec2(originX,originY);
//    d.max=Vec2(maxX,maxY);
//    
//    debugData.push_back(d);
//}

void TowerLayer::createSprite(StructureUserData* ud, std::string plist, std::string sheet, cocos2d::Vec2 location)
{
    //we can NOT add duplicate hashes!
    if(std::find(tagRegistry.begin(), tagRegistry.end(), OT::OpenTowerManager::sharedTowerManager()->hashPoint(OT::OTPoint(location.x,location.y))) != tagRegistry.end())
        return;
    
	char frame[50] = {0};

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(plist,sheet);
    
    sprintf(frame, ud->format.c_str(), ud->type, ud->varient, ud->startFrame);

    Sprite* _sprite1 = Sprite::createWithSpriteFrameName(frame);
    _sprite1->setPosition( location );
	_sprite1->setTag(OT::OpenTowerManager::sharedTowerManager()->hashPoint(OT::OTPoint(location.x,location.y)));
	_sprite1->setUserData(ud);
    addChild(_sprite1,100);
    
    this->tagRegistry.push_back(OT::OpenTowerManager::sharedTowerManager()->hashPoint(OT::OTPoint(location.x,location.y)));
    
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
    DrawPrimitives::drawSolidRect(Vec2(0,0),Vec2(10,10),Color4F::GRAY);//draw a point at (0,0)
    
    //for(std::vector<debug>::iterator it = debugData.begin(); it != debugData.end(); ++it)
	//{
	//	DrawPrimitives::drawSolidRect((*it).origin,(*it).max,Color4F::GRAY);//have opengl draw the structure, instead of sprite
	//}
    
}


#include "TowerScene.h"
#include "MainMenuScene.h"
USING_NS_CC;

Scene* Tower::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Tower::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Tower::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto tlistener = EventListenerMouse::create();
	tlistener->onMouseMove = CC_CALLBACK_1(Tower::onMouseMove, this);
	tlistener->onMouseDown = CC_CALLBACK_1(Tower::onMouseDown, this);
	tlistener->onMouseUp = CC_CALLBACK_1(Tower::onMouseUp, this);
	tlistener->onMouseScroll = CC_CALLBACK_1(Tower::onMouseScroll, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(tlistener, this);


    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(Tower::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);


	CCTMXTiledMap* map = CCTMXTiledMap::create("tower.tmx");
    this->addChild(map, 0, 1);
    
    return true;
}

void Tower::onMouseMove(cocos2d::Event* _event)
{
	CCLOG("MOVE");
	EventMouse* e = (EventMouse*)_event;
}
void Tower::onMouseUp(cocos2d::Event* _event)
{
	CCLOG("CLICK UP");
	EventMouse* e = (EventMouse*)_event;
}
void Tower::onMouseDown(cocos2d::Event* _event)
{
	CCLOG("CLICK DOWN");
	EventMouse* e = (EventMouse*)_event;
}
void Tower::onMouseScroll(cocos2d::Event* _event)
{
	CCLOG("SCROLL");
	EventMouse* e = (EventMouse*)_event;
}

void Tower::menuCloseCallback(Ref* pSender)
{ 
	CCScene *pScene = MainMenu::createScene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

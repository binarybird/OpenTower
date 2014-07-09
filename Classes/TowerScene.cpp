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
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto pCloseItem = MenuItemImage::create("CloseNormal.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(Tower::menuCloseCallback,this));
    
	pCloseItem->setPosition(Vec2(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,origin.y + pCloseItem->getContentSize().height/2));

    Menu* pMenu = Menu::create(pCloseItem, NULL);
    pMenu->setPosition(Vec2::ZERO);
    this->addChild(pMenu, 1);
    
    this->initMouse();
    this->scheduleUpdate();
    
    return true;
}

void Tower::update(float delta){
    
}

void Tower::initMouse()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    auto tlistener = EventListenerMouse::create();
	tlistener->onMouseMove = CC_CALLBACK_1(Tower::onMouseMove, this);
	tlistener->onMouseDown = CC_CALLBACK_1(Tower::onMouseDown, this);
	tlistener->onMouseUp = CC_CALLBACK_1(Tower::onMouseUp, this);
	tlistener->onMouseScroll = CC_CALLBACK_1(Tower::onMouseScroll, this);
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(tlistener, this);
    
    _currentStructure = SOFFICE;//tmp - I only have the office structure made atm
    _mouseYOffset = visibleSize.height;
    _currentStructureSize = getSizeForStructure(_currentStructure);
    
    _mouseLayer = MouseLayer::create();
    _mouseLayer->setStructureSize(_currentStructureSize);
    this->addChild(_mouseLayer, 10);
}

void Tower::onMouseMove(cocos2d::Event* _event)
{
	//CCLOG("MOVE");
	EventMouse* e = (EventMouse*)_event;
    
    _mouseLayer->setPosition(Vec2(e->getCursorX()-_currentStructureSize.width/2,
                                  _mouseYOffset + e->getCursorY() - _currentStructureSize.height/2));
}
void Tower::onMouseUp(cocos2d::Event* _event)
{
	//CCLOG("CLICK UP");
	EventMouse* e = (EventMouse*)_event;
    
    /* *PROTO*
     
     auto manager OpenTowerManager::sharedManager()
     
     position = create sprite
     
     manager->createStructure(type, positin)
     
     */
}
void Tower::onMouseDown(cocos2d::Event* _event)
{
	//CCLOG("CLICK DOWN");
	EventMouse* e = (EventMouse*)_event;
}
void Tower::onMouseScroll(cocos2d::Event* _event)
{
	//CCLOG("SCROLL");
	EventMouse* e = (EventMouse*)_event;
}

void Tower::menuCloseCallback(Ref* pSender)
{ 
	Scene *pScene = MainMenu::createScene();
    Director::sharedDirector()->replaceScene(pScene);
}

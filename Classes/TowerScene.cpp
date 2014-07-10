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

	_isMovingToolPanal = false;
	_mouseYOffset = visibleSize.height;

	this->initToolPanal();
	this->initTower();
    this->initMouse();
    this->scheduleUpdate();

	//this->runAction(CCFollow::create(_mouseLayer,Rect::ZERO));
    
    return true;
}

void Tower::update(float delta){
    
}



void Tower::initToolPanal()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	_toolPanalLayer = ToolPanalLayer::create();
	_toolPanalLayer->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(_toolPanalLayer, 9);
}

void Tower::initTower()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	_towerLayer = TowerLayer::create();
	_towerLayer->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(_towerLayer, 5);
}

void Tower::initMouse()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto tlistener = EventListenerMouse::create();
	tlistener->onMouseMove = CC_CALLBACK_1(Tower::onMouseMove, this);
	tlistener->onMouseDown = CC_CALLBACK_1(Tower::onMouseDown, this);
	tlistener->onMouseUp = CC_CALLBACK_1(Tower::onMouseUp, this);
	tlistener->onMouseScroll = CC_CALLBACK_1(Tower::onMouseScroll, this);
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(tlistener, this);
    
    _currentStructure = SOFFICE;//tmp - I only have the office structure made atm
    
    _currentStructureSize = getSizeForStructure(_currentStructure);
    
    _mouseLayer = MouseLayer::create();
    _mouseLayer->setStructureSize(_currentStructureSize);
	_mouseLayer->setPosition(visibleSize.width,visibleSize.height);
    this->addChild(_mouseLayer, 10);
}

void Tower::toolPanalCallback(CCObject *sender)
{
	//_currentStructure = type;
	//_currentStructureSize = getSizeForStructure(_currentStructure);
}

void Tower::onMouseMove(cocos2d::Event* _event)
{
	EventMouse* e = (EventMouse*)_event;

	if(_isMovingToolPanal == true)
	{
		Vec2 tPP = _toolPanalLayer->getPosition();
		float mPPY = e->getCursorY();
		float mPPX = e->getCursorX();
		mPPY=mPPY+_mouseYOffset;

		_toolPanalLayer->setPosition(Vec2(mPPX-_windowOffsetX,mPPY-_windowOffsetY));
	}


    _mouseLayer->setPosition(e->getCursorX()-_currentStructureSize.width/2, _mouseYOffset + e->getCursorY() - _currentStructureSize.height/2);
}
void Tower::onMouseUp(cocos2d::Event* _event)
{

	EventMouse* e = (EventMouse*)_event;

	if(_isMovingToolPanal == true)
	{
		_isMovingToolPanal = false;
	}
	
    /* *PROTO*
     
     auto manager OpenTowerManager::sharedManager()
     
     position = create sprite
     
     manager->createStructure(type, positin)
     
     */
}
void Tower::onMouseDown(cocos2d::Event* _event)
{
	EventMouse* e = (EventMouse*)_event;

	Vec2 tPP = _toolPanalLayer->getPosition();
	float mPPY = e->getCursorY();
	float mPPX = e->getCursorX();

	mPPY=mPPY+_mouseYOffset;

	if(mPPY < tPP.y + TOOLPANAL_HEIGHT+2 && mPPY > tPP.y-2)
		if(mPPX > tPP.x -2 && mPPX < tPP.x + TOOLPANAL_WIDTH+2){
			_isMovingToolPanal = true;
			
			_windowOffsetX = mPPX - tPP.x;
			_windowOffsetY = mPPY - tPP.y;
		}


}
void Tower::onMouseScroll(cocos2d::Event* _event)
{
	EventMouse* e = (EventMouse*)_event;

	_towerLayer->runAction(MoveBy::create(1/SCROLL_SPEED ,Vec2((-1*e->getScrollX())*SCROLL_MULTIPLIER, e->getScrollY()*SCROLL_MULTIPLIER)));
}

void Tower::menuCloseCallback(Ref* pSender)
{ 
	Scene *pScene = MainMenu::createScene();
    Director::sharedDirector()->replaceScene(pScene);
}

#include "TowerScene.h"

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

    auto pCloseItem = MenuItemImage::create(UI_CLOSE_N,
                                            UI_CLOSE_S,
                                            CC_CALLBACK_1(Tower::menuCloseCallback,this));
	pCloseItem->setPosition(Vec2(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,origin.y + pCloseItem->getContentSize().height/2));

    Menu* pMenu = Menu::create(pCloseItem, NULL);
    pMenu->setPosition(Vec2::ZERO);
    this->addChild(pMenu, 1);
	_isMovingToolPanal = false;
	_mouseYOffset = visibleSize.height;
    isClosing = false;

	this->initToolPanal();
	this->initTower();
    this->initMouse();
    this->scheduleUpdate();

	this->load();
    
    return true;
}

void Tower::update(float delta)
{
	OT::OpenTowerManager::sharedTowerManager()->update(delta);
}

void Tower::createStructure(Vec2 position)
{
    Vec2 ret = this->convertFromTowerSceneToTowerLayer(position);
    
	bool sucess = OT::OpenTowerManager::sharedTowerManager()->addStructure(_currentStructure, OT::OTPoint(ret.x,ret.y));

	if(sucess){
		_towerLayer->createObject(_currentStructure, ret);
        CCLOG("PLACED (%f,%f) a %i",position.x,position.y,_currentStructure);
    }
	else
		CCLOG("--CANT PLACE--");
	
}

cocos2d::Vec2 Tower::convertFromTowerSceneToTowerLayer(Vec2 mLoc)
{
    Vec2 lLoc = _towerLayer->getPosition();

    float angle = CC_RADIANS_TO_DEGREES(lLoc.getAngle());

    if(angle >= 0 && angle <= 90)
    {
        return (mLoc - lLoc);
    }
    else if(angle > 90 && angle <= 180)
    {
        return (mLoc+Vec2(abs(lLoc.x), -lLoc.y));
    }
    else if(angle >= -180 && angle <= -270)
    {
		return (mLoc + lLoc);
    }
    else if (angle > -270 && angle < 0)
    {
        return (mLoc - lLoc);
    }
        
	return Vec2::ZERO;
}

void Tower::initToolPanal()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	_toolPanalLayer = ToolPanalLayer::create();
	_toolPanalLayer->setTowerScene(this);
	_toolPanalLayer->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(_toolPanalLayer, 9);
}

void Tower::initTower()
{
	_towerLayer = TowerLayer::create();
	_towerLayer->setPosition(Vec2::ZERO);
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
    
    _currentStructure = OT::OTOFFICE;
	OT::OTSize tmp = OT::OpenTowerManager::sharedTowerManager()->getSizeForStructure(_currentStructure);
	_currentStructureSize = cocos2d::Size(tmp.width,tmp.height);
    
    _mouseLayer = MouseLayer::create();
    _mouseLayer->setStructureSize(_currentStructureSize);
	_mouseLayer->setPosition(visibleSize.width,visibleSize.height);
    this->addChild(_mouseLayer, 10);
}

void Tower::load()
{
    //TODO - THE OBJECT TYPE IS INCORRECT - ITS OF ITS BASE CLASS
    //TODO - THE HASHED POINT VECTOR IN TOWER LAYER NEEDS POPULATING
	if(OT::OpenTowerManager::sharedTowerManager()->load("lol","lol")){

		int structureCount = OT::OpenTowerManager::sharedTowerManager()->getStructureCount();

		for(int i=0;i<structureCount;i++)
		{
            //need to identify class, its not a structure!
			OT::Structure::OTStructure* stru = OT::OpenTowerManager::sharedTowerManager()->getStructureAtIndex(i);
            
            //CCLOG("TYPE %d, LOC: (%f,%f)",stru->getClassType(),stru->x,stru->y);
			 
			_towerLayer->createObject(stru->getClassType(), Vec2(stru->x,stru->y));//stru->classType
		}
	}
	else{
		CCLOG("LOAD ERROR");
	}
}

void Tower::toolPanalCallback(OT::OTType type)
{
	_currentStructure = type;
	_currentStructure = OT::OTOFFICE;
	OT::OTSize tmp = OT::OpenTowerManager::sharedTowerManager()->getSizeForStructure(_currentStructure);
	_currentStructureSize = cocos2d::Size(tmp.width,tmp.height);
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
    if(isClosing == true)
        return;
    
	EventMouse* e = (EventMouse*)_event;

	if(_isMovingToolPanal == true)
	{
		_isMovingToolPanal = false;

		return; //if we are moving a window, we dont want to build things!
	}

	float mPPY = e->getCursorY()+_mouseYOffset;
	float mPPX = e->getCursorX();
	Vec2 towerP = _towerLayer->getPosition();
    
    this->createStructure(Vec2(mPPX,mPPY));
    
}

void Tower::onMouseDown(cocos2d::Event* _event)
{
    if(isClosing == true)
        return;
    
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
    isClosing = true;
    
	if(OT::OpenTowerManager::sharedTowerManager()->save("lol","lol"));
        OT::OpenTowerManager::sharedTowerManager()->cleanup();

	Scene *pScene = MainMenu::createScene();
    Director::sharedDirector()->replaceScene(pScene);
}

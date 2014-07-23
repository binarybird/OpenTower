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
	pCloseItem->setVertexZ(Z_INGAMEEXIT_LAYER);

    Menu* pMenu = Menu::create(pCloseItem, NULL);
    pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, Z_INGAMEEXIT_LAYER);
    
	_isMovingToolPanal = false;
	_mouseYOffset = visibleSize.height;
    _isClosing = false;
    _returnFromSave = false;

	this->initToolPanal();
	this->initTower();
    this->initMouse();
    this->scheduleUpdate();
    
    return true;
}

void Tower::onEnter()
{
    Layer::onEnter();
    if(OT::OpenTowerManager::sharedTowerManager()->didLoadTower)
        this->load();
}

void Tower::update(float delta)
{
	OT::OpenTowerManager::sharedTowerManager()->update(delta);
}

void Tower::createStructure(Vec2 position)
{
    Vec2 ret = this->convertFromTowerSceneToTowerLayer(position);
    
    OT::OTPoint correctedPosition = OT::OpenTowerManager::sharedTowerManager()->addStructure(_currentStructure, OT::OTPoint(ret.x,ret.y));
    
    if(correctedPosition != OT::OTPoint::ZERO){
        _towerLayer->createObject(_currentStructure, Vec2(correctedPosition.x,correctedPosition.y));
    }else{
        CCLOG("--CANT PLACE--");
    }
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

void Tower::toolPanalCallback(OT::OTType type)
{
	_currentStructure = type;
	
	OT::OTSize tmp = OT::OpenTowerManager::sharedTowerManager()->getSizeForStructure(_currentStructure);

	_mouseLayer->setStructureSize(Size(tmp.width,tmp.height));
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
    if(_isClosing == true || _returnFromSave == true)
    {
        _returnFromSave = false;
        return;// if we are pressing the close button, we dont want to build things!
    }
    
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
    if(_isClosing == true || _returnFromSave == true)
        return;// if we are pressing the close button, we dont want to build things!
    
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
    if(_isClosing == true || _returnFromSave == true)
        return;// if we are pressing the close button, we dont want to build things!
    
	EventMouse* e = (EventMouse*)_event;

	_towerLayer->runAction(MoveBy::create(1/SCROLL_SPEED ,Vec2((-1*e->getScrollX())*SCROLL_MULTIPLIER, e->getScrollY()*SCROLL_MULTIPLIER)));
}

void Tower::menuCloseCallback(Ref* pSender)
{
    _isClosing = true;
    
    this->closeLoadLayer();
    
    bool didSave = false;
    
        //PRE SAVE CHECKING
        if(OT::OpenTowerManager::sharedTowerManager()->loadTowerPath.length() == 0)
        {
            Size visibleSize = Director::getInstance()->getVisibleSize();
            
            SaveTowerLayer* loadLayer = SaveTowerLayer::create();
            loadLayer->setMainMenu(this);
            loadLayer->setName("savelayer");
            
            loadLayer->setPosition(visibleSize.width/2 - LOADTOWER_DIALOG_WIDTH/2, visibleSize.height/2 - LOADTOWER_DIALOG_HEIGHT/2);
            
            this->addChild(loadLayer,7);
            
            return;
        }
        
        //SAVE
        didSave = this->save();
    
        //POST SAVE CHECKING
        if(!didSave)
        {
            this->cancle();
            
            MessageBox("Unable To Save!","Alert");
            
            return;
        }

    this->close();
}

void Tower::cancle()
{
    CCLOG("Cancled save");
    this->closeLoadLayer();
    _isClosing = false;
    _returnFromSave = true;
}

void Tower::close()
{
    CCLOG("Closing");
    OT::OpenTowerManager::sharedTowerManager()->cleanup();
    this->removeAllChildrenWithCleanup(true);
    
    Scene *pScene = MainMenu::createScene();
    Director::sharedDirector()->replaceScene(pScene);
}

void Tower::closeLoadLayer()
{
    if(this->getChildByName("savelayer"))
    {
        this->removeChildByName("savelayer");
    }
}

bool Tower::save()
{
    CCLOG("Saving");
    bool ret = false;
    
	if(OT::OpenTowerManager::sharedTowerManager()->save())
    {
        OT::OpenTowerManager::sharedTowerManager()->cleanup();
        ret = true;
    }
    else
    {
        std::cout<<"Cannot Save For Some Reason!"<<std::endl;
    }
    
    return ret;
}

bool Tower::load()
{
    bool ret = false;
    
    if(_towerLayer == NULL)
        return false;
    
	if(OT::OpenTowerManager::sharedTowerManager()->load())
    {
		int structureCount = OT::OpenTowerManager::sharedTowerManager()->getStructureCount();
        
		for(int i=0;i<structureCount;i++)
		{
			OT::Structure::OTStructure* stru = OT::OpenTowerManager::sharedTowerManager()->getStructureAtIndex(i);
            
			_towerLayer->createObject(stru->getClassType(), Vec2(stru->x,stru->y));

		}
        ret = true;
	}
	else{
		CCLOG("LOAD ERROR");
	}
    
    return ret;
}
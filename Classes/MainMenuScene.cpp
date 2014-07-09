#include "MainMenuScene.h"
#include "TowerScene.h"
USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    CCMenuItemImage *pTowerItem = CCMenuItemImage::create(
                                        "start.png",
                                        "start.png",
                                        this,
                                        menu_selector(MainMenu::menuOpenTowerCallback));
    
	pTowerItem->setPosition(ccp(origin.x + visibleSize.width/2 - pTowerItem->getContentSize().width, origin.y + visibleSize.height/2));


	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(MainMenu::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width/2 - pTowerItem->getContentSize().width  , origin.y + visibleSize.height/2 -  pTowerItem->getContentSize().height));

    CCMenu* pMenu = CCMenu::create(pCloseItem,pTowerItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

	CCLabelTTF* pLabelNewTower = CCLabelTTF::create("New Tower", "Arial", 24);
	pLabelNewTower->setPosition(ccp(origin.x + visibleSize.width/2 + pLabelNewTower->getContentSize().width/2, origin.y + visibleSize.height/2));
    this->addChild(pLabelNewTower, 1);

	CCLabelTTF* pLabelQuit = CCLabelTTF::create("Close", "Arial", 24);
	pLabelQuit->setPosition(ccp(origin.x + visibleSize.width/2 + pLabelQuit->getContentSize().width/2  , origin.y + visibleSize.height/2 -  pTowerItem->getContentSize().height));
    this->addChild(pLabelQuit, 1);
    
    CCLabelTTF* pLabel = CCLabelTTF::create("OpenTower", "Arial", 24);
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height - pLabel->getContentSize().height));
    this->addChild(pLabel, 1);
    
    return true;
}

void MainMenu::menuOpenTowerCallback(Ref* pSender)
{
	CCScene *pScene = Tower::createScene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void MainMenu::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

#include "MainMenuScene.h"
#include "MainTowerScene.h"
USING_NS_CC;

CCScene* MainMenu::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainMenu *layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
enum
{
    kTagTileMap = 1,
};

bool MainMenu::init()
{

    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();


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



void MainMenu::menuOpenTowerCallback(CCObject* pSender)
{
	CCScene *pScene = MainTowerScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void MainMenu::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

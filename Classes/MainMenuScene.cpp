#include "MainMenuScene.h"

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

    auto pTowerItem = CCMenuItemImage::create(
                                        "start.png",
                                        "start.png",
                                        CC_CALLBACK_1(MainMenu::menuOpenTowerCallback,this));
    
	pTowerItem->setPosition(Vec2(origin.x + visibleSize.width/2 - pTowerItem->getContentSize().width, origin.y + visibleSize.height/2));


    auto pCloseItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainMenu::menuCloseCallback,this));
    
    pCloseItem->setPosition(Vec2(origin.x + visibleSize.width/2 - pTowerItem->getContentSize().width  , origin.y + visibleSize.height/2 -  pTowerItem->getContentSize().height));
    
    
    Menu* pMenu = Menu::create(pCloseItem,pTowerItem, NULL);
    pMenu->setPosition(Vec2::ZERO);
    this->addChild(pMenu, 1);

	auto pLabelNewTower = LabelTTF::create("New Tower", "Arial", 24);
	pLabelNewTower->setPosition(Vec2(origin.x + visibleSize.width/2 + pLabelNewTower->getContentSize().width/2, origin.y + visibleSize.height/2));
    this->addChild(pLabelNewTower, 1);

	auto pLabelQuit = LabelTTF::create("Close", "Arial", 24);
	pLabelQuit->setPosition(Vec2(origin.x + visibleSize.width/2 + pLabelQuit->getContentSize().width/2  , origin.y + visibleSize.height/2 -  pTowerItem->getContentSize().height));
    this->addChild(pLabelQuit, 1);
    
    auto label = LabelTTF::create("OpenTower!", "Arial", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
    
    return true;
}

void MainMenu::menuOpenTowerCallback(Ref* pSender)
{
	Scene *pScene = Tower::createScene();
    Director::sharedDirector()->replaceScene(pScene);
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

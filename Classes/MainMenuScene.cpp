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
    
    buttonLock = false;

    auto pTowerItem = CCMenuItemImage::create(
                                        UI_PLAYBUTTON_N,
                                        UI_PLAYBUTTON_S,
                                        CC_CALLBACK_1(MainMenu::menuOpenTowerCallback,this));
    
	pTowerItem->setPosition(Vec2(origin.x + visibleSize.width/2 - pTowerItem->getContentSize().width, visibleSize.height/2));
    
    //******************************
    
    auto pLoadTowerItem = CCMenuItemImage::create(
                                                  UI_PLAYBUTTON_N,
                                                  UI_PLAYBUTTON_S,
                                                  CC_CALLBACK_1(MainMenu::menuLoadTowerCallback,this));
    
	pLoadTowerItem->setPosition(Vec2(origin.x + visibleSize.width/2 - pTowerItem->getContentSize().width  , visibleSize.height/2 -  pTowerItem->getContentSize().height));
    
    //******************************
    
    auto pMultiplayerItem = CCMenuItemImage::create(
                                                  UI_PLAYBUTTON_N,
                                                  UI_PLAYBUTTON_S,
                                                  CC_CALLBACK_1(MainMenu::menuMultiplayerCallback,this));
    
	pMultiplayerItem->setPosition(Vec2(origin.x + visibleSize.width/2 - pTowerItem->getContentSize().width  , visibleSize.height/2 -  pTowerItem->getContentSize().height*2));
    
    //******************************
    
    auto pOptionsItem = CCMenuItemImage::create(
                                                  UI_PLAYBUTTON_N,
                                                  UI_PLAYBUTTON_S,
                                                  CC_CALLBACK_1(MainMenu::menuOptionsCallback,this));
    
	pOptionsItem->setPosition(Vec2(origin.x + visibleSize.width/2 - pTowerItem->getContentSize().width  , visibleSize.height/2 -  pTowerItem->getContentSize().height*3));

    //******************************

    auto pCloseItem = MenuItemImage::create(
										   UI_CLOSE_N,
                                           UI_CLOSE_S,
                                           CC_CALLBACK_1(MainMenu::menuCloseCallback,this));
    
    pCloseItem->setPosition(Vec2(origin.x + visibleSize.width/2 - pTowerItem->getContentSize().width  , visibleSize.height/2 -  pTowerItem->getContentSize().height*4));
    
    
    Menu* pMenu = Menu::create(pCloseItem,pTowerItem,pLoadTowerItem,pMultiplayerItem,pOptionsItem, NULL);
    pMenu->setPosition(Vec2::ZERO);
    this->addChild(pMenu, Z_GENERIC_LAYER);

	auto pLabelNewTower = LabelTTF::create(MAINMENU_NEWTOWER, GLOBAL_FONT_TYPE, 24);
	pLabelNewTower->setPosition(Vec2(origin.x + visibleSize.width/2 + pLabelNewTower->getContentSize().width/2, origin.y + visibleSize.height/2));
    this->addChild(pLabelNewTower, Z_GENERIC_LAYER);
    
    auto pLabelLoad = LabelTTF::create(MAINMENU_LOADTOWER, GLOBAL_FONT_TYPE, 24);
	pLabelLoad->setPosition(Vec2(origin.x + visibleSize.width/2 + pLabelLoad->getContentSize().width/2  , origin.y + visibleSize.height/2 -  pTowerItem->getContentSize().height));
    this->addChild(pLabelLoad, Z_GENERIC_LAYER);
    
    auto pLabelMultiplayer = LabelTTF::create(MAINMENU_MULTIPLAYER, GLOBAL_FONT_TYPE, 24);
	pLabelMultiplayer->setPosition(Vec2(origin.x + visibleSize.width/2 + pLabelMultiplayer->getContentSize().width/2  , origin.y + visibleSize.height/2 -  pTowerItem->getContentSize().height*2));
    this->addChild(pLabelMultiplayer, Z_GENERIC_LAYER);
    
    auto pLabelOptions = LabelTTF::create(MAINMENU_OPTIONS, GLOBAL_FONT_TYPE, 24);
	pLabelOptions->setPosition(Vec2(origin.x + visibleSize.width/2 + pLabelOptions->getContentSize().width/2  , origin.y + visibleSize.height/2 -  pTowerItem->getContentSize().height*3));
    this->addChild(pLabelOptions, Z_GENERIC_LAYER);

	auto pLabelQuit = LabelTTF::create(MAINMENU_CLOSE, GLOBAL_FONT_TYPE, 24);
	pLabelQuit->setPosition(Vec2(origin.x + visibleSize.width/2 + pLabelQuit->getContentSize().width/2  , origin.y + visibleSize.height/2 -  pTowerItem->getContentSize().height*4));
    this->addChild(pLabelQuit, Z_GENERIC_LAYER);
    
    auto label = LabelTTF::create(GAMENAME, GLOBAL_FONT_TYPE, 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, Z_GENERIC_LAYER);
    
    return true;
}

void MainMenu::closeLoadLayer()
{
    this->removeChildByName("loadlayer");
}

void MainMenu::menuMultiplayerCallback(cocos2d::Ref* pSender)
{
    MessageBox("Multiplayer Not in yet!","Alert");
}

void MainMenu::menuOptionsCallback(cocos2d::Ref* pSender)
{
    MessageBox("Options not in yet!","Alert");
}

void MainMenu::menuOpenTowerCallback(Ref* pSender)
{
    if(buttonLock == false)
    {
        this->closeLoadLayer();
        buttonLock = true;
        Scene *pScene = Tower::createScene();
        Director::sharedDirector()->replaceScene(pScene);
    }
}

void MainMenu::menuLoadTowerCallback(cocos2d::Ref* pSender)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    LoadTowerLayer* loadLayer = LoadTowerLayer::create();
    loadLayer->setMainMenu(this);
    loadLayer->setName("loadlayer");

    loadLayer->setPosition(visibleSize.width/2 - LOADTOWER_DIALOG_WIDTH/2, visibleSize.height/2 - LOADTOWER_DIALOG_HEIGHT/2);
    
    this->addChild(loadLayer,7);
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

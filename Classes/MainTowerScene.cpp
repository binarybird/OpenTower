#include "MainTowerScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

enum
{
    kTagTileMap = 1,
};

CCScene* MainTowerScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainTowerScene *layer = MainTowerScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


bool MainTowerScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(MainTowerScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);


	CCTMXTiledMap* map = CCTMXTiledMap::create("tower.tmx");
    this->addChild(map, 0, kTagTileMap);
	
	//schedule(schedule_selector(MainTowerScene::generateMap), 0.2f);

    return true;
}

void MainTowerScene::generateMap(){

	CCTMXTiledMap* map = (CCTMXTiledMap*) getChildByTag(kTagTileMap);
    CCTMXLayer* layer;
    layer = map->layerNamed("GreenLayer");

    CCSize ls = layer->getLayerSize();
    for (unsigned int y = 0; y < ls.height; y++) 
    {
        for (unsigned int x = 0; x < ls.width; x++) 
        {
            layer->setTileGID(1, ccp( x, y ) );

        }
    } 
}


void MainTowerScene::menuCloseCallback(CCObject* pSender)
{
	CCScene *pScene = MainMenu::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

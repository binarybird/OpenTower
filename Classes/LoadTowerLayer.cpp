#include "LoadTowerLayer.h"
#include "MainMenuScene.h"


USING_NS_CC;

bool LoadTowerLayer::init(){
    
    if ( !Layer::init() )
    {
        return false;
    }
    
	CCDirector::getInstance()->setDepthTest(true);
	this->setVertexZ(8);
    
    auto pCloseItem = MenuItemImage::create(
                                            UI_CLOSE_N,
                                            UI_CLOSE_S,
                                            CC_CALLBACK_1(LoadTowerLayer::menuCloseCallback,this));
    
//    pCloseItem->setPosition(Vec2(LOADTOWER_DIALOG_WIDTH - pCloseItem->getContentSize().width/2, pCloseItem->getContentSize().height/2));
//    
//    auto m_pEditName = CCEditBox::create(editBoxSize, CCScale9Sprite::create("extensions/green_edit.png"));
//    
//    m_pEditName->setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height*3/4));
//    
//    m_pEditName->setFontColor(ccRED);
//    
//    m_pEditName->setPlaceHolder("Name:");
//    
//    m_pEditName->setMaxLength(8);
//    
//    m_pEditName->setReturnType(kKeyboardReturnTypeDone);
//    
//    m_pEditName->setDelegate(this);
//    
//    addChild(m_pEditName);
    
    Menu* pMenu = Menu::create(pCloseItem, NULL);
    pMenu->setPosition(Vec2::ZERO);
    this->addChild(pMenu, 1);
    
    

    return true;
}

void LoadTowerLayer::setMainMenu(cocos2d::Layer* scene)
{
    this->_menu = scene;
}

void LoadTowerLayer::menuCloseCallback(cocos2d::Ref* pSender)
{
    ((MainMenu*)_menu)->closeLoadLayer();
}

void LoadTowerLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
	DrawPrimitives::drawSolidRect(Vec2(0,0),Vec2(LOADTOWER_DIALOG_WIDTH,LOADTOWER_DIALOG_HEIGHT),Color4F::GRAY);
	DrawPrimitives::setDrawColor4B(0xff,0xff,0xff,0xff);
	DrawPrimitives::drawRect(Vec2(-2,-2),Vec2(LOADTOWER_DIALOG_WIDTH+2,LOADTOWER_DIALOG_HEIGHT+2));
}
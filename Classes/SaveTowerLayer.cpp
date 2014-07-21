#include "SaveTowerLayer.h"
#include "TowerScene.h"

USING_NS_CC;
USING_NS_CC_EXT;


bool SaveTowerLayer::init(){
    
    if ( !Layer::init() )
    {
        return false;
    }
    
	CCDirector::getInstance()->setDepthTest(true);
	this->setVertexZ(20);

    
    auto pForceCloseItem = MenuItemFont::create(
                                            SAVEMENU_CLOSEWITHOUTSAVING,
                                            CC_CALLBACK_1(SaveTowerLayer::menuForceCloseCallback,this));
    pForceCloseItem->setFontSize(GLOBAL_FONT_SIZE);
    pForceCloseItem->setFontName(GLOBAL_FONT_TYPE);
    pForceCloseItem->setPosition(Vec2(SAVETOWER_DIALOG_WIDTH - pForceCloseItem->getContentSize().width/2, pForceCloseItem->getContentSize().height/2));
    
    auto pCancleItem = MenuItemFont::create(
                                            SAVEMENU_CANCLE,
                                                 CC_CALLBACK_1(SaveTowerLayer::menuCancleCallback,this));
    pCancleItem->setFontSize(GLOBAL_FONT_SIZE);
    pCancleItem->setFontName(GLOBAL_FONT_TYPE);
    pCancleItem->setPosition(Vec2(SAVETOWER_DIALOG_WIDTH/2, pForceCloseItem->getContentSize().height/2));
    
    auto pTowerItem = MenuItemFont::create(
                                           SAVEMENU_SAVE,
                                              CC_CALLBACK_1(SaveTowerLayer::menuOpenCallback,this));
    pTowerItem->setFontSize(GLOBAL_FONT_SIZE);
    pTowerItem->setFontName(GLOBAL_FONT_TYPE);
	pTowerItem->setPosition(Vec2(pTowerItem->getContentSize().width/2, pForceCloseItem->getContentSize().height/2));

	_savePath = EditBox::create(Size(SAVETOWER_TEXTBOX_WIDTH,SAVETOWER_TEXTBOX_HEIGHT), extension::Scale9Sprite::create(UI_TEXTFIELD));
    _savePath->setPosition(Vec2(LOADTOWER_DIALOG_WIDTH/2,LOADTOWER_DIALOG_HEIGHT/2));
    _savePath->setFontName(GLOBAL_FONT_TYPE);
    _savePath->setFontSize(25);
    _savePath->setFontColor(Color3B::RED);
    _savePath->setPlaceHolder("Save Path:");
    _savePath->setPlaceholderFontColor(Color3B::WHITE);
    _savePath->setMaxLength(50);
    _savePath->setReturnType(EditBox::KeyboardReturnType::DONE);
    _savePath->setDelegate(this);
    this->addChild(_savePath);
    
    Menu* pMenu = Menu::create(pTowerItem,pForceCloseItem,pCancleItem, NULL);
    pMenu->setPosition(Vec2::ZERO);
    this->addChild(pMenu, 1);
    
    return true;
}

void SaveTowerLayer::menuForceCloseCallback(cocos2d::Ref* pSender)
{
    ((Tower*)_menu)->close();
}

void SaveTowerLayer::menuCancleCallback(cocos2d::Ref* pSender)
{
    ((Tower*)_menu)->cancle();
}

void SaveTowerLayer::setMainMenu(cocos2d::Layer* scene)
{
    this->_menu = scene;
}

void SaveTowerLayer::menuOpenCallback(cocos2d::Ref* pSender)
{
    OT::OpenTowerManager::sharedTowerManager()->didLoadTower = true;
    OT::OpenTowerManager::sharedTowerManager()->loadTowerPath = _filePath;

    ((Tower*)_menu)->menuCloseCallback(NULL);
}

//void SaveTowerLayer::menuCloseCallback(cocos2d::Ref* pSender)
//{
//    ((Tower*)_menu)->closeLoadLayer();
//}

void SaveTowerLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
	DrawPrimitives::drawSolidRect(Vec2(0,0),Vec2(SAVETOWER_DIALOG_WIDTH,SAVETOWER_DIALOG_HEIGHT),Color4F::GRAY);
	DrawPrimitives::setDrawColor4B(0xff,0xff,0xff,0xff);
	DrawPrimitives::drawRect(Vec2(-2,-2),Vec2(SAVETOWER_DIALOG_WIDTH+2,SAVETOWER_DIALOG_HEIGHT+2));
}

void SaveTowerLayer::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox)
{
    log("editBox %p DidBegin !", editBox);
}

void SaveTowerLayer::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox)
{
    log("editBox %p DidEnd !", editBox);
}

void SaveTowerLayer::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text)
{
    log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
    
    this->_filePath = text;
}

void SaveTowerLayer::editBoxReturn(EditBox* editBox)
{
    log("editBox %p was returned !",editBox);
    
}
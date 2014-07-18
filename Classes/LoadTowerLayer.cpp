#include "LoadTowerLayer.h"
#include "MainMenuScene.h"

USING_NS_CC;
USING_NS_CC_EXT;


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
    pCloseItem->setPosition(Vec2(LOADTOWER_DIALOG_WIDTH - pCloseItem->getContentSize().width/2, pCloseItem->getContentSize().height/2));
    
    auto pTowerItem = MenuItemImage::create(
                                              UI_PLAYBUTTON_N,
                                              UI_PLAYBUTTON_S,
                                              CC_CALLBACK_1(LoadTowerLayer::menuOpenCallback,this));
	pTowerItem->setPosition(Vec2((LOADTOWER_DIALOG_WIDTH/2) - pTowerItem->getContentSize().width,LOADTOWER_DIALOG_HEIGHT/3));
    
    auto pLabelNewTower = LabelTTF::create(MAINMENU_LOADTOWER, GLOBAL_FONT_TYPE, 24);
	pLabelNewTower->setPosition(Vec2((LOADTOWER_DIALOG_WIDTH/2) + pTowerItem->getContentSize().width, LOADTOWER_DIALOG_HEIGHT/3));
    this->addChild(pLabelNewTower, 1);

	_savePath = EditBox::create(Size(LOADTOWER_TEXTBOX_WIDTH,LOADTOWER_TEXTBOX_HEIGHT), extension::Scale9Sprite::create(UI_TEXTFIELD));
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
    
    Menu* pMenu = Menu::create(pCloseItem,pTowerItem, NULL);
    pMenu->setPosition(Vec2::ZERO);
    this->addChild(pMenu, 1);
    
    

    return true;
}

void LoadTowerLayer::setMainMenu(cocos2d::Layer* scene)
{
    this->_menu = scene;
}

void LoadTowerLayer::menuOpenCallback(cocos2d::Ref* pSender)
{
    FileUtils *fileUtils = FileUtils::getInstance();
    bool pathVerified = fileUtils->isFileExist(_filePath);
    fileUtils->destroyInstance();
    
    CCLOG("PATH EXISTS %i",pathVerified);
    
    if(pathVerified)
        ((MainMenu*)_menu)->loadTowerWithPath(_filePath);
    else
        MessageBox("Invalid Save File","Alert");
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

void LoadTowerLayer::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox)
{
    log("editBox %p DidBegin !", editBox);
}

void LoadTowerLayer::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox)
{
    log("editBox %p DidEnd !", editBox);
}

void LoadTowerLayer::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text)
{
    log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
    
    this->_filePath = text;
}

void LoadTowerLayer::editBoxReturn(EditBox* editBox)
{
    log("editBox %p was returned !",editBox);
    
}
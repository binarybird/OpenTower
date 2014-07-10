#include "ToolPanalLayer.h"
#include "TowerScene.h"
USING_NS_CC;

bool ToolPanalLayer::init(){
    
    if ( !Layer::init() )
    {
        return false;
    }
    
	CCDirector::getInstance()->setDepthTest(true);
	this->setVertexZ(8);

	
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto pOfficeItem = MenuItemImage::create("UI/Icon-LargeOffice.png",
                                            "UI/Icon-LargeOffice.png",
											CC_CALLBACK_1(ToolPanalLayer::officeCallback,this));
	pOfficeItem->setPosition(Vec2(0+pOfficeItem->getContentSize().width/2,180 - pOfficeItem->getContentSize().height/2));
	Menu* pMenu = Menu::create(pOfficeItem, NULL);
	pMenu->setPosition(Vec2::ZERO);
    this->addChild(pMenu, 1);

    
    return true;
}
//void ToolPanalLayer::setTowerScene(Tower* tower)
//{
//	this->_tower = tower;
//}
void ToolPanalLayer::officeCallback(cocos2d::Ref* pSender)
{
	//_tower->toolPanalCallback(SOFFICE);
	
	/*CCObject* o = new CCObject();
	o->autorelease();

	CCCallFuncND *callBack = CCCallFuncO::create(Tower, callfuncO_selector(Tower::toolPanalCallback),o);*/

}

void ToolPanalLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
	DrawPrimitives::drawSolidRect(Vec2(0,0),Vec2(TOOLPANAL_WIDTH,TOOLPANAL_HEIGHT),Color4F::GRAY);
	DrawPrimitives::setDrawColor4B(0xff,0xff,0xff,0xff);
	DrawPrimitives::drawRect(Vec2(-2,-2),Vec2(TOOLPANAL_WIDTH+2,TOOLPANAL_HEIGHT+2));
}
#include "ToolPanalLayer.h"
#include "TowerScene.h"
USING_NS_CC;

bool ToolPanalLayer::init(){
    
    if ( !Layer::init() )
    {
        return false;
    }
    
	CCDirector::getInstance()->setDepthTest(true);
	this->setVertexZ(Z_TOOLPANEL_LAYER);

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto pOfficeItem = MenuItemImage::create(TOOLPANEL_ICONOFFICE_N_1,
                                             TOOLPANEL_ICONOFFICE_S_1,
                                             CC_CALLBACK_1(ToolPanalLayer::officeCallback,this));
	pOfficeItem->setPosition(Vec2(0+pOfficeItem->getContentSize().width/2,180 - pOfficeItem->getContentSize().height/2));
    
	Menu* pMenu = Menu::create(pOfficeItem, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, Z_GENERIC_LAYER);

    
    return true;
}
void ToolPanalLayer::setTowerScene(cocos2d::Layer* tower)
{
	this->_tower = tower;
}
void ToolPanalLayer::officeCallback(cocos2d::Ref* pSender)
{
	//had to hack Tower in this way - cannot include Tower.h in this class' header
	Tower* t = (Tower*)_tower;
	t->toolPanalCallback(OT::OTOFFICE);
}

void ToolPanalLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
	DrawPrimitives::drawSolidRect(Vec2(0,0),Vec2(TOOLPANAL_WIDTH,TOOLPANAL_HEIGHT),Color4F::GRAY);
	DrawPrimitives::setDrawColor4B(0xff,0xff,0xff,0xff);
	DrawPrimitives::drawRect(Vec2(-2,-2),Vec2(TOOLPANAL_WIDTH+2,TOOLPANAL_HEIGHT+2));
}
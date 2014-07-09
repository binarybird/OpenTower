#include "MouseLayer.h"

USING_NS_CC;

bool MouseLayer::init(){
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    _squareSize = Size(32,32);
    
    return true;
}

void MouseLayer::setStructureSize(cocos2d::Size size)
{
    _squareSize = size;
}

void MouseLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    DrawPrimitives::drawRect(
                             Vec2(origin.x,origin.y),
                             Vec2(origin.x+_squareSize.width, origin.y+_squareSize.height)
                             );
}
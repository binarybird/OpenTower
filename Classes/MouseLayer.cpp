#include "MouseLayer.h"

USING_NS_CC;

bool MouseLayer::init(){
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    _squareSize = Size(32,32);
	CCDirector::getInstance()->setDepthTest(true);
	this->setVertexZ(10);
    
    return true;
}

void MouseLayer::setStructureSize(cocos2d::Size size)
{
    _squareSize = size;
}

void MouseLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
	glEnable(GL_LINE_SMOOTH);

    DrawPrimitives::drawRect(
                             Vec2(0,0),
                             Vec2(_squareSize.width, _squareSize.height)
                             );
}
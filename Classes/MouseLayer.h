//
//  MouseLayer.h
//  OpenTower
//

#ifndef __OpenTower__MouseLayer__
#define __OpenTower__MouseLayer__

#include "cocos2d.h"

class MouseLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void setStructureSize(cocos2d::Size size);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MouseLayer);
protected:
    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags);
    cocos2d::Size _squareSize;
};

#endif /* defined(__OpenTower__MouseLayer__) */

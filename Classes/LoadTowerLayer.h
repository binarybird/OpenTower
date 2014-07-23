#ifndef __LoadTower_LAYER_H__
#define __LoadTower_LAYER_H__

#include "cocos2d.h"
#include "Resources.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include "cocos-ext.h"
#else
#include "extensions/cocos-ext.h"
#endif
#include <string>

class LoadTowerLayer : public cocos2d::Layer, public cocos2d::extension::EditBoxDelegate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void setMainMenu(cocos2d::Layer* scene);
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuOpenCallback(cocos2d::Ref* pSender);
    
    virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);
    
    // implement the "static create()" method manually
    CREATE_FUNC(LoadTowerLayer);
private:
    cocos2d::Layer* _menu;
    cocos2d::extension::EditBox* _savePath;
    std::string _filePath;
    
    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags);
};
#endif
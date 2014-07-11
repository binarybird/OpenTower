#include "OpenTowerManager.h"

USING_NS_OT

OpenTowerManager* OpenTowerManager::_tower;

OpenTowerManager::OpenTowerManager()
{

}

OpenTowerManager::~OpenTowerManager()
{
    
}

OpenTowerManager* OpenTowerManager::sharedTowerManager()
{
    if(_tower == 0){
        _tower = new OpenTowerManager();
    }
    
    return _tower;
}

void OpenTowerManager::update(float delta)
{
	
	//WRITE/UPDATE inGameTimeOfDay here
}

void OpenTowerManager::addStructure(OTType type, cocos2d::Vec2 position)
{
    
}
void OpenTowerManager::removeStructure(OTType type, cocos2d::Vec2 position)
{
    
}

size_t OpenTowerManager::hash(const char* str)
{
	return (*(size_t*)str)>> 2;
}
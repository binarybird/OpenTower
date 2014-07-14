#include "OpenTowerManager.h"

USING_NS_OT

OpenTowerManager* OpenTowerManager::_tower;
std::map<int, OT::Structure::OTStructure> OpenTowerManager::structureRegistry;
std::map<int, OT::Entity::OTEntity> OpenTowerManager::entityRegistry;
OpenTowerManager::OpenTowerManager()
{
	sigmaTime = 0;
	currentQuarter = Q1;
	currentTimeOfDay = MORNING;
	currentDayOfMonth = 1;

	
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

	sigmaTime+=delta;

	/*
	* 1 day = 37.5sec
	* 1Q = 150sec
	* 1y = 600sec
	*
	* 1Q = 4 days
	* 4Q = 1 year
	*/

	if(currentDayOfMonth == 5)
	{
		//CCLOG("DAY OF MONTH CHANGE");
		switch(currentQuarter)
		{
		case Q1: currentQuarter = Q2; break;
		case Q2: currentQuarter = Q3; break;
		case Q3: currentQuarter = Q4; break;
		case Q4: currentQuarter = Q1; break;
		default: break;//CCLOG("TIME: QUARTER ERROR"); break;
		}
		currentDayOfMonth = 1;
	}

	if(sigmaTime > 9.375 && sigmaTime < 13.875)
		currentTimeOfDay = MORNING;
	if(sigmaTime > 13.875 && sigmaTime < 18.75)
		currentTimeOfDay = DAY;
	if(sigmaTime > 18.75 && sigmaTime < 29.625)
		currentTimeOfDay = AFTERNOON;
	if(sigmaTime > 29.625 && sigmaTime < 32.8125)
		currentTimeOfDay = EVENING;
	if(sigmaTime > 32.8125)
		currentTimeOfDay = NIGHT;
	if(sigmaTime >= 37.5)
	{
		sigmaTime = 0;
		currentDayOfMonth+=1;

		//CCLOG("DAY %d, Q %d",currentDayOfMonth,currentQuarter);
	}

	//cocos2d::CCLog("SIGMA: %f, TIME: %d, Day %d, Quarter %d",sigmaTime,currentTimeOfDay,currentDayOfMonth,currentQuarter);

}

bool OpenTowerManager::addStructure(OT::OTType type, OT::OTPoint position)
{
	bool ret = false;

	Structure::OTStructure structure;
	structure.x = position.x;
	structure.y = position.y;
	OTSize size = getSizeForStructure(type);
	structure.width = size.width;
	structure.height = size.height;

	ret = doesCollideWithStructure(structure);

	if(!ret)
	{
		structureRegistry[hashPoint(position)] = structure;
	}
	debug();//TODO: need to convert pixel to screen coord

	//CCLOG("Count %d",structureRegistry.size());

    return !ret;
}
void OpenTowerManager::removeStructure(OT::OTPoint position)
{
    
}
void OpenTowerManager::getStructure(OT::OTPoint position)
{
}

bool OpenTowerManager::doesCollideWithStructure(Structure::OTStructure structure)
{
	bool ret = false;
	for(std::map<int, OT::Structure::OTStructure>::iterator iter=this->structureRegistry.begin(); iter!=this->structureRegistry.end(); ++iter)
	{
		ret = (iter->second).doesCollideWithStructure(structure);
	}

	return ret;
}

void OpenTowerManager::debug()
{
	int i=0;
	for(std::map<int, OT::Structure::OTStructure>::iterator iter=this->structureRegistry.begin(); iter!=this->structureRegistry.end(); ++iter)
	{
		CCLOG("%i) WIDTH: %f, HEIGHT %f, X %f, Y %f",i,(iter->second).width,(iter->second).height,(iter->second).x,(iter->second).y);
		i++;
	}
}

OT::OTSize OpenTowerManager::getSizeForStructure(enum OT::OTType type)
{
    OT::OTSize ret;
    
    switch (type) {
        case SOFFICE :
            ret = OT::OTSize(160,72);
            break;
        default:
            ret = OT::OTSize(32,32);
            break;
	}
    
    return ret;
}

int OpenTowerManager::hashPoint(OT::OTPoint vector)
{
	return (int)((vector.x+vector.y)*(vector.x+vector.y+1)/2)+vector.y;
}
#include "OpenTowerManager.h"

USING_NS_OT

OpenTowerManager* OpenTowerManager::_tower;

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
		CCLOG("DAY OF MONTH CHANGE");
		switch(currentQuarter)
		{
		case Q1: currentQuarter = Q2; break;
		case Q2: currentQuarter = Q3; break;
		case Q3: currentQuarter = Q4; break;
		case Q4: currentQuarter = Q1; break;
		default: CCLOG("TIME: QUARTER ERROR"); break;
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

		CCLOG("DAY %d, Q %d",currentDayOfMonth,currentQuarter);
	}

	//cocos2d::CCLog("SIGMA: %f, TIME: %d, Day %d, Quarter %d",sigmaTime,currentTimeOfDay,currentDayOfMonth,currentQuarter);

}

void OpenTowerManager::addStructure(OT::OTType type, OT::OTPoint position)
{
    
}
void OpenTowerManager::removeStructure(OT::OTPoint position)
{
    
}
void OpenTowerManager::getStructure(OT::OTPoint position)
{
}

bool OpenTowerManager::structureDoesCollide(OT::OTPoint structurePoint)
{
}

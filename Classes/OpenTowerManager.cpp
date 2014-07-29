#include "OpenTowerManager.h"

USING_NS_OT

OpenTowerManager* OpenTowerManager::_tower;

OpenTowerManager::OpenTowerManager()
{
	didInit = false;
}

void OpenTowerManager::init()
{
	structureRegistry = new std::vector<OT::Structure::OTStructure*>();
	entityRegistry = new std::vector<OT::Entity::OTEntity*>();

	sigmaTime = 0;
	currentQuarter = Q1;
	currentTimeOfDay = MORNING;
	currentDayOfMonth = 1;
	year = 0;
    
    didLoadTower = false;
    loadTowerPath = "";

	didInit = true;

}

OpenTowerManager::~OpenTowerManager()
{
    
}

OpenTowerManager* OpenTowerManager::sharedTowerManager()
{
    if(_tower == 0){
        _tower = new OpenTowerManager();
    }

	//my first time doing this static controller class thing
	//not sure how to detect if a "static class" is new or needs init 
	//we reuse the same "static class" potentially multiple times (every time we open or make a new tower)
	//but is "cleaned" each time a tower is closed (structures and entities are removed)
	if(_tower->didInit == false)
		_tower->init();

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
		switch(currentQuarter)
		{
            case Q1: currentQuarter = Q2; break;
            case Q2: currentQuarter = Q3; break;
            case Q3: currentQuarter = Q4; break;
            case Q4: currentQuarter = Q1; year+=1; break;
            default: break;
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
	}

}

OT::OTPoint OpenTowerManager::addStructure(OT::OTType type, OT::OTPoint position)
{
    OTPoint correctedY = this->correctedFloorLocation(position);

	Structure::OTOffice* structure = new Structure::OTOffice();
	structure->x = correctedY.x;
	structure->y = correctedY.y;
	OTSize size = getSizeForStructure(type);
	structure->width = size.width;
	structure->height = size.height;
	structure->hash = hashPoint(position);

	bool doesCollide = doesCollideWithStructure(structure);

	if(!doesCollide)
	{
		structureRegistry->push_back(structure);
	}
	else
    {
        correctedY = OTPoint::ZERO;
        delete structure;
    }
    
    structure = NULL;
    
    return correctedY;
}

bool OpenTowerManager::addFloor(OT::OTPoint floorBegin, OT::OTPoint floorEnd)
{
	return false;
}

OT::OTPoint OpenTowerManager::correctedFloorLocation(OT::OTPoint point)
{
    //TODO: fix for -y
    assert(point.y >=0);
    
    point.y -= ((int)point.y % 72);
    point.y += 36;
    
    return point;
}

void OpenTowerManager::removeStructure(OT::OTPoint position)
{
    
}

void OpenTowerManager::removeStructure(int hash)
{
    
}

void OpenTowerManager::removeStructureAtIndex(int idx)
{
    
}

OT::Structure::OTStructure* OpenTowerManager::getStructure(OT::OTPoint position)
{
	return this->getStructure(hashPoint(position));
}

OT::Structure::OTStructure* OpenTowerManager::getStructure(int hash)
{
	for(std::vector<OT::Structure::OTStructure*>::iterator it = structureRegistry->begin(); it != structureRegistry->end(); ++it) 
	{
		if((*it)->hash == hash)
			return (*it);
	}
    return NULL;
}

OT::Structure::OTStructure* OpenTowerManager::getStructureAtIndex(int idx)
{
	
	return structureRegistry->at(idx);
}

int OpenTowerManager::getStructureCount()
{
	return this->structureRegistry->size();
}
int OpenTowerManager::getEntityCount()
{
	return this->entityRegistry->size();
}

bool OpenTowerManager::doesCollideWithStructure(Structure::OTStructure *structure)
{
	for(std::vector<OT::Structure::OTStructure*>::iterator it = structureRegistry->begin(); it != structureRegistry->end(); ++it) 
	{
		if((*it)->doesCollideWithStructure(structure) == true)
			return true;
	}

	return false;
}

OT::OTSize OpenTowerManager::getSizeForStructure(enum OT::OTType type)
{
    OTSize ret;
    
    switch (type) {
        case OTOFFICE :
            ret = OTSize(160,72);
            break;
		case OTFLOOR:
			ret = OTSize(32,72);
			break;
        default:
            ret = OTSize(32,32);
            break;
	}
    
    return ret;
}

int OpenTowerManager::hashPoint(OT::OTPoint vector)
{
	return (int)((vector.x+vector.y)*(vector.x+vector.y+1)/2)+vector.y;
}

bool OpenTowerManager::save()
{
	OTSerializer::saveBundle bundle;
    
    if(OT::OpenTowerManager::sharedTowerManager()->didLoadTower)
        bundle.saveFilePath = OT::OpenTowerManager::sharedTowerManager()->loadTowerPath;
    else
        return false;
    
    bundle.saveFilePath = loadTowerPath;
	bundle.cash = 1000;
	bundle.currentDayOfMonth = currentDayOfMonth;
	bundle.currentTimeOfDay = currentTimeOfDay;
	bundle.towerName = "HelloWorld";
	bundle.currentQuarter = currentQuarter;
	bundle.entityRegistry = entityRegistry;
	bundle.structureRegistry = structureRegistry;
    bundle.year = year;

	return OTSerializer::saveAll(bundle);
}

bool OpenTowerManager::load()
{
	if(didInit == true)
	{
		this->cleanup();
	}

    if(this->loadTowerPath.length() == 0)
        return false;
    
	OT::OTSerializer::saveBundle bundle = OTSerializer::loadAll(loadTowerPath);
 
	this->cash = bundle.cash;
	this->currentDayOfMonth = bundle.currentDayOfMonth;
	this->currentQuarter = bundle.currentQuarter;
	this->currentTimeOfDay = bundle.currentTimeOfDay;
	this->entityRegistry = bundle.entityRegistry;
	this->structureRegistry = bundle.structureRegistry;
    this->year = bundle.year;
    
    if(entityRegistry == NULL || structureRegistry == NULL)
        return false;
    
	this->didInit = true;

	return true;
}

void OpenTowerManager::cleanup()
{
	//
	//Ran into this, may come back up (FYI)
	//
	//http://support.microsoft.com/kb/121216/en-us
	//
	
    if(structureRegistry != NULL)
    {
        for(std::vector<OT::Structure::OTStructure*>::iterator it = structureRegistry->begin(); it != structureRegistry->end(); ++it)
        {
            delete *it;
        }
        delete structureRegistry;
    }

    if(entityRegistry != NULL)
    {
        for(std::vector<OT::Entity::OTEntity*>::iterator it = entityRegistry->begin(); it != entityRegistry->end(); ++it)
        {
            delete *it;
        }
        delete entityRegistry;
    }

	didInit = false;
	currentQuarter = Q1;
	currentTimeOfDay = MORNING;
	currentDayOfMonth = 1;
}
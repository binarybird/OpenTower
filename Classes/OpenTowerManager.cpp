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

	//TODO - De-serialize data
    //TODO - get actual stats from serialized data
	sigmaTime = 0;
	currentQuarter = Q1;
	currentTimeOfDay = MORNING;
	currentDayOfMonth = 1;

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
		case Q4: currentQuarter = Q1; break;
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

bool OpenTowerManager::addStructure(OT::OTType type, OT::OTPoint position)
{
	bool ret = false;

	/*Structure::OTStructure* structure = new Structure::OTStructure();
	structure->x = position.x;
	structure->y = position.y;
	OTSize size = getSizeForStructure(type);
	structure->width = size.width;
	structure->height = size.height;
	structure->hash = hashPoint(position);*/

	Structure::OTOffice* structure = new Structure::OTOffice();
	structure->x = position.x;
	structure->y = position.y;
	OTSize size = getSizeForStructure(type);
	structure->width = size.width;
	structure->height = size.height;
	structure->hash = hashPoint(position);

	ret = doesCollideWithStructure(structure);

	if(!ret)
	{
		structureRegistry->push_back(structure);
	}
	else{
        delete structure;
    }
    
    structure = NULL;

    return !ret;
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
    OT::OTSize ret;
    
    switch (type) {
        case OTOFFICE :
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

bool OpenTowerManager::save(std::string savePath, std::string saveName)
{

	OTSerializer::saveBundle bundle;
	bundle.saveFilePath = "/somewhere/over/the/rainbow/";//last slash significant
	bundle.cash = 1000;
	bundle.currentDayOfMonth = currentDayOfMonth;
	bundle.currentTimeOfDay = currentTimeOfDay;
	bundle.towerName = "HelloWorld";
	bundle.currentQuarter = currentQuarter;
	bundle.entityRegistry = entityRegistry;
	bundle.structureRegistry = structureRegistry;

	return OTSerializer::saveAll(bundle);
}

bool OpenTowerManager::load(std::string savePath, std::string saveName)
{
	if(didInit == true)
	{
		this->cleanup();
	}

	OT::OTSerializer::saveBundle bundle = OTSerializer::loadAll("HelloWorld");
 
	this->cash = bundle.cash;
	this->currentDayOfMonth = bundle.currentDayOfMonth;
	this->currentQuarter = bundle.currentQuarter;
	this->currentTimeOfDay = bundle.currentTimeOfDay;
	this->entityRegistry = bundle.entityRegistry;
	this->structureRegistry = bundle.structureRegistry;

    for(std::vector<OT::Structure::OTStructure*>::iterator it = structureRegistry->begin(); it != structureRegistry->end(); ++it)
    {
        //CCLOG("FINAL CHACK %i",(*it)->getClassType());
    }
    
	this->didInit = true;

	return true;
}

void OpenTowerManager::cleanup()
{
	//TODO serialize all data to a file

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
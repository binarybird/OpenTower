#include "OTSerializer.h"

USING_NS_OT

OTSerializer::OTSerializer()
{
	this->classType = OTSERIALIZER;
}

OTSerializer::~OTSerializer()
{
}

bool OTSerializer::saveAll(OT::OTSerializer::saveBundle bundle)
{
	//TODO - need a real way to identify classes and types

	OTObjectBlobList *saveData = new OTObjectBlobList();

	for(std::vector<OT::Structure::OTStructure*>::iterator it = bundle.structureRegistry->begin(); it != bundle.structureRegistry->end(); ++it) 
	{
		char buffer[33];//itoa((*it)->hash,buffer,16)
		(*it)->save(saveData->addBlob(itoa((*it)->hash,buffer,16)));//blob's id is the hex value of the hash stored in the object
	}

	for(std::vector<OT::Entity::OTEntity*>::iterator it = bundle.entityRegistry->begin(); it != bundle.entityRegistry->end(); ++it) 
	{
		char buffer[33];
		(*it)->save(saveData->addBlob(itoa((*it)->hash,buffer,16)));//blob's id is the hex value of the hash stored in the object
	}

	OTObjectBlob* gameState = saveData->addBlob("gamestate");

	gameState->addData("cash",&bundle.cash,D_DOUBLE,1);
	gameState->addData("time",&bundle.currentTimeOfDay,D_INT,1);
	gameState->addData("day",&bundle.currentDayOfMonth,D_INT,1);
	gameState->addData("month",&bundle.currentQuarter,D_INT,1);

	//std::string saveFileName = (bundle.saveFilePath+bundle.towerName+FILE_EXTENTION); for release only
	std::string saveFileName = (bundle.towerName+FILE_EXTENTION);

	saveData->save((char*)saveFileName.c_str());

	delete saveData;

	return true;
}

OT::OTSerializer::saveBundle OTSerializer::loadAll(std::string fileName)
{
	saveBundle bundle;

	std::vector<OT::Structure::OTStructure*>* structureRegistry = new std::vector<OT::Structure::OTStructure*>();
	std::vector<OT::Entity::OTEntity*>* entityRegistry = new std::vector<OT::Entity::OTEntity*>();
	
	fileName+=FILE_EXTENTION;

	cocos2d::CCLog("LOADING... %c",(char*)fileName.c_str());

	OTObjectBlobList *loadData = new OTObjectBlobList();
	loadData->load((char*)fileName.c_str());
	
	for(int i = 0; i< loadData->getNumBlobs(); i++)
	{
		OTObjectBlob* dataIn = loadData->getBlob(i);

		OTType type;
		dataIn->getData("classtype",&type);

		Structure::OTOffice* office;
		//need to have pointers to everything here :(

		switch (type) {
        case OTOFFICE :
            office = new Structure::OTOffice();
			office->load(dataIn);
			structureRegistry->push_back(office);
            break;
        default: break;
		}
	}

	OTObjectBlob* gameState =  loadData->getBlob("gamestate");

	bundle.saveFilePath = "/somewhere/over/the/rainbow/";//last slash significant
	gameState->getData("cash",&bundle.cash);
	gameState->getData("time",&bundle.currentTimeOfDay);
	gameState->getData("month",&bundle.currentQuarter);
	gameState->getData("day",&bundle.currentDayOfMonth);
	
	bundle.towerName = "HelloWorld";
	bundle.entityRegistry = entityRegistry;
	bundle.structureRegistry = structureRegistry;

    return bundle;
}

char* OTSerializer::getClassIdentifier(OT::OTType type)
{
	//(char*)(*it)->className.c_str()
	return "CLASS";
}
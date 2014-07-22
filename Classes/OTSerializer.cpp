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
    bool ret = false;
    
    if(bundle.entityRegistry != NULL && bundle.structureRegistry != NULL){
        OTObjectBlobList *saveData = new OTObjectBlobList();

        for(std::vector<OT::Structure::OTStructure*>::iterator it = bundle.structureRegistry->begin(); it != bundle.structureRegistry->end(); ++it)
        {
            if((*it)->hash != 0){
                char buffer[15] = {0};
                #if OT_TARGET_PLATFORM == OT_PLATFORM_WINDOWS ||  OT_TARGET_PLATFORM == OT_PLATFORM_WIN32// see OTMacros.h
                    _snprintf(buffer, 15,"%i",(*it)->hash);//fucking microsoft
                #else
                    snprintf(buffer, 15,"%i",(*it)->hash);
                #endif
                (*it)->save(saveData->addBlob(buffer));//blob's id is the value of the hash stored in the object
            }
        }

        for(std::vector<OT::Entity::OTEntity*>::iterator it = bundle.entityRegistry->begin(); it != bundle.entityRegistry->end(); ++it)
        {
            if((*it)->hash != 0){
                char buffer[15] = {0};
                #if  OT_TARGET_PLATFORM == OT_PLATFORM_WINDOWS ||  OT_TARGET_PLATFORM == OT_PLATFORM_WIN32 // see OTMacros.h
                    _snprintf(buffer, 15,"%i",(*it)->hash);//fucking microsoft
                #else
                    snprintf(buffer, 15,"%i",(*it)->hash);
                #endif
                (*it)->save(saveData->addBlob(buffer));//blob's id is the value of the hash stored in  the object
            }
        }

        OTObjectBlob* gameState = saveData->addBlob("gamestate");
        
        int version = OPENTOWER_VERSION;

        gameState->addData("cash",&bundle.cash, D_DOUBLE, 1);
        gameState->addData("time",&bundle.currentTimeOfDay, D_INT,1 );
        gameState->addData("day",&bundle.currentDayOfMonth, D_INT, 1);
        gameState->addData("month",&bundle.currentQuarter, D_INT, 1);
        gameState->addData("version", &version, D_INT, 1);

        std::string saveFileName = (bundle.saveFilePath);

        saveData->save((char*)saveFileName.c_str());

        delete saveData;
        ret = true;
    }

	return ret;
}

OT::OTSerializer::saveBundle OTSerializer::loadAll(std::string fileName)
{
	saveBundle bundle;

	std::vector<OT::Structure::OTStructure*>* structureRegistry = new std::vector<OT::Structure::OTStructure*>();
	std::vector<OT::Entity::OTEntity*>* entityRegistry = new std::vector<OT::Entity::OTEntity*>();
	
	//fileName+=FILE_EXTENTION;

	OTObjectBlobList *loadData = new OTObjectBlobList();
	loadData->load((char*)fileName.c_str());
    
    int version;
    
    OTObjectBlob* gameState =  loadData->getBlob("gamestate");
    if(gameState != NULL)
    {
        bundle.saveFilePath = fileName;//last slash significant
        gameState->getData("cash",&bundle.cash);
        gameState->getData("time",&bundle.currentTimeOfDay);
        gameState->getData("month",&bundle.currentQuarter);
        gameState->getData("day",&bundle.currentDayOfMonth);
        gameState->getData("version",&version);
    }
	
    //TODO - check version: different versions could have different loading data
    
    //here we load the classes
	for(int i = 0; i< loadData->getNumBlobs(); i++)
	{
		OTObjectBlob* dataIn = loadData->getBlob(i);

		OTType type;
		dataIn->getData("classtype",&type);
        
		Structure::OTOffice* office;

		switch (type) {
        case OTOFFICE :
            office = new Structure::OTOffice();
			office->load(dataIn);
			structureRegistry->push_back(office);
            break;
        default: break;
		}
	}

	bundle.towerName = "HelloWorld";
	bundle.entityRegistry = entityRegistry;
	bundle.structureRegistry = structureRegistry;

    return bundle;
}

OT::OTType OTSerializer::getClassType()
{
    return this->classType;
}
void OTSerializer::setClassType(OT::OTType type)
{
    this->classType = type;
}
#include "OTSerializer.h"


USING_NS_OT

void OTSerializer::saveAll(OT::OTSerializer::saveBundle bundle)
{
	//TODO - need a real way to identify classes and types

	OTObjectBlobList *saveData = new OTObjectBlobList();

	for(std::vector<OT::Structure::OTStructure*>::iterator it = bundle.structureRegistry->begin(); it != bundle.structureRegistry->end(); ++it) 
	{
		(*it)->save(saveData->addBlob((char*)(*it)->className.c_str()));
	}

	for(std::vector<OT::Entity::OTEntity*>::iterator it = bundle.entityRegistry->begin(); it != bundle.entityRegistry->end(); ++it) 
	{
		(*it)->save(saveData->addBlob((char*)(*it)->className.c_str()));
	}

	saveData->addBlob("cash")->addData("cash",&bundle.cash,D_DOUBLE,1);
	saveData->addBlob("time")->addData("time",&bundle.currentTimeOfDay,D_INT,1);
	saveData->addBlob("day")->addData("day",&bundle.currentDayOfMonth,D_INT,1);
	saveData->addBlob("month")->addData("month",&bundle.currentQuarter,D_INT,1);

	std::string saveFileName = bundle.towerName+".OpenTower";

	saveData->save((char*)saveFileName.c_str());

	delete saveData;
}

OT::OTSerializer::saveBundle OTSerializer::loadAll()
{
	saveBundle bundle;

    return bundle;
}

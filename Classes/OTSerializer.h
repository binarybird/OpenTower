//
//  OTSerializer.h
//  OpenTower
//

#ifndef __OpenTower__OTSerializer__
#define __OpenTower__OTSerializer__

#include <iostream>
#include "OTObjectBlobList.h"
#include "OTObjectBlob.h"
#include "OTSerializable.h"
#include "OTMacros.h"
#include "OTStructure.h"
#include "OTEntity.h"
#include "OTPoint.h"
#include "OTSize.h"
#include "OTObject.h"

USING_NS_OT_BEGIN

class OTSerializer : public OT::OTObject{
public:
	struct saveBundle{
		std::string towerName;
		std::vector<OT::Structure::OTStructure*>* structureRegistry;
		std::vector<OT::Entity::OTEntity*>* entityRegistry;
		OT::OTTime currentTimeOfDay;
		OT::OTQuarter currentQuarter;
		int currentDayOfMonth;
		double cash;
	};
    static void saveAll(saveBundle bundle);
    static saveBundle loadAll();
};

USING_NS_OT_END

#endif /* defined(__OpenTower__OTSerializer__) */

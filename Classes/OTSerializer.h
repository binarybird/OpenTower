//
//  OTSerializer.h
//  OpenTower
//

#ifndef __OpenTower__OTSerializer__
#define __OpenTower__OTSerializer__

#include "OpenTower.h"
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>

USING_NS_OT_BEGIN

class OTSerializer : public OT::OTObject{
public:
	struct saveBundle{
		std::string saveFilePath;
		std::string towerName;
		std::vector<OT::Structure::OTStructure*>* structureRegistry;
		std::vector<OT::Entity::OTEntity*>* entityRegistry;
		OT::OTTime currentTimeOfDay;
		OT::OTQuarter currentQuarter;
		int currentDayOfMonth;
		double cash;
	};

	OTSerializer();
	~OTSerializer();
    static bool saveAll(saveBundle bundle);
    static saveBundle loadAll(std::string fileName);

    virtual OT::OTType getClassType();
    virtual void setClassType(OT::OTType type);
	OT::OTType classType;
};

USING_NS_OT_END

#endif /* defined(__OpenTower__OTSerializer__) */

#ifndef __OpenTower__OTOffice__
#define __OpenTower__OTOffice__
#include "OTStructure.h"
#include "OTObjectBlob.h"
#include <string>

USING_NS_STRUCTURE_BEGIN

class OTOffice : public OT::Structure::OTStructure
{
public:
	OTOffice(void);
	~OTOffice(void);
	virtual void save(OT::OTObjectBlob *state);
	virtual void load(OT::OTObjectBlob *state);

    OT::OTType classType;
	std::string customOfficeName;
};

USING_NS_STRUCTURE_END
#endif
#ifndef __OpenTower__OTOffice__
#define __OpenTower__OTOffice__
#include "OTStructure.h"
#include "OTObjectBlob.h"

USING_NS_STRUCTURE_BEGIN

class OTOffice : public OT::OTStructure
{
public:
	OTOffice(void);
	~OTOffice(void);
	virtual void save(OT::OTObjectBlob *state);
	virtual void load(OT::OTObjectBlob *state);
    int type;
};

USING_NS_STRUCTURE_END
#endif
#pragma once
#include "OTStructure.h"

USING_NS_STRUCTURE_BEGIN

class OTOffice : public OTStructure
{
public:
	OTOffice(void);
	~OTOffice(void);
	virtual void save(OT::OTObjectBlob *state);
	virtual void load(OT::OTObjectBlob *state);
    int type;
};

USING_NS_STRUCTURE_END
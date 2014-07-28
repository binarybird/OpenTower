#ifndef __OpenTower__OTFloor__
#define __OpenTower__OTFloor__
#include "OTStructure.h"
#include "OTObjectBlob.h"
#include <string>

USING_NS_STRUCTURE_BEGIN


// The floor's x and y (inherited) is its spawn point
// The floors size (inherited) is its total size (size left + size right)
class OTFloor : public OT::Structure::OTStructure
{
public:
	OTFloor(void);
	~OTFloor(void);
	virtual void save(OT::OTObjectBlob *state);
	virtual void load(OT::OTObjectBlob *state);

    virtual void setClassType(OT::OTType type) override;
    virtual OT::OTType getClassType() override;
    
    OT::OTType classType;

	OT::OTSize left;
	OT::OTSize right;
};

USING_NS_STRUCTURE_END
#endif
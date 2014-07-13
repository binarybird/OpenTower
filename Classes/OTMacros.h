//
//  OTEnums.h
//  OpenTower
//
#ifndef OpenTower_OTEnums_h
#define OpenTower_OTEnums_h

#include "OTSize.h"
#include "OTPoint.h"

#define USING_NS_OT_BEGIN namespace OT{
#define USING_NS_OT_END }
#define USING_NS_OT using namespace OT;

#define USING_NS_ENTITY_BEGIN namespace OT { namespace Entity{
#define USING_NS_ENTITY_END }}
#define USING_NS_ENTITY using namespace OT::Entity;

#define USING_NS_STRUCTURE_BEGIN namespace OT { namespace Structure{
#define USING_NS_STRUCTURE_END }}
#define USING_NS_STRUCTURE using namespace OT::Structure;

USING_NS_OT_BEGIN

enum OTType{
    OBJECT      =0,
    ENTITY      =1,
    STRUCTURE   =2,
    PERSON      =3,
    ELEVATORCAR =4,
    SOFFICE     =5,
    EOFFICE     =6,
    
};

enum OTTime{
	MORNING		=600,
    DAY         =900,
    AFTERNOON   =1200,
    EVENING     =1900,
    NIGHT       =2100,
};

enum OTQuarter{
    Q1  =1,
    Q2  =2,
    Q3  =3,
    Q4  =4,
};

static OT::OTSize getSizeForStructure(enum OT::OTType type)
{
    OT::OTSize ret;
    
    switch (type) {
        case SOFFICE :
            ret = OT::OTSize(72,32);
            break;
        default:
            ret = OT::OTSize(32,32);
            break;
    }
    
    return ret;
}

static int hashPoint(OT::OTPoint vector)
{
	return (int)((vector.x+vector.y)*(vector.x+vector.y+1)/2)+vector.y;
}

USING_NS_OT_END

#endif

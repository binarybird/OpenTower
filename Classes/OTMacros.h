//
//  OTEnums.h
//  OpenTower
//
#include "cocos2d.h"


#ifndef OpenTower_OTEnums_h
#define OpenTower_OTEnums_h

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
    DAY         =700,
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

static cocos2d::Size getSizeForStructure(enum OTType type)
{
    cocos2d::Size ret;
    
    switch (type) {
        case SOFFICE :
            ret = cocos2d::Size(72,32);
            break;
        default:
            ret = cocos2d::Size(32,32);
            break;
    }
    
    return ret;
}



static int hashVector(cocos2d::Vec2 vector)
{
	return (int)((vector.x+vector.y)*(vector.x+vector.y+1)/2)+vector.y;
}

USING_NS_OT_END

#endif

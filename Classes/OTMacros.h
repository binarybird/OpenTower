//
//  OTEnums.h
//  OpenTower
//

#ifndef OpenTower_OTEnums_h
#define OpenTower_OTEnums_h

#define USING_NS_OT_BEGIN namespace OT{
#define USING_NS_OT_END }
#define USING_NS_OT using namespace OT;

#define USING_NS_ENTITIY_BEGIN namespace OT { namespace Entity{
#define USING_NS_ENTITY_END }}
#define USING_NS_ENTITY using namespace OT::Entity;

#define USING_NS_STRUCTURE_BEGIN namespace OT { namespace Structure{
#define USING_NS_STRUCTURE_END }}
#define USING_NS_STRUCTURE using namespace OT::Structure;

enum OTType{
    OBJECT      =0,
    ENTITY      =1,
    STRUCTURE   =2,
    PERSON      =3,
    ELEVATORCAR =4,
    
};



#endif

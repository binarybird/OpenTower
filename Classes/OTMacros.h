//
//  OTEnums.h
//  OpenTower
//
#ifndef OpenTower_OTEnums_h
#define OpenTower_OTEnums_h

#define FILE_EXTENTION ".OpenTower"

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
    OTOBJECT      =0,
    OTENTITY      =1,
    OTSTRUCTURE   =2,
    OTPERSON      =3,
    OTELEVATORCAR =4,
    OTOFFICE     =5,
	OTOBJECTBLOB = 6,
	OTOBJECTBLOBLIST = 7,
	OTPOINT = 8,
	OTSERIALIZER = 9,
	OTSERIALIZABLE = 10,
	OTSIZE = 11,

    
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

USING_NS_OT_END

#endif

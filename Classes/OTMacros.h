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


//////////////////////////////////////////////////////////////////////////
// pre configure (  totaly ripped from cocos2d :p - if it aint broke... )
//
// ********* You MUST set a target platform in your projects setting -> preprocessor macros ******
//
//////////////////////////////////////////////////////////////////////////

#define OT_PLATFORM_UNKNOWN            0
#define OT_PLATFORM_IOS                1
#define OT_PLATFORM_ANDROID            2
#define OT_PLATFORM_WIN32              3
#define OT_PLATFORM_MARMALADE          4
#define OT_PLATFORM_LINUX              5
#define OT_PLATFORM_BADA               6
#define OT_PLATFORM_BLACKBERRY         7
#define OT_PLATFORM_MAC                8
#define OT_PLATFORM_NACL               9
#define OT_PLATFORM_EMSCRIPTEN        10
#define OT_PLATFORM_TIZEN             11
#define OT_PLATFORM_QT5               12
#define OT_PLATFORM_WP8               13
#define OT_PLATFORM_WINRT             14

// Determine target platform by compile environment macro.
#define OT_TARGET_PLATFORM         OT_PLATFORM_UNKNOWN

// mac
#if defined(OT_TARGET_OS_MAC)
#undef  OT_TARGET_PLATFORM
#define OT_TARGET_PLATFORM         OT_PLATFORM_MAC
#endif

// iphone
#if defined(OT_TARGET_OS_IPHONE)
#undef  OT_TARGET_PLATFORM
#define OT_TARGET_PLATFORM         OT_PLATFORM_IOS
#endif

// android
#if defined(ANDROID)
#undef  OT_TARGET_PLATFORM
#define OT_TARGET_PLATFORM         OT_PLATFORM_ANDROID
#endif

// win32
#if defined(WIN32) && defined(_WINDOWS)
#undef  OT_TARGET_PLATFORM
#define OT_TARGET_PLATFORM         OT_PLATFORM_WIN32
#endif

// linux
#if defined(LINUX)
#undef  OT_TARGET_PLATFORM
#define OT_TARGET_PLATFORM         OT_PLATFORM_LINUX
#endif

// marmalade
#if defined(MARMALADE)
#undef  OT_TARGET_PLATFORM
#define OT_TARGET_PLATFORM         OT_PLATFORM_MARMALADE
#endif

// bada
#if defined(SHP)
#undef  OT_TARGET_PLATFORM
#define OT_TARGET_PLATFORM         OT_PLATFORM_BADA
#endif

// qnx
#if defined(__QNX__)
#undef  OT_TARGET_PLATFORM
#define OT_TARGET_PLATFORM     OT_PLATFORM_BLACKBERRY
#endif

// native client
#if defined(__native_client__)
#undef  OT_TARGET_PLATFORM
#define OT_TARGET_PLATFORM     OT_PLATFORM_NACL
#endif

// Emscripten
#if defined(EMSCRIPTEN)
#undef  OT_TARGET_PLATFORM
#define OT_TARGET_PLATFORM     OT_PLATFORM_EMSCRIPTEN
#endif

// tizen
#if defined(TIZEN)
#undef  OT_TARGET_PLATFORM
#define OT_TARGET_PLATFORM     OT_PLATFORM_TIZEN
#endif

// qt5
#if defined(OT_TARGET_QT5)
#undef  OT_TARGET_PLATFORM
#define OT_TARGET_PLATFORM     OT_PLATFORM_QT5
#endif

// WinRT (Windows Store App)
#if defined(WINRT)
#undef  OT_TARGET_PLATFORM
#define OT_TARGET_PLATFORM			OT_PLATFORM_WINRT
#endif

// WP8 (Windows Phone 8 App)
#if defined(WP8)
#undef  OT_TARGET_PLATFORM
#define OT_TARGET_PLATFORM			OT_PLATFORM_WP8
#endif


//////////////////////////////////////////////////////////////////////////
// post configure
//////////////////////////////////////////////////////////////////////////

// check user set platform
#if ! OT_TARGET_PLATFORM
#error  "Cannot recognize the target platform; are you targeting an unsupported platform?"
#endif

#if (OT_TARGET_PLATFORM == OT_PLATFORM_WIN32)
#ifndef __MINGW32__
#pragma warning (disable:4127)
#endif
#endif  // OT_PLATFORM_WIN32



#endif

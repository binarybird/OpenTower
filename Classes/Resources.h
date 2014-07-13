#ifndef __Resources__
#define __Resources__

/*===============default settings===============*/

#define SCROLL_MULTIPLIER 10
#define SCROLL_SPEED 2

#define TOOLPANAL_HEIGHT 200
#define TOOLPANAL_WIDTH 96

/*===============strings===============*/

#define GAMENAME "OpenTower"
#define MAINMENU_NEWTOWER "New Tower"
#define MAINMENU_CLOSE "Close"

/*===============images===============*/

#define UI_PLAYBUTTON_N "start.png"
#define UI_PLAYBUTTON_S "start.png"
#define UI_CLOSE_N "CloseNormal.png"
#define UI_CLOSE_S "CloseSelected.png"

#define TOOLPANEL_ICONOFFICE_N_1 "UI/Icon-LargeOffice.png"
#define TOOLPANEL_ICONOFFICE_S_1 "UI/Icon-LargeOffice.png"

#define BACKGROUND_SKYLINE "UI/OT_skyline.png"

/*===============sprites===============*/
/*
 * Naming conventions for individual sprite sheets:
 *
 * Let  t%d_%d_%d.png  =  tX_Y_Z.png
 *
 * For Occupied Rooms:
 * X=Room type		 (e.g. office with 5 windows, office with 2 windows, etc...)
 * Y=Room Contents   (e.g. The unique frameset varient: office with a couch, office with a computer, office with a chair and computer, etc...)
 * Z=Frame Number	 (These frames are looped. NOTE: if Z==0 it is the night version of the animation)
 *
 *
 * For UN-Occupied Rooms:
 * X=Room Type		 (e.g. Empty office with 5 windows, empty office with 2 windows, etc...)
 * Y=0				 (For unoccupied rooms Y always == 0)
 * Z=0|1			 (Because empty rooms are not animated there are only two frames, Z==0:night, Z==1:day)
 *
 * Note: in both cases Y should be a non decreasing unique integer across the entire sprite sheet (0 is empty varient, 1 is chair varient, 2 is tv varient, etc..)
 * Y is used to find the number of animated frames the varient has - see FRAMECOUNT enum
 */
#define SPRITE_OFFICE_FORMAT "office_t%d_%d_%d.png"
#define SPRITE_OFFICE_PLIST "SpriteSheets/office.plist"
#define SPRITE_OFFICE_SHEET "SpriteSheets/office.png"

enum FRAMECOUNT{
	OFFICE_0 = 2,
	OFFICE_1 = 7,
	OFFICE_2 = 6,
	OFFICE_3 = 4,
	OFFICE_4 = 7,
	OFFICE_5 = 4,
	OFFICE_6 = 3,
	OFFICE_7 = 3,
	CONDO_0 = 0,
	CONDO_1 = 0,
	CONDO_2 = 0,
};

struct StructureUserData{
	int type;
	int varient;
	int startFrame;
	int numFrames;
	std::string format;
};

#endif
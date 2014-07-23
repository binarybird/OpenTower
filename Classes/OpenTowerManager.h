//
//  OpenTower.h
//  OpenTower
//

#ifndef __OpenTower__OpenTower__
#define __OpenTower__OpenTower__

#include "OTMacros.h"
#include "OTStructure.h"
#include "OTEntity.h"
#include "OTPoint.h"
#include "OTSize.h"
#include "OTSerializer.h"
#include "OTOffice.h"

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>

#include "cocos2d.h"


USING_NS_OT_BEGIN

class OpenTowerManager{
public:
    OpenTowerManager();
    ~OpenTowerManager();

    /*
     * @arg: NYI
     * @return: NYI
     *
     * @description: NYI
     */
    void removeStructure(OT::OTPoint position);
    
    /*
     * @arg: NYI
     * @return: NYI
     *
     * @description: NYI
     */
	void removeStructure(int hash);
    
    /*
     * @arg: NYI
     * @return: NYI
     *
     * @description: NYI
     */
	void removeStructureAtIndex(int idx);
    
    /*
     * @arg: OT::OTPoint - any point on the x,y plane
     * @return: OT::Structure::OTStructure - structure object at the given point
     *
     * @description: hashes the argument point and calles getStructure(int hash)
     */
	OT::Structure::OTStructure* getStructure(OT::OTPoint position);
    
    /*
     * @arg: int - the hash of the OT::Point
     * @return: OT::Structure::OTStructure - structure object for the given hash
     *
     * @description: iterates through the structure simulation stack, returns the structure if the hashes match
     */
	OT::Structure::OTStructure* getStructure(int hash);
    
    /*
     * @arg: int - the index at the structure simulation stack
     * @return: OT::Structure::OTStructure - structure object at the given point
     *
     * @description: returns the structure object at the index given from the structure simulation stack
     */
	OT::Structure::OTStructure* getStructureAtIndex(int idx);
    
	/*
     * @arg: OT::OTType - structure type, OT::OTPosition - position anywhere in the x,y plane
     * @return: bool 0 if fail 1 of suceed
     *
     * @description: creates a floor from floorBegin to floorEnd. Checks for placement validity
     */
    bool addFloor(OT::OTPoint floorBegin, OT::OTPoint floorEnd);

    /*
     * @arg: OT::OTType - structure type, OT::OTPosition - position anywhere in the x,y plane
     * @return: OT::OTPoint - the location of the structure with the y corrected to conform to the floor grid - OT::OTPoint::ZERO if failure
     *
     * @description: Checks for structure collision, corrects y value for the floor grid, and adds the structure to the structure simulation stack (if no collision).
     */
    OT::OTPoint addStructure(OT::OTType type, OT::OTPoint position);
    
    /*
     * @arg: OT::Structure - structure object
     * @return: bool - 0 if no collision, 1 if collision
     *
     * @description: iterates through all structures in the structure simulation stack to check for collisions
     */
	bool doesCollideWithStructure(OT::Structure::OTStructure *structure);
    
    /*
     * @arg: OT::Point - any point on the x,y plane
     * @return: OT::OTPoint - the argument point with the y corrected to conform to the floor grid
     *
     * @description: corrects the y value to conform to the floor grid, x value is unchanged
     */
    OT::OTPoint correctedFloorLocation(OT::OTPoint point);
    
    /*
     * @arg: None
     * @return: Void
     *
     * @description: called by OpenTowerManager::sharedTowerManager() if there is no static instance of this class. Creates various 
     * instance variables and populates static ones
     */
    void init();
    
    /*
     * @arg: float
     * @return: Void
     *
     * @description: Called by your implementation code to update and move the OpenTower simulation logic (ideal >30 times a second)
     */
	void update(float delta);
    
    /*
     * @arg: None
     * @return: Void
     *
     * @description: Cleans up the statically allocated variables - needs to be called for every tower game closed
     */
	void cleanup();
    
    /*
     * @arg: None
     * @return: bool 1 if success, 0 if fail
     *
     * @description: saves the current gamestate to disk. this->loadTowerPath MUST contain a save path, otherwise fail
     */
	bool save();
    
    /*
     * @arg: None
     * @return: bool 1 if success, 0 if fail
     *
     * @description: loads the saved gamestate to disk. this->loadTowerPath MUST contain a load path, otherwise fail
     */
	bool load();
    
    /*
     * @arg: OT::OTType - the type of structure
     * @return: OT::OTSize - size of the the structure
     *
     * @description: a simple switch statment based on OT::OTType and returns a size
     */
    OT::OTSize getSizeForStructure(enum OT::OTType type);
    
    /*
     * @arg: OT::OTPoint
     * @return: int
     *
     * @description: hashes the point to an integer
     */
    int hashPoint(OT::OTPoint vector);
    
    /*
     * @arg: None
     * @return: int
     *
     * @description: returns the number of structures currently in the structure simulator stack
     */
	int getStructureCount();
    
    /*
     * @arg: None
     * @return: int
     *
     * @description: returns the number of entities currently in the entity simulator stack
     */
	int getEntityCount();

    /*
     * @arg: None
     * @return: OpenTowerManager
     *
     * @description: initilizes (if needed) and returns a static instance of OpenTowerManager
     */
	static OpenTowerManager* sharedTowerManager();

    /*
     * @return: OT::OTTime - time of day
     *
     * @description: the current time of day is set by the update() method (1 day = 37.5sec)
     */
    OT::OTTime currentTimeOfDay;
    
    /*
     * @return: OT::OTQuarter - time of day
     *
     * @description: the current quarter is set by the update() method (1Q = 150sec = 4days)
     */
    OT::OTQuarter currentQuarter;
    
    /*
     * @return: int - current day of the month
     *
     * @description: the current day is set by the update() method (1Q = 150sec = 4days)
     */
    int currentDayOfMonth;
    
    /*
     * @return: int - current number of years active
     *
     * @description: the current year is set by the update() method (1y = 600sec = 4Q = 16days)
     */
    int year;
    
    /*
     * @return: double amount of cash
     *
     * @description: its cash, money, $$$.
     */
	double cash;
    
    /*
     * @misc
     *
     * @description: instance variables used by the load() and save() methods (in this and other classes) to determine the state of the tower instance.
     */
    bool didInit;
    bool didLoadTower;
    std::string loadTowerPath;

private:
    static OpenTowerManager* _tower;
	std::vector<OT::Structure::OTStructure*>* structureRegistry;
	std::vector<OT::Entity::OTEntity*>* entityRegistry;

	float sigmaTime;

};

USING_NS_OT_END

#endif /* defined(__OpenTower__OpenTower__) */

//
//  OTSerializer.h
//  OpenTower
//

#ifndef __OpenTower__OTSerializer__
#define __OpenTower__OTSerializer__

#include <iostream>
#include "OTObjectBlobList.h"
#include "OTObjectBlob.h"
#include "OTSerializable.h"
#include "OTMacros.h"

USING_NS_OT_BEGIN

class OTSerializer {
public:
    static void saveAll(char* towerName);
    static void loadAll(char* towerName);
    void save(OTObjectBlob *state);
    void load(OTObjectBlob *state);
};

USING_NS_OT_END

#endif /* defined(__OpenTower__OTSerializer__) */

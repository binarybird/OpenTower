#ifndef OBJECTBLOBLIST_H
#define OBJECTBLOBLIST_H

#include "OTObjectBlob.h"
#include "OTMacros.h"
#include "OTObject.h"

USING_NS_OT_BEGIN

class OTObjectBlobList : public OT::OTObject{
protected:
    int numBlobs;
    char **blobName;
    OT::OTObjectBlob **blobs;
	
public:
    OTObjectBlobList();
    virtual ~OTObjectBlobList();
    int getNumBlobs();
    OT::OTObjectBlob *addBlob(char *name);
    OT::OTObjectBlob *getBlob(int idx);
    OT::OTObjectBlob *getBlob(char *name);
    int getBlobIdx(char *name);
    bool save(char *filename);
    bool load(char *filename);
	OT::OTType classType;
};

USING_NS_OT_END

#endif
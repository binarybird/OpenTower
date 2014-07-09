#ifndef OBJECTBLOBLIST_H
#define OBJECTBLOBLIST_H

#include "OTObjectBlob.h"
#include "OTMacros.h"

USING_NS_OT_BEGIN

class OTObjectBlobList {
protected:
    int numBlobs;
    char **blobName;
    OTObjectBlob **blobs;
public:
    OTObjectBlobList();
    virtual ~OTObjectBlobList();
    int getNumBlobs();
    OTObjectBlob *addBlob(char *name);
    OTObjectBlob *getBlob(int idx);
    OTObjectBlob *getBlob(char *name);
    int getBlobIdx(char *name);
    bool save(char *filename);
    bool load(char *filename);
};

USING_NS_OT_END

#endif
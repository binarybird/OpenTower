#ifndef OBJECTBLOB_H
#define OBJECTBLOB_H
 
/*
bool,char,int,float,double
*/
#include "OTMacros.h"


USING_NS_OT_BEGIN

const static int D_BOOL = 0;
const static int D_CHAR = 1;
const static int D_INT = 2;
const static int D_FLOAT = 3;
const static int D_DOUBLE = 4;
 
class OTObjectBlob{
protected:
    int numData;
    char **dataName;
    int *dataType;
    int *dataSize;
    int *dataLength;
    char **data;
public:
    OTObjectBlob();
    virtual ~OTObjectBlob();
    void addData(char *name, void *data_in, int type, int length);
    int getDataSize(char *name);
    int getDataType(char *name);
    int getDataLength(char *name);
    int getDataIdx(char *name);
    void *getData(char *name);
    void getData(char *name, void *data_out);
    int getTypeSize(int type);
    void massageData(int type, void *data_in, int length, int size);
    char *saveBlob(int *size);
    void loadBlob(char *blob);
};

USING_NS_OT_END
 
#endif
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "OTObjectBlob.h"

USING_NS_OT

OTObjectBlob::OTObjectBlob()
{
    numData = 0;
    dataName = NULL;
    dataType = NULL;
    dataSize = NULL;
    dataLength = NULL;
    data = NULL;

	this->classType = OTOBJECTBLOB;
}
OTObjectBlob::~OTObjectBlob()
{
    for(int d=0;d<numData;d++)
    {
        free(dataName[d]);
        free(data[d]);
    }
    free(dataName);
    free(data);
    free(dataType);
    free(dataSize);
    free(dataLength);
}
/*
 addData takes a named handle, a pointer to data, a known type (as defined in
 ObjectBlob.h) and the length or amount of data located at that pointer and
 copies it into the blob's storage in a consistent format.
 */
void OTObjectBlob::addData(char *name, void *data_in, int type, int length)
{
    numData++;
    dataName = (char **)realloc(dataName, sizeof(char *)*numData);
    dataName[numData-1] = strdup(name);
    dataType = (int *)realloc(dataType, sizeof(int)*numData);
    dataType[numData-1] = type;
    dataSize = (int *)realloc(dataSize, sizeof(int)*numData);
    dataSize[numData-1] = getTypeSize(type);
    dataLength = (int *)realloc(dataLength, sizeof(int)*numData);
    dataLength[numData-1] = length;
    data = (char **)realloc(data, sizeof(char *)*numData);
    data[numData-1] = (char *)malloc(sizeof(char)*dataSize[numData-1]*length);
    massageData(type, data_in, length, dataSize[numData-1]);
}
/*
 getDataSize returns the size of the datatype stored at the named handle
 */
int OTObjectBlob::getDataSize(char *name)
{
    int idx = getDataIdx(name);
    if(idx >= 0 && idx < numData)
    {
        return dataSize[idx];
    }
    return -1;
}
/*
 getDataType returns the type of data stored at the named handle
 */
int OTObjectBlob::getDataType(char *name)
{
    int idx = getDataIdx(name);
    if(idx >= 0 && idx < numData)
    {
        return dataType[idx];
    }
    return -1;
}
/*
 getDataLength returns the number of data stored at the named handle
 */
int OTObjectBlob::getDataLength(char *name)
{
    int idx = getDataIdx(name);
    if(idx >= 0 && idx < numData)
    {
        return dataLength[idx];
    }
    return -1;
}
/*
 getDataIdx returns the internal index of the stored data at the named
 handle
 */
int OTObjectBlob::getDataIdx(char *name)
{
    for(int d=0;d<numData;d++)
    {
        if(strcmp(dataName[d], name) == 0)
        {
            return d;
        }
    }
    printf("Object Blob Error: Couldn't find data handle '%s'.\n",name);
    return -1;
}
/*
 getData(char *name) returns a pointer to the raw data identified at
 the named handle
 */
void *OTObjectBlob::getData(char *name)
{
    int idx = getDataIdx(name);
    if(idx >= 0 && idx < numData)
    {
        return data[idx];
    }
    return NULL;
}
/*
 getData(char *name, void *data_out) loads the stored data identified by
 the named handle into the area pointed to by data_out.
 
 Ideally this should massage the data into the expected platform format
 before copying the stored data into data_out.
 */
void OTObjectBlob::getData(char *name, void *data_out)
{
    int idx = getDataIdx(name);
    if(idx >= 0 && idx < numData)
    {
        memcpy(data_out, data[idx], dataSize[idx]*dataLength[idx]);
    }
}
/*
 getTypeSize returns the internal storage size of the indicated data type
 */
int OTObjectBlob::getTypeSize(int type)
{
    //These are hard-coded in the event I decide to use platforms with different
    //fundamental data type sizes, the save files will be consistent with this
    //to allow interchange of save data
    switch (type) {
        case D_BOOL:
            return 1;
            break;
        case D_CHAR:
            return 1;
            break;
        case D_INT:
            return 4;
            break;
        case D_FLOAT:
            return 4;
            break;
        case D_DOUBLE:
            return 8;
            break;
    }
    return 0;
}
/*
 massageData is a wrapper that allows ObjectBlob to be truly cross
 platform, currently it is just a simple pass-through but the idea
 is this can deal with data size mismatches and endian differences
 across platform types.
 */
void OTObjectBlob::massageData(int type, void *data_in, int length, int size)
{
    //passthrough for LE (ie x86, iOS)
    //stored data is Little Endian
    memcpy(data[numData-1], data_in, length*size);
}
/*
 saveBlob creates a character array that contains the data currently
 stored in the ObjectBlob, the integer pointed to by size will be
 filled with the size of the array
 */
char *OTObjectBlob::saveBlob(int *size)
{
    int blobSize = 0;
    int blobOffset = 0;
    int intTemp;
    char *blobTemp = (char *)malloc(sizeof(int));
    //save number of data blocks in the blob
    memcpy(blobTemp, &numData, sizeof(int));
    blobOffset += sizeof(int);
    blobSize += sizeof(int);
    //save blocks
    //int - name length
    //char * - name
    //int - type
    //int - size
    //int - length
    //char (size*length) - data
    for(int d=0;d<numData;d++)
    {
        blobSize += sizeof(int)*4+strlen(dataName[d])+1+dataLength[d]*dataSize[d];
        blobTemp = (char *)realloc(blobTemp, blobSize);
        intTemp = strlen(dataName[d])+1;
        memcpy(&blobTemp[blobOffset], &intTemp, sizeof(int));
        blobOffset += sizeof(int);
        memcpy(&blobTemp[blobOffset], dataName[d], intTemp);
        blobOffset += intTemp;
        memcpy(&blobTemp[blobOffset], &dataType[d], sizeof(int));
        blobOffset += sizeof(int);
        memcpy(&blobTemp[blobOffset], &dataSize[d], sizeof(int));
        blobOffset += sizeof(int);
        memcpy(&blobTemp[blobOffset], &dataLength[d], sizeof(int));
        blobOffset += sizeof(int);
        memcpy(&blobTemp[blobOffset], data[d], dataLength[d]*dataSize[d]);
        blobOffset += dataLength[d]*dataSize[d];
    }
    *size = blobSize;
    return blobTemp;
}
/*
 loadBlob will take a character array that was previously created by
 saveBlob and fill the ObjectBlob with its contents.
 */
void OTObjectBlob::loadBlob(char *blob)
{
    int numBlocks = 0;
    int blobOffset = 0;
    memcpy(&numBlocks, &blob[blobOffset], sizeof(int));
    blobOffset += sizeof(int);
    int nameLength;
    char *nameTemp;
    int typeTemp;
    int sizeTemp;
    int lengthTemp;
    char *dataTemp;
    for(int d=0;d<numBlocks;d++)
    {
        memcpy(&nameLength, &blob[blobOffset], sizeof(int));
        blobOffset+=sizeof(int);
        nameTemp = &blob[blobOffset];
        blobOffset += nameLength;
        memcpy(&typeTemp, &blob[blobOffset], sizeof(int));
        blobOffset += sizeof(int);
        memcpy(&sizeTemp, &blob[blobOffset], sizeof(int));
        blobOffset += sizeof(int);
        memcpy(&lengthTemp, &blob[blobOffset], sizeof(int));
        blobOffset += sizeof(int);
        dataTemp = &blob[blobOffset];
        addData(nameTemp, dataTemp, typeTemp, lengthTemp);
        blobOffset += lengthTemp*sizeTemp;
    }
}
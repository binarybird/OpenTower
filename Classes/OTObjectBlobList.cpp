#include "OTObjectBlobList.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

USING_NS_OT

OTObjectBlobList::OTObjectBlobList()
{
    numBlobs = 0;
    blobName = NULL;
    blobs = NULL;

	this->classType = OTOBJECTBLOBLIST;
}
OTObjectBlobList::~OTObjectBlobList()
{
    for(int b=0;b<numBlobs;b++)
    {
        free(blobName[b]);
        delete blobs[b];
    }
    free(blobName);
    free(blobs);
}
int OTObjectBlobList::getNumBlobs()
{
    return numBlobs;
}
/*
 addBlob will create a new ObjectBlob identified by name and return it
 */
OTObjectBlob *OTObjectBlobList::addBlob(char *name)
{
    if(getBlobIdx(name) >= 0)return NULL;
    printf("Adding Blob: %s\n",name);
    numBlobs++;
    blobName = (char **)realloc(blobName, sizeof(char *)*numBlobs);
    blobName[numBlobs-1] = strdup(name);
    blobs = (OTObjectBlob **)realloc(blobs, sizeof(OTObjectBlob *)*numBlobs);
    blobs[numBlobs-1] = new OTObjectBlob;
    return blobs[numBlobs-1];
}
/*
 getBlob(int idx) returns the ObjectBlob located at idx
 */
OTObjectBlob *OTObjectBlobList::getBlob(int idx)
{
    if(idx >= 0 && idx < numBlobs)
    {
        return blobs[idx];
    }
    return NULL;
}
/*
 getBlob(char *name) returns the named ObjectBlob
 */
OTObjectBlob *OTObjectBlobList::getBlob(char *name)
{
    for(int b=0;b<numBlobs;b++)
    {
        if(strcmp(blobName[b],name) == 0)
        {
            return blobs[b];
        }
    }
    printf("Object Blob List Error: Couldn't find data handle '%s'.\n",name);
    return NULL;
}
/*
 getBlobIdx get the internal index of the named ObjectBlob
 */
int OTObjectBlobList::getBlobIdx(char *name)
{
    for(int b=0;b<numBlobs;b++)
    {
        if(strcmp(blobName[b],name) == 0)
        {
            return b;
        }
    }
    printf("Object Blob List Error: Couldn't find data handle '%s'.\n",name);
    return -1;
}
/*
 save writes all of the contained ObjectBlobs to the file identified by filename
 */
bool OTObjectBlobList::save(char *filename)
{
    FILE *outfile = fopen(filename, "wb");
    if(outfile == NULL)return false;
    printf("Writing out %i blobs.\n",numBlobs);
    fwrite(&numBlobs, sizeof(int), 1, outfile);
    int blobNameLength = 0;
    int blobSize = 0;
    char *blobData;
    for(int b=0;b<numBlobs;b++)
    {
        blobNameLength = strlen(blobName[b])+1;
        fwrite(&blobNameLength, sizeof(int), 1, outfile);
        fwrite(blobName[b], 1, blobNameLength, outfile);
        blobData = blobs[b]->saveBlob(&blobSize);
        fwrite(&blobSize, sizeof(int), 1, outfile);
        fwrite(blobData, 1, blobSize, outfile);
        free(blobData);
    }
    fclose(outfile);
    return true;
}
/*
 load reads the ObjectBlobList file identified by filename
 */
bool OTObjectBlobList::load(char *filename)
{
    FILE *infile = fopen(filename, "rb");
    if(infile == NULL)return false;
    int numBlobsTemp = 0;
    fread(&numBlobsTemp, sizeof(int), 1, infile);
    printf("Reading in %i blobs.\n",numBlobsTemp);
    int blobNameLength = 0;
    int blobSize = 0;
    char *blobNameTemp = (char *)malloc(1);
    blobNameTemp[0] = 0;
    OTObjectBlob *newBlob;
    for(int b=0;b<numBlobsTemp;b++)
    {
        fread(&blobNameLength, sizeof(int), 1, infile);
        printf("Reading in blob name of length %i.\n",blobNameLength);
        blobNameTemp = (char *)realloc(blobNameTemp, blobNameLength);
        fread(blobNameTemp, 1, blobNameLength, infile);
        printf("Blob name temp = %s\n",blobNameTemp);
        newBlob = addBlob(blobNameTemp);
        if(newBlob == NULL)
        {
            fclose(infile);
            free(blobNameTemp);
            return false;
        }
        fread(&blobSize, sizeof(int), 1, infile);
        char *blobData = (char *)malloc(blobSize);
        fread(blobData, 1, blobSize, infile);
        newBlob->loadBlob(blobData);
        free(blobData);
    }
    free(blobNameTemp);
    return true;
}
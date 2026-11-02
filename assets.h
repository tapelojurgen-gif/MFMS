/* assets.h - Asset Management module */
#ifndef ASSETS_H
#define ASSETS_H

#include "utils.h"

typedef struct {
    int    id;
    char   name[NAME_LEN];
    char   type[NAME_LEN];
    double purchaseValue;
    char   department[NAME_LEN];
    char   condition[COND_LEN];
} Asset;

void         assetMenu(void);
int          addAsset(void);                          /* 1 = added, 0 = storage full */
void         displayAssets(void);
void         searchAsset(void);
int          findAssetById(int id);                   /* index, or -1 if not found */
int          getAssetCount(void);
const Asset *getAsset(int index);                     /* NULL if index is invalid */

#endif

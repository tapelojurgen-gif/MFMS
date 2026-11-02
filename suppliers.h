/* suppliers.h - Supplier Management module */
#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#include "utils.h"

typedef struct {
    int  id;
    char name[NAME_LEN];
    char email[EMAIL_LEN];
    char telephone[PHONE_LEN];
    char location[NAME_LEN];
} Supplier;

void            supplierMenu(void);
int             addSupplier(void);                    /* 1 = added, 0 = storage full */
void            displaySuppliers(void);
void            searchSupplier(void);
int             findSupplierById(int id);             /* index, or -1 if not found */
int             getSupplierCount(void);
const Supplier *getSupplier(int index);               /* NULL if index is invalid */

#endif

#ifndef SUPPLIERS_H       
#define SUPPLIERS_H       
                          
                          
#define MAX_SUPPLIERS 50  
                          
                          
typedef struct            
{                         
    int supplierID;       
    char supplierName[50];
    char email[50];       
    char telephone[20];   
    char location[40];    
} Supplier;               
                          
                          
void supplierMenu();      
void addSupplier();       
void displaySuppliers();  
void searchSupplier();    
                          
                          
#endif                    






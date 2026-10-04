#include <stdio.h>
#include <string.h>
int main(){
    char Name[10][50];
    char ID[10][10];
    char email[10][50];
    char telephone[10][20];
    char town[10][50];
   for (int i = 0;i < 10; i++){
       printf("Enter Supplier Name: %d\n",i+1);
     printf("Enter Supplier Name :");
    fgets(Name[i], sizeof(Name[i]), stdin);   
   

     printf("Enter Supplier ID:");
    fgets(ID[i], sizeof(ID[i]), stdin);

     printf("Enter Supplier Email:");
    fgets(email[i], sizeof(email[i]), stdin);

     printf("Enter Supplier Telephone Number:");
    fgets(telephone[i], sizeof(telephone[i]), stdin);

     printf("Enter Supplier Town:");
    fgets(town[i], sizeof(town[i]), stdin);
}
   printf("\n===============SUPPLIER_INFORMATION=======================\n");

for(int i=0; i<10; i++){
    printf("\nSupplier %d\n", i+1);
    printf("SUPPLIER NAME IS: %s",Name[i]);
    printf("SUPPLIER ID: %s", ID[i]);
    printf("SUPPLIER EMAIL: %s",email[i]);
    printf("SUPPLIER TELEPHONE: %s",telephone[i]);
    printf("SUPPLIER TOWM: %s",town[i]);
}

 return 0;   
}
#include <stdio.h> #include <string.h>
#define MAX_EMPLOYEES 100
#define MAX_BUDGETS 50
#define MAX_SUPPLIERS 100
#define MAX_ASSETS 100
/* =========================
STRUCTURES ========================= */
 
struct Employee { int id;
char name[50]; char department[50]; float basicSalary; float housingAllowance; float transportAllowance;
};
struct Budget { char department[50]; float allocated; float expenditure;
};
struct Supplier
{ int id;
char name[50]; char email[50]; char telephone[20]; char location[50];
};
struct Asset
{ int id;
char name[50]; char type[50]; float purchaseValue; char department[50]; char condition[30];
};
/* =========================
FUNCTION DECLARATIONS ========================= */
void displayMenu(); void addEmployee(); void displayEmployees(); void searchEmployee();
float calculateSalary(struct Employee employee); void addBudget(); void displayBudgets(); void addSupplier(); void displaySuppliers();
 
void searchSupplier(); void addAsset(); void displayAssets(); void searchAsset(); void employeeReport(); void budgetReport(); void supplierReport(); void assetReport(); void displayReports();
/* ========================= GLOBAL ARRAYS =========================
*/ struct Employee employees[MAX_EMPLOYEES]; struct Budget budgets[MAX_BUDGETS]; struct Supplier suppliers[MAX_SUPPLIERS]; struct Asset assets[MAX_ASSETS]; int employeeCount = 0; int budgetCount = 0; int supplierCount = 0; int assetCount = 0;
/* ========================= MAIN FUNCTION
=========================
*/ int main() { int choice; do { displayMenu(); printf("Enter your choice: "); scanf("%d", &choice); switch (choice)
{ case 1: addEmployee(); break; case 2: addBudget(); break; case 3:
addSupplier(); break; case 4:
addAsset(); break; case 5:
displayReports(); break; case 6: printf("\nThank you for using MFMS.\n"); break; default:
printf("\nInvalid choice. Please try again.\n");
}
} while (choice != 6); return 0;
}
 
/* ========================= MAIN MENU ========================= */ void
displayMenu() { printf("\n");
printf("========================================\n"); printf(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n"); printf("========================================\n");
printf("1. Employee Management\n"); printf("2. Budget Management\n"); printf("3. Supplier Management\n"); printf("4. Asset Management\n"); printf("5. Reports\n"); printf("6. Exit\n"); printf("========================================\n");
}
/* =========================
EMPLOYEE MANAGEMENT =========================
*/ void addEmployee() { if (employeeCount >= MAX_EMPLOYEES) {
printf("Employee storage is full.\n"); return;
}
printf("\n===== ADD EMPLOYEE =====\n");
printf("Enter Employee ID: "); scanf("%d", &employees[employeeCount].id); printf("Enter Employee Name: ");
scanf(" %[^\n]", employees[employeeCount].name); printf("Enter Department: ");
scanf(" %[^\n]", employees[employeeCount].department); printf("Enter Basic Salary: ");
scanf("%f", &employees[employeeCount].basicSalary); printf("Enter Housing Allowance: ");
scanf("%f", &employees[employeeCount].housingAllowance); printf("Enter Transport Allowance: ");
scanf("%f", &employees[employeeCount].transportAllowance); if (employees[employeeCount].basicSalary < 0 || employees[employeeCount].housingAllowance < 0 || employees[employeeCount].transportAllowance < 0)
{ printf("Salary values cannot be negative.\n"); return;
}
employeeCount++;
 
printf("Employee added successfully.\n");
}
void displayEmployees() { int i;
printf("\n===== EMPLOYEE LIST =====\n");
if (employeeCount == 0) { printf("No employees registered.\n"); return;
}
for (i = 0; i < employeeCount; i++) { printf("\nEmployee ID: %d\n", employees[i].id); printf("Name: %s\n", employees[i].name); printf("Department: %s\n", employees[i].department); printf("Basic Salary: N$%.2f\n", employees[i].basicSalary); printf("Housing Allowance:
N$%.2f\n", employees[i].housingAllowance); printf("Transport Allowance: N$%.2f\n", employees[i].transportAllowance); printf("Gross Salary:
N$%.2f\n", calculateSalary(employees[i]));
}
}
void searchEmployee() { int id;
int i;
printf("\nEnter Employee ID to search: ");
scanf("%d", &id); for (i = 0; i < employeeCount; i++) { if (employees[i].id == id) { printf("\nEmployee Found\n"); printf("ID: %d\n", employees[i].id); printf("Name: %s\n", employees[i].name); printf("Department: %s\n", employees[i].department); printf("Gross Salary: N$%.2f\n", calculateSalary(employees[i])); return;
}
}
printf("Employee not found.\n");
}
float calculateSalary(struct Employee employee)
{ return employee.basicSalary
+ employee.housingAllowance
+ employee.transportAllowance;
}
/* ========================= BUDGET MANAGEMENT =========================
*/ void addBudget() { if (budgetCount >= MAX_BUDGETS) {
 
printf("Budget storage is full.\n"); return;
}
printf("\n===== ADD BUDGET =====\n");
printf("Enter Department: ");
scanf(" %[^\n]", budgets[budgetCount].department); printf("Enter Allocated Budget: "); scanf("%f", &budgets[budgetCount].allocated); printf("Enter Expenditure: ");
scanf("%f", &budgets[budgetCount].expenditure); if (budgets[budgetCount].allocated < 0 || budgets[budgetCount].expenditure < 0)
{ printf("Budget values cannot be negative.\n"); return;
}
budgetCount++;
printf("Budget added successfully.\n");
}
void displayBudgets() { int i; float
remaining;
printf("\n===== BUDGET INFORMATION =====\n");
if (budgetCount == 0) { printf("No budgets registered.\n"); return;
}
for (i = 0; i < budgetCount; i++) { remaining = budgets[i].allocated - budgets[i].expenditure; printf("\nDepartment: %s\n", budgets[i].department); printf("Allocated Budget: N$%.2f\n", budgets[i].allocated); printf("Expenditure: N$%.2f\n", budgets[i].expenditure); printf("Remaining Budget: N$%.2f\n", remaining); if (budgets[i].expenditure > budgets[i].allocated)
{ printf("Status: OVER BUDGET\n");
} else {
printf("Status: WITHIN BUDGET\n");
}
}
}
 
/* =========================
SUPPLIER MANAGEMENT ========================= */
void addSupplier() { if (supplierCount >= MAX_SUPPLIERS) {
printf("Supplier storage is full.\n"); return;
}
printf("\n===== ADD SUPPLIER =====\n");
printf("Enter Supplier ID: "); scanf("%d", &suppliers[supplierCount].id); printf("Enter Supplier Name: "); scanf(" %[^\n]", suppliers[supplierCount].name); printf("Enter Email: ");
scanf(" %[^\n]", suppliers[supplierCount].email); printf("Enter Telephone: ");
scanf(" %[^\n]", suppliers[supplierCount].telephone); printf("Enter Town/Location: ");
scanf(" %[^\n]", suppliers[supplierCount].location); supplierCount++;
printf("Supplier added successfully.\n");
}
void displaySuppliers() { int i;
printf("\n===== SUPPLIER LIST =====\n");
if (supplierCount == 0) { printf("No suppliers registered.\n"); return;
}
for (i = 0; i < supplierCount; i++)
{ printf("\nSupplier ID: %d\n", suppliers[i].id); printf("Name: %s\n", suppliers[i].name); printf("Email: %s\n", suppliers[i].email); printf("Telephone: %s\n", suppliers[i].telephone); printf("Location: %s\n", suppliers[i].location);
}
}
void  searchSupplier()
{ int id; int i;
 
printf("\nEnter Supplier ID to search: "); scanf("%d", &id); for (i = 0; i < supplierCount; i++) { if (suppliers[i].id == id) { printf("\nSupplier Found\n"); printf("Name: %s\n", suppliers[i].name); printf("Email: %s\n", suppliers[i].email); printf("Telephone: %s\n", suppliers[i].telephone); printf("Location: %s\n", suppliers[i].location); return;
}
}
printf("Supplier not found.\n");
}
/* ========================= ASSET MANAGEMENT ========================= */
void addAsset() { if (assetCount >= MAX_ASSETS) {

printf("Asset storage is full.\n"); return;
}
printf("\n===== ADD ASSET =====\n"); printf("Enter Asset ID: "); scanf("%d", &assets[assetCount].id); printf("Enter Asset Name: "); scanf(" %[^\n]", assets[assetCount].name); printf("Enter Asset Type: "); scanf(" %[^\n]", assets[assetCount].type); printf("Enter Purchase Value: "); scanf("%f", &assets[assetCount].purchaseValue); printf("Enter Department: "); scanf(" %[^\n]", assets[assetCount].department); printf("Enter Condition: "); scanf(" %[^\n]", assets[assetCount].condition); if (assets[assetCount].purchaseValue < 0)
{ printf("Purchase value cannot be negative.\n"); return;
}
assetCount++; printf("Asset added successfully.\n");
}
void displayAssets() {
 
int i;
printf("\n===== ASSET REGISTER =====\n");
if (assetCount == 0) { printf("No assets registered.\n"); return;
}
for (i = 0; i < assetCount; i++) { printf("\nAsset ID: %d\n", assets[i].id); printf("Asset Name: %s\n", assets[i].name); printf("Asset Type: %s\n", assets[i].type); printf("Purchase Value: N$%.2f\n", assets[i].purchaseValue); printf("Department: %s\n", assets[i].department); printf("Condition: %s\n", assets[i].condition);
}
}
void searchAsset()
{ int id; int i;
printf("\nEnter Asset ID to search: "); scanf("%d", &id); for (i = 0; i < assetCount; i++) { if (assets[i].id == id) { printf("\nAsset Found\n"); printf("Name: %s\n", assets[i].name); printf("Type: %s\n", assets[i].type);
printf("Value: N$%.2f\n", assets[i].purchaseValue); printf("Department: %s\n", assets[i].department); printf("Condition: %s\n", assets[i].condition); return;
}
}
printf("Asset not found.\n");
}
/* ========================= REPORTS ========================= */
void employeeReport() { int i;
float total = 0; float highest = 0; float lowest = 0; if (employeeCount == 0)
{ printf("\nNo employee data available.\n"); return;
}
 
for (i = 0; i < employeeCount; i++) { float salary = calculateSalary(employees[i]); total += salary; if (i == 0) { highest = salary; lowest = salary;
}
if (salary > highest) highest = salary; if (salary < lowest) lowest = salary;
}
printf("\n===== EMPLOYEE REPORT =====\n");
printf("Total Employees: %d\n", employeeCount); printf("Average Salary: N$%.2f\n", total / employeeCount); printf("Highest Salary:
N$%.2f\n", highest); printf("Lowest Salary:
N$%.2f\n", lowest);
}
void budgetReport() {
int i; float totalAllocated = 0; float totalExpenditure = 0; printf("\n===== BUDGET REPORT =====\n"); if
(budgetCount == 0) { printf("No budget data available.\n"); return;
}
for (i = 0; i < budgetCount; i++)
{ totalAllocated += budgets[i].allocated; totalExpenditure += budgets[i].expenditure;
}
printf("Total Allocated Budget: N$%.2f\n", totalAllocated);
printf("Total Expenditure: N$%.2f\n", totalExpenditure); printf("Remaining Budget: N$%.2f\n", totalAllocated - totalExpenditure); printf("\nDepartments Over Budget:\n"); for (i = 0; i < budgetCount; i++)
{ if (budgets[i].expenditure > budgets[i].allocated) { printf("- %s\n", budgets[i].department);
}
}
}
 
void supplierReport() { printf("\n===== SUPPLIER REPORT =====\n");
displaySuppliers();
}
void assetReport() { printf("\n===== ASSET REPORT =====\n"); displayAssets();
}
void displayReports() { int choice; do
{ printf("\n===== REPORTS
=====\n"); printf("1. Employee Report\n"); printf("2. Budget Report\n"); printf("3. Supplier Report\n"); printf("4. Asset Report\n"); printf("5. Return to Main Menu\n"); printf("Enter your choice: "); scanf("%d", &choice); switch (choice)
{ case 1: employeeReport(); break; case 2: budgetReport(); break; case 3:
supplierReport(); break; case 4: assetReport(); break; case 5: break; default: printf("Invalid choice.\n");
}
} while (choice != 5);
}

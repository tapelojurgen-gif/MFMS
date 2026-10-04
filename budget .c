
Budget Management Functions
addBudget()
Adds a department, allocated budget and expenditure.
displayBudgets()
Displays all stored departmental budget information.
calculateBudget()
Calculates the remaining budget for a selected department.
checkExceededBudgets()
Identifies departments whose expenditure exceeds their allocated budget.
budgetMenu()
Provides navigation for the Budget Management module.
1.	Data Structure
A structure is used to keep the related information for one department together. An array of these structures allows multiple departments to be stored.
typedef struct
{
    int departmentID;     char departmentName[50];     double allocatedBudget;     double expenditure; } Budget;
Budget budgets[MAX_DEPARTMENTS]; int budgetCount = 0;
2.	Complete budget.h
#ifndef BUDGET_H
#define BUDGET_H #define MAX_DEPARTMENTS 20
typedef struct
{
    int departmentID;     char departmentName[50];     double allocatedBudget;     double expenditure; } Budget;
void budgetMenu(); void addBudget(); void displayBudgets(); void calculateBudget(); void checkExceededBudgets();
#endif
 3.	Complete budget.c
#include <stdio.h>
#include <string.h>
#include "budget.h"
Budget budgets[MAX_DEPARTMENTS]; int budgetCount = 0;
void addBudget()
{
    if (budgetCount >= MAX_DEPARTMENTS)
    {
        printf("\nMaximum number of departments reached.\n");         return;     }     printf("\n===== ADD DEPARTMENTAL BUDGET =====\n");
    printf("Enter Department ID: ");     scanf("%d", &budgets[budgetCount].departmentID);     getchar();
    printf("Enter Department Name: ");     fgets(budgets[budgetCount].departmentName,           sizeof(budgets[budgetCount].departmentName), stdin);
    budgets[budgetCount].departmentName[
        strcspn(budgets[budgetCount].departmentName, "\n")     ] = '\0';
    printf("Enter Allocated Budget (N$): ");     scanf("%lf", &budgets[budgetCount].allocatedBudget);
    while (budgets[budgetCount].allocatedBudget < 0)
    {
        printf("Budget cannot be negative.\n");         printf("Enter Allocated Budget again (N$): ");         scanf("%lf", &budgets[budgetCount].allocatedBudget);     }
    printf("Enter Expenditure (N$): ");     scanf("%lf", &budgets[budgetCount].expenditure);
    while (budgets[budgetCount].expenditure < 0)
    {
        printf("Expenditure cannot be negative.\n");         printf("Enter Expenditure again (N$): ");         scanf("%lf", &budgets[budgetCount].expenditure);     }     budgetCount++;
    printf("\nBudget added successfully!\n"); }
void displayBudgets()
{     int i;
    if (budgetCount == 0)
    {
        printf("\nNo budget information available.\n");         return;     }     printf("\n================ BUDGET INFORMATION ================\n");
    for (i = 0; i < budgetCount; i++)
    {         double remaining;
        remaining = budgets[i].allocatedBudget                     budgets[i].expenditure;
        printf("\nDepartment ID: %d\n",                budgets[i].departmentID);
        printf("Department: %s\n",                budgets[i].departmentName);
        printf("Allocated Budget: N$%.2f\n",                budgets[i].allocatedBudget);
        printf("Expenditure: N$%.2f\n",                budgets[i].expenditure);         if (remaining >= 0)
        {
            printf("Remaining Budget: N$%.2f\n",                    remaining);
            printf("Status: WITHIN BUDGET\n");
        }         else         {
            printf("Amount Over Budget: N$%.2f\n",                    -remaining);
            printf("Status: OVER BUDGET\n");         }
        printf("---------------------------------------------\n");
    }
}
void calculateBudget()
{     int id;     int i;     int found = 0;     printf("\n===== CALCULATE REMAINING BUDGET =====\n");
    printf("Enter Department ID: ");     scanf("%d", &id);
    for (i = 0; i < budgetCount; i++)
    {
        if (budgets[i].departmentID == id)
        {             double remaining;
            remaining = budgets[i].allocatedBudget                         budgets[i].expenditure;
            printf("\nDepartment: %s\n",                    budgets[i].departmentName);
            printf("Allocated Budget: N$%.2f\n",                    budgets[i].allocatedBudget);
            printf("Expenditure: N$%.2f\n",                    budgets[i].expenditure);
            printf("Remaining Budget: N$%.2f\n",                    remaining);
            if (remaining >= 0)
            {
                printf("Status: WITHIN BUDGET\n");
            }             else             {
                printf("Status: OVER BUDGET\n");                 printf("Amount Over Budget: N$%.2f\n",
                       -remaining);
            }
            found = 1;             break;
        }
    }
    if (!found)
    {
        printf("\nDepartment not found.\n");
    }
}
void checkExceededBudgets()
{     int i;     int found = 0;     printf("\n===== DEPARTMENTS OVER BUDGET =====\n");
    for (i = 0; i < budgetCount; i++)
    {
        if (budgets[i].expenditure >             budgets[i].allocatedBudget)
        {             double amountOver;
            amountOver = budgets[i].expenditure                          budgets[i].allocatedBudget;             printf("\nDepartment: %s\n",                    budgets[i].departmentName);
            printf("Allocated Budget: N$%.2f\n",                    budgets[i].allocatedBudget);
            printf("Expenditure: N$%.2f\n",                    budgets[i].expenditure);
            printf("Amount Over Budget: N$%.2f\n",                    amountOver);
            found = 1;
        }
    }
    if (!found)
    {
        printf("No departments have exceeded their budgets.\n");
    }
}
void budgetMenu()
{     int choice;
    do     {         printf("\n");
        printf("====================================\n");         printf("       BUDGET MANAGEMENT\n");         printf("====================================\n");         printf("1. Add Departmental Budget\n");         printf("2. Display Budget Information\n");         printf("3. Calculate Remaining Budget\n");         printf("4. Check Departments Over Budget\n");         printf("5. Return to Main Menu\n");         printf("====================================\n");
        printf("Enter your choice: ");         scanf("%d", &choice);
        switch (choice)         {             case 1:                 addBudget();                 break;
            case 2:                 displayBudgets();                 break;
            case 3:                 calculateBudget();                 break;
            case 4:                 checkExceededBudgets();                 break;
            case 5:                 printf("Returning to main menu...\n");                 break;
            default:
                printf("Invalid choice. Please try again.\n");         }
    } while (choice != 5);
}
4.	Connecting the Module to main.c
The main program should include the budget header file and call budgetMenu() when the user selects Budget Management from the main menu.
#include "budget.h" ...
case 2:     budgetMenu();     break;
5.	Program Flow
MAIN MENU
   |
   +-- 1. Employee Management
   |
   +-- 2. Budget Management
          |
          +-- Add Departmental Budget
          +-- Display Budget Information
          +-- Calculate Remaining Budget
          +-- Check Departments Over Budget
          +-- Return to Main Menu
   |
   +-- 3. Supplier Management
   |
   +-- 4. Asset Management
   |
   +-- 5. Reports
   |
   +-- 6. Exit
6.	Main Calculation
Remaining Budget = Allocated Budget − Expenditure
If the remaining budget is zero or positive, the department is within budget. If expenses are greater than the allocated budget, the department is over budget.
Example:
Allocated Budget = N$500000
Expenditure      = N$420000
Remaining = 500000 - 420000
          = N$80000
Status = WITHIN BUDGET

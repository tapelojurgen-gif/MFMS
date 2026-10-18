
#include <stdio.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

void employeeReport(void)
{
    int i;
    float total = 0;
    float highest = 0;
    float lowest = 0;

    if (employeeCount == 0) {
        printf("\nNo employee data available.\n");
        return;
    }

    for (i = 0; i < employeeCount; i++) {
        float salary = calculateSalary(employees[i]);
        total += salary;

        if (i == 0) {
            highest = salary;
            lowest = salary;
        }

        if (salary > highest)
            highest = salary;

        if (salary < lowest)
            lowest = salary;
    }

    printf("\n===== EMPLOYEE REPORT =====\n");
    printf("Total Employees: %d\n", employeeCount);
    printf("Average Salary: N$%.2f\n",
           total / employeeCount);
    printf("Highest Salary: N$%.2f\n", highest);
    printf("Lowest Salary: N$%.2f\n", lowest);
}

void budgetReport(void)
{
    int i;
    float totalAllocated = 0;
    float totalExpenditure = 0;

    printf("\n===== BUDGET REPORT =====\n");

    if (budgetCount == 0) {
        printf("No budget data available.\n");
        return;
    }

    for (i = 0; i < budgetCount; i++) {
        totalAllocated += budgets[i].allocated;
        totalExpenditure += budgets[i].expenditure;
    }

    printf("Total Allocated Budget: N$%.2f\n",
           totalAllocated);
    printf("Total Expenditure: N$%.2f\n",
           totalExpenditure);
    printf("Remaining Budget: N$%.2f\n",
           totalAllocated - totalExpenditure);

    printf("\nDepartments Over Budget:\n");

    for (i = 0; i < budgetCount; i++) {
        if (budgets[i].expenditure > budgets[i].allocated) {
            printf("- %s\n", budgets[i].department);
        }
    }
}

void supplierReport(void)
{
    printf("\n===== SUPPLIER REPORT =====\n");
    displaySuppliers();
}

void assetReport(void)
{
    printf("\n===== ASSET REPORT =====\n");
    displayAssets();
}

void displayReports(void)
{
    int choice;

    do {
        printf("\n===== REPORTS =====\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Return to Main Menu\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                employeeReport();
                break;

            case 2:
                budgetReport();
                break;

            case 3:
                supplierReport();
                break;

            case 4:
                assetReport();
                break;

            case 5:
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 5);
}

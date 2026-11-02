
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

#define LABEL_LEN (NAME_LEN * 2 + 8)

void employeeReport(void)
{
    int i;
    int count = getEmployeeCount();
    int highestIndex = 0;
    int lowestIndex = 0;
    double total = 0;
    double gross, highest, lowest;
    char label[LABEL_LEN];

    printf("\n===== EMPLOYEE REPORT =====\n");
    if (count == 0) {
        printf("No employee data available.\n");
        return;
    }

    printf("%-6s %-38s %16s\n", "ID", "Name - Department", "Gross Salary");
    printf("------------------------------------------------------------------\n");
    for (i = 0; i < count; i++) {
        const Employee *e = getEmployee(i);
        gross = calculateGrossSalary(e);
        total += gross;

        if (gross > calculateGrossSalary(getEmployee(highestIndex))) {
            highestIndex = i;
        }
        if (gross < calculateGrossSalary(getEmployee(lowestIndex))) {
            lowestIndex = i;
        }
        buildLabel(label, sizeof label, e->name, " - ", e->department);
        printf("%-6d %-38.38s N$%13.2f\n", e->id, label, gross);
    }

    highest = calculateGrossSalary(getEmployee(highestIndex));
    lowest  = calculateGrossSalary(getEmployee(lowestIndex));
    printf("------------------------------------------------------------------\n");
    printf("Total Employees:  %d\n", count);
    printf("Total Payroll:    N$%.2f\n", total);
    printf("Average Salary:   N$%.2f\n", total / count);
    printf("Highest Salary:   N$%.2f (%s)\n", highest, getEmployee(highestIndex)->name);
    printf("Lowest Salary:    N$%.2f (%s)\n", lowest, getEmployee(lowestIndex)->name);
}

void budgetReport(void)
{
    int i;
    int overCount = 0;
    int count = getBudgetCount();
    double totalAllocated = 0;
    double totalExpenditure = 0;

    printf("\n===== BUDGET REPORT =====\n");
    if (count == 0) {
        printf("No budget data available.\n");
        return;
    }

    printf("%-24s %15s %15s %15s  %s\n",
           "Department", "Allocated", "Spent", "Remaining", "Status");
    printf("---------------------------------------------------------------------------------\n");
    for (i = 0; i < count; i++) {
        const Budget *b = getBudget(i);
        totalAllocated   += b->allocated;
        totalExpenditure += b->expenditure;
        printf("%-24.24s N$%12.2f N$%12.2f N$%12.2f  %s\n",
               b->department, b->allocated, b->expenditure,
               calculateRemaining(b), budgetStatus(b));
    }
    printf("---------------------------------------------------------------------------------\n");
    printf("Total Allocated Budget: N$%.2f\n", totalAllocated);
    printf("Total Expenditure:      N$%.2f\n", totalExpenditure);
    printf("Total Remaining Budget: N$%.2f\n", totalAllocated - totalExpenditure);

    printf("\nDepartments Over Budget:\n");
    for (i = 0; i < count; i++) {
        if (isOverBudget(getBudget(i))) {
            printf("  - %s\n", getBudget(i)->department);
            overCount++;
        }
    }
    if (overCount == 0) {
        printf("  None. All departments are within budget.\n");
    }
}

void supplierReport(void)
{
    int i;
    int count = getSupplierCount();
    char label[LABEL_LEN];

    printf("\n===== SUPPLIER REPORT =====\n");
    if (count == 0) {
        printf("No supplier data available.\n");
        return;
    }

    printf("%-6s %-34s %-28s %-16s\n", "ID", "Name - Location", "Email", "Telephone");
    printf("-------------------------------------------------------------------------------------\n");
    for (i = 0; i < count; i++) {
        const Supplier *s = getSupplier(i);
        buildLabel(label, sizeof label, s->name, " - ", s->location);
        printf("%-6d %-34.34s %-28.28s %-16.16s\n", s->id, label, s->email, s->telephone);
    }
    printf("-------------------------------------------------------------------------------------\n");
    printf("Total Suppliers: %d\n", count);
}

void assetReport(void)
{
    int i;
    int count = getAssetCount();
    int good = 0, fair = 0, poor = 0;
    double totalValue = 0;
    char label[LABEL_LEN];

    printf("\n===== ASSET REPORT =====\n");
    if (count == 0) {
        printf("No asset data available.\n");
        return;
    }

    printf("%-6s %-32s %-16s %-10s %14s\n", "ID", "Name (Type)", "Department", "Condition", "Value");
    printf("-----------------------------------------------------------------------------------\n");
    for (i = 0; i < count; i++) {
        const Asset *a = getAsset(i);
        totalValue += a->purchaseValue;

        if (strcmp(a->condition, "Good") == 0) {
            good++;
        } else if (strcmp(a->condition, "Fair") == 0) {
            fair++;
        } else {
            poor++;
        }

        buildLabel(label, sizeof label, a->name, " - ", a->type);
        printf("%-6d %-32.32s %-16.16s %-10s N$%11.2f\n",
               a->id, label, a->department, a->condition, a->purchaseValue);
    }
    printf("-----------------------------------------------------------------------------------\n");
    printf("Total Assets:      %d\n", count);
    printf("Total Asset Value: N$%.2f\n", totalValue);
    printf("Condition summary: %d Good, %d Fair, %d Poor\n", good, fair, poor);
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
        choice = promptInt("Enter your choice: ", 1, 5);

        switch (choice) {
        case 1: employeeReport(); break;
        case 2: budgetReport();   break;
        case 3: supplierReport(); break;
        case 4: assetReport();    break;
        case 5:                   break;
        }
    } while (choice != 5);
}

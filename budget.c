
#include <stdio.h>
#include <string.h>
#include "budget.h"

static Budget budgets[MAX_BUDGETS];
static int budgetCount = 0;

double calculateRemaining(const Budget *budget)
{
    return budget->allocated - budget->expenditure;
}

int isOverBudget(const Budget *budget)
{
    return budget->expenditure > budget->allocated;
}

const char *budgetStatus(const Budget *budget)
{
    if (isOverBudget(budget)) {
        return "OVER BUDGET";
    }
    return "WITHIN BUDGET";
}

/* Department names are compared ignoring upper/lower case (uses strcmp inside). */
int findBudgetByDepartment(const char *department)
{
    int i;
    for (i = 0; i < budgetCount; i++) {
        if (equalsIgnoreCase(budgets[i].department, department)) {
            return i;
        }
    }
    return -1;
}

int getBudgetCount(void)
{
    return budgetCount;
}

const Budget *getBudget(int index)
{
    if (index < 0 || index >= budgetCount) {
        return NULL;
    }
    return &budgets[index];
}

static void printBudget(const Budget *b)
{
    printf("\nDepartment:       %s\n", b->department);
    printf("Allocated Budget: N$%.2f\n", b->allocated);
    printf("Expenditure:      N$%.2f\n", b->expenditure);
    printf("Remaining Budget: N$%.2f\n", calculateRemaining(b));
    printf("Status:           %s\n", budgetStatus(b));
}

int addBudget(void)
{
    char department[NAME_LEN];
    Budget *b;

    if (budgetCount >= MAX_BUDGETS) {
        printf("Budget storage is full.\n");
        return 0;
    }

    printf("\n===== ADD DEPARTMENT BUDGET =====\n");
    for (;;) {
        promptText("Enter Department: ", department, sizeof department);
        if (findBudgetByDepartment(department) == -1) {
            break;
        }
        printf("  Error: a budget for \"%s\" already exists.\n", department);
    }

    b = &budgets[budgetCount];
    strcpy(b->department, department);
    b->allocated   = promptMoney("Enter Allocated Budget (N$): ");
    b->expenditure = promptMoney("Enter Expenditure so far (N$, 0 if none): ");

    budgetCount++;
    printf("Budget added successfully. Status: %s\n", budgetStatus(b));
    return 1;
}

void recordExpenditure(void)
{
    char department[NAME_LEN];
    double amount;
    int i;

    printf("\n===== RECORD EXPENDITURE =====\n");
    if (budgetCount == 0) {
        printf("No budgets registered. Add a department budget first.\n");
        return;
    }
    promptText("Enter Department: ", department, sizeof department);
    i = findBudgetByDepartment(department);
    if (i < 0) {
        printf("Department \"%s\" not found.\n", department);
        return;
    }

    amount = promptMoney("Enter amount spent (N$): ");
    budgets[i].expenditure += amount;

    printf("Expenditure recorded.\n");
    printf("Remaining Budget: N$%.2f\n", calculateRemaining(&budgets[i]));
    printf("Status: %s\n", budgetStatus(&budgets[i]));
    if (isOverBudget(&budgets[i])) {
        printf("WARNING: %s has exceeded its allocated budget!\n", budgets[i].department);
    }
}

void displayBudgets(void)
{
    int i;

    printf("\n===== BUDGET INFORMATION =====\n");
    if (budgetCount == 0) {
        printf("No budgets registered.\n");
        return;
    }
    for (i = 0; i < budgetCount; i++) {
        printBudget(&budgets[i]);
    }
}

void displayOverBudget(void)
{
    int i;
    int count = 0;

    printf("\n===== DEPARTMENTS OVER BUDGET =====\n");
    for (i = 0; i < budgetCount; i++) {
        if (isOverBudget(&budgets[i])) {
            printBudget(&budgets[i]);
            count++;
        }
    }
    if (count == 0) {
        printf("No department has exceeded its budget.\n");
    }
}

void budgetMenu(void)
{
    int choice;

    do {
        printf("\n===== BUDGET MANAGEMENT =====\n");
        printf("1. Add Department Budget\n");
        printf("2. Record Expenditure\n");
        printf("3. Display All Budgets (remaining & status)\n");
        printf("4. Show Departments Over Budget\n");
        printf("5. Back to Main Menu\n");
        choice = promptInt("Enter your choice: ", 1, 5);

        switch (choice) {
        case 1: addBudget();          break;
        case 2: recordExpenditure();  break;
        case 3: displayBudgets();     break;
        case 4: displayOverBudget();  break;
        case 5:                       break;
        }
    } while (choice != 5);
}

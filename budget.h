/* budget.h - Budget Management module */
#ifndef BUDGET_H
#define BUDGET_H

#include "utils.h"

typedef struct {
    char   department[NAME_LEN];
    double allocated;
    double expenditure;
} Budget;

void         budgetMenu(void);
int          addBudget(void);                         /* 1 = added, 0 = not added */
void         recordExpenditure(void);
void         displayBudgets(void);
void         displayOverBudget(void);
double       calculateRemaining(const Budget *budget);
int          isOverBudget(const Budget *budget);      /* 1 = over, 0 = within */
const char  *budgetStatus(const Budget *budget);
int          findBudgetByDepartment(const char *department);   /* index, or -1 */
int          getBudgetCount(void);
const Budget *getBudget(int index);                   /* NULL if index is invalid */

#endif

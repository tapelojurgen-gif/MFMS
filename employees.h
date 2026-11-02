/* employees.h - Employee Management module */
#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include "utils.h"

typedef struct {
    int    id;
    char   name[NAME_LEN];
    char   department[NAME_LEN];
    double basicSalary;
    double housingAllowance;
    double transportAllowance;
} Employee;

void           employeeMenu(void);
int            addEmployee(void);                     /* 1 = added, 0 = storage full */
void           displayEmployees(void);
void           searchEmployee(void);
void           showEmployeeSalary(void);
double         calculateGrossSalary(const Employee *employee);
int            findEmployeeById(int id);              /* index, or -1 if not found */
int            getEmployeeCount(void);
const Employee *getEmployee(int index);               /* NULL if index is invalid */

#endif

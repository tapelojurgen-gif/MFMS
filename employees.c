
#include <stdio.h>
#include <string.h>
#include "employees.h"

static Employee employees[MAX_EMPLOYEES];
static int employeeCount = 0;

double calculateGrossSalary(const Employee *employee)
{
    return employee->basicSalary
         + employee->housingAllowance
         + employee->transportAllowance;
}

int findEmployeeById(int id)
{
    int i;
    for (i = 0; i < employeeCount; i++) {
        if (employees[i].id == id) {
            return i;
        }
    }
    return -1;
}

int getEmployeeCount(void)
{
    return employeeCount;
}

const Employee *getEmployee(int index)
{
    if (index < 0 || index >= employeeCount) {
        return NULL;
    }
    return &employees[index];
}

static void printEmployee(const Employee *e)
{
    double gross = calculateGrossSalary(e);

    printf("\nEmployee ID:          %d\n", e->id);
    printf("Name:                 %s\n", e->name);
    printf("Department:           %s\n", e->department);
    printf("Basic Salary:         N$%.2f\n", e->basicSalary);
    printf("Housing Allowance:    N$%.2f\n", e->housingAllowance);
    printf("Transport Allowance:  N$%.2f\n", e->transportAllowance);
    printf("Gross Monthly Salary: N$%.2f\n", gross);
}

int addEmployee(void)
{
    Employee *e;
    int id;

    if (employeeCount >= MAX_EMPLOYEES) {
        printf("Employee storage is full.\n");
        return 0;
    }

    printf("\n===== ADD EMPLOYEE =====\n");
    for (;;) {
        id = promptInt("Enter Employee ID (positive number): ", 1, 999999);
        if (findEmployeeById(id) == -1) {
            break;
        }
        printf("  Error: an employee with ID %d already exists.\n", id);
    }

    e = &employees[employeeCount];
    e->id = id;
    promptText("Enter Employee Name: ", e->name, sizeof e->name);
    promptText("Enter Department: ", e->department, sizeof e->department);
    e->basicSalary        = promptMoney("Enter Basic Salary (N$): ");
    e->housingAllowance   = promptMoney("Enter Housing Allowance (N$): ");
    e->transportAllowance = promptMoney("Enter Transport Allowance (N$): ");

    employeeCount++;
    printf("Employee added successfully.\n");
    return 1;
}

void displayEmployees(void)
{
    int i;

    printf("\n===== EMPLOYEE LIST =====\n");
    if (employeeCount == 0) {
        printf("No employees registered.\n");
        return;
    }
    for (i = 0; i < employeeCount; i++) {
        printEmployee(&employees[i]);
    }
    printf("\nTotal employees: %d\n", employeeCount);
}

void searchEmployee(void)
{
    int choice, id, i;
    int found = 0;
    char term[NAME_LEN];

    printf("\n===== SEARCH EMPLOYEE =====\n");
    if (employeeCount == 0) {
        printf("No employees registered.\n");
        return;
    }
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    choice = promptInt("Enter your choice: ", 1, 2);

    if (choice == 1) {
        id = promptInt("Enter Employee ID to search: ", 1, 999999);
        i = findEmployeeById(id);
        if (i >= 0) {
            printf("\nEmployee Found");
            printEmployee(&employees[i]);
        } else {
            printf("Employee not found.\n");
        }
    } else {
        promptText("Enter name (or part of a name): ", term, sizeof term);
        for (i = 0; i < employeeCount; i++) {
            if (containsIgnoreCase(employees[i].name, term)) {
                printEmployee(&employees[i]);
                found++;
            }
        }
        if (found == 0) {
            printf("No employee found matching \"%s\".\n", term);
        } else {
            printf("\n%d employee(s) found.\n", found);
        }
    }
}

void showEmployeeSalary(void)
{
    int id, i;
    double gross;

    printf("\n===== SALARY INFORMATION =====\n");
    if (employeeCount == 0) {
        printf("No employees registered.\n");
        return;
    }
    id = promptInt("Enter Employee ID: ", 1, 999999);
    i = findEmployeeById(id);
    if (i < 0) {
        printf("Employee not found.\n");
        return;
    }
    gross = calculateGrossSalary(&employees[i]);
    printf("\nSalary breakdown for %s\n", employees[i].name);
    printf("  Basic Salary:        N$%.2f\n", employees[i].basicSalary);
    printf("  Housing Allowance:   N$%.2f\n", employees[i].housingAllowance);
    printf("  Transport Allowance: N$%.2f\n", employees[i].transportAllowance);
    printf("  Gross Monthly:       N$%.2f\n", gross);
    printf("  Gross Annual:        N$%.2f\n", gross * 12);
}

void employeeMenu(void)
{
    int choice;

    do {
        printf("\n===== EMPLOYEE MANAGEMENT =====\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee\n");
        printf("4. Calculate Employee Salary\n");
        printf("5. Back to Main Menu\n");
        choice = promptInt("Enter your choice: ", 1, 5);

        switch (choice) {
        case 1: addEmployee();        break;
        case 2: displayEmployees();   break;
        case 3: searchEmployee();     break;
        case 4: showEmployeeSalary(); break;
        case 5:                       break;
        }
    } while (choice != 5);
}

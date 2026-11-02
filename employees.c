/* =========================
EMPLOYEE MANAGEMENT ========================= */
void addEmployee() {
if (employeeCount >= MAX_EMPLOYEES) {
printf("Employee storage is full.\n");
return;
}
printf("\n===== ADD EMPLOYEE =====\n");
printf("Enter Employee ID: ");
scanf("%d", &employees[employeeCount].id);
printf("Enter Employee Name: ");
scanf(" %[^\n]", employees[employeeCount].name);
printf("Enter Department: ");
scanf(" %[^\n]", employees[employeeCount].department);
printf("Enter Basic Salary: ");
scanf("%f", &employees[employeeCount].basicSalary);
printf("Enter Housing Allowance: ");
scanf("%f", &employees[employeeCount].housingAllowance);
printf("Enter Transport Allowance: ");
scanf("%f", &employees[employeeCount].transportAllowance);
if (employees[employeeCount].basicSalary < 0 ||
employees[employeeCount].housingAllowance < 0 ||
employees[employeeCount].transportAllowance < 0) {
printf("Salary values cannot be negative.\n");
return;
}
employeeCount++;
printf("Employee added successfully.\n");
}
void displayEmployees() {
int i;
printf("\n===== EMPLOYEE LIST =====\n");
if (employeeCount == 0) {
printf("No employees registered.\n");
return;
}
for (i = 0; i < employeeCount; i++) {
printf("\nEmployee ID: %d\n", employees[i].id);
printf("Name: %s\n", employees[i].name);
printf("Department: %s\n", employees[i].department);
printf("Basic Salary: N$%.2f\n", employees[i].basicSalary);
printf("Housing Allowance: N$%.2f\n", employees[i].housingAllowance);
printf("Transport Allowance: N$%.2f\n", employees[i].transportAllowance);
printf("Gross Salary: N$%.2f\n", calculateSalary(employees[i]));
}
}
void searchEmployee() {
int id;
int i;
printf("\nEnter Employee ID to search: ");
scanf("%d", &id);
for (i = 0; i < employeeCount; i++) {
if (employees[i].id == id) {
printf("\nEmployee Found\n");
printf("ID: %d\n", employees[i].id);
printf("Name: %s\n", employees[i].name);
printf("Department: %s\n", employees[i].department);
printf("Gross Salary: N$%.2f\n", calculateSalary(employees[i]));
return;
}
}
printf("Employee not found.\n");
}
float calculateSalary(struct Employee employee) {
return employee.basicSalary
+ employee.housingAllowance
+ employee.transportAllowance;
}
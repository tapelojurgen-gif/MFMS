# Municipal Financial Management System (MFMS)

**Course:** PAP521S – Programming in Practice (Group Project A)
**Language:** ANSI C (C99) | **Compiler:** GCC | **Editor:** Visual Studio Code | **Version control:** Git & GitHub

## Group Members
<!-- CONFIRM the final member list and spellings before submission -->
| Name | Student No. |
|------|-------------|
| Amaufufu Diogenus | 224082493 |
| Esco T. Haukena | 223069760 |
| Jurgen Narseb | 225106930 |
| Osama Bin Laden Shooya | 226039625 |
| Lazarus Thomas | 224019589 |
| Ester Amunime | 221117385 |

## Project Description
MFMS is a menu-driven C program that helps a municipality manage basic financial and
administrative information. It has modules for employees, departmental budgets, suppliers and
municipal assets, lets the user search for records, and produces summary reports.

## Features
1. **Employee Management** – add, display, search (by ID or name) and calculate salary (basic + housing + transport, monthly and annual).
2. **Budget Management** – add a department budget, record expenditure, calculate remaining budget, show status (WITHIN / OVER BUDGET) and list departments that exceeded their budget.
3. **Supplier Management** – add, display and search suppliers (by ID, name or location). Stores name, email, telephone and location.
4. **Asset Management** – register, display and search assets (by ID or name). Stores ID, name, type, value, department and condition.
5. **Reports** – employee, budget, supplier and asset reports.

## How to Build and Run
All source files are in the project folder. From a terminal in that folder:

```
gcc -std=c99 -Wall -Wextra -pedantic -o MFMS main.c utils.c employees.c budget.c suppliers.c assets.c reports.c
```

Run it:

- Windows: `MFMS.exe` (if you build with `-o MFMS.exe`) or `.\MFMS`
- Linux / macOS: `./MFMS`

If `make` is installed you can simply type `make`.
The program compiles with **no warnings** under the flags above.

## Project Structure
| File | Purpose |
|------|---------|
| `main.c` | Main menu and navigation only |
| `utils.h / utils.c` | Shared constants, safe input functions and validation helpers |
| `employees.h / employees.c` | Employee module |
| `budget.h / budget.c` | Budget module |
| `suppliers.h / suppliers.c` | Supplier module |
| `assets.h / assets.c` | Asset module |
| `reports.h / reports.c` | Reports module |
| `Makefile` | Optional build script |

Every header uses include guards (`#ifndef / #define / #endif`).

## Input Validation
- Menu choices outside the range, letters or blank input are rejected and the user is asked again.
- Negative salaries, allowances, budgets, expenditure and asset values are rejected.
- Empty names (employee, department, supplier, asset) are rejected, as is text that is too long.
- Duplicate IDs (employee, supplier, asset) and duplicate department budgets are rejected.
- Supplier email must look like `name@example.com`; telephone must contain 7–15 digits.
- Non-numeric text typed where a number is expected is rejected (no crash or endless loop).

## Programming Concepts Used
Variables and data types (`int`, `double`, `char[]`, `struct`) · arithmetic, relational and logical
operators · `if / else` and `switch` · `for`, `while` and `do-while` loops · arrays of structs ·
string functions (`strlen`, `strcmp`, `strcpy`, `strcat`, `strstr`, `strchr`) · functions with
parameters and return values · input validation.

Where the string functions are used:
- `strlen` – empty/too-long checks, phone and label length checks (`utils.c`)
- `strcmp` – department matching and condition counting (`utils.c`, `budget.c`, `reports.c`)
- `strcpy` – storing validated text and the asset condition (`utils.c`, `assets.c`)
- `strcat` – building "Name - Location" style labels for reports (`utils.c`, `reports.c`)

## Design Decisions (Foundation for Project B)
- Each module owns its data (a private array and counter) and exposes it only through functions
  such as `getEmployeeCount()` and `getEmployee(i)`. Reports never touch another module's arrays.
- Because of this, later extensions (saving to files, dynamic memory, sorting, editing/deleting
  records) can be added inside one module without changing the others.
- All shared limits live in `utils.h`, so capacity can be changed in one place.

## Individual Responsibilities
<!-- CONFIRM: reports were committed by Ester Amunime; README previously credited Esco T. Haukena -->
| Group Member | Responsibility |
|--------------|----------------|
| Lazarus Thomas | Employee Management (`employees.c/.h`) |
| Osama Bin Laden Shooya | Budget Management (`budget.c/.h`) |
| Jurgen Narseb | Supplier Management (`suppliers.c/.h`), testing, documentation, GitHub coordination |
| Amaufufu Diogenus | Asset Management (`assets.c/.h`), functions, integration and data validation (`utils.c/.h`) |
| Esco T. Haukena / Ester Amunime | Reports (`reports.c/.h`) and documentation |

## GitHub
Repository: https://github.com/tapelojurgen-gif/MFMS

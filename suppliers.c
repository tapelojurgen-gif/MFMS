/* suppliers.c - Supplier Management module
 * Owner: Jurgen N. (Supplier Management)
 */
#include <stdio.h>
#include <string.h>
#include "suppliers.h"

static Supplier suppliers[MAX_SUPPLIERS];
static int supplierCount = 0;

/* Look through the array and return the position of the supplier with this ID. */
int findSupplierById(int id)
{
    int i;
    for (i = 0; i < supplierCount; i++) {
        if (suppliers[i].id == id) {
            return i;
        }
    }
    return -1;
}

int getSupplierCount(void)
{
    return supplierCount;
}

const Supplier *getSupplier(int index)
{
    if (index < 0 || index >= supplierCount) {
        return NULL;
    }
    return &suppliers[index];
}

static void printSupplier(const Supplier *s)
{
    printf("\nSupplier ID: %d\n", s->id);
    printf("Name:        %s\n", s->name);
    printf("Email:       %s\n", s->email);
    printf("Telephone:   %s\n", s->telephone);
    printf("Location:    %s\n", s->location);
}

int addSupplier(void)
{
    Supplier *s;
    int id;

    if (supplierCount >= MAX_SUPPLIERS) {
        printf("Supplier storage is full.\n");
        return 0;
    }

    printf("\n===== ADD SUPPLIER =====\n");
    for (;;) {
        id = promptInt("Enter Supplier ID (positive number): ", 1, 999999);
        if (findSupplierById(id) == -1) {
            break;
        }
        printf("  Error: a supplier with ID %d already exists.\n", id);
    }

    s = &suppliers[supplierCount];
    s->id = id;
    promptText("Enter Supplier Name: ", s->name, sizeof s->name);
    promptEmail("Enter Supplier Email: ", s->email, sizeof s->email);
    promptPhone("Enter Supplier Telephone: ", s->telephone, sizeof s->telephone);
    promptText("Enter Supplier Town/Location: ", s->location, sizeof s->location);

    supplierCount++;
    printf("Supplier added successfully.\n");
    return 1;
}

void displaySuppliers(void)
{
    int i;

    printf("\n===== SUPPLIER LIST =====\n");
    if (supplierCount == 0) {
        printf("No suppliers registered.\n");
        return;
    }
    for (i = 0; i < supplierCount; i++) {
        printSupplier(&suppliers[i]);
    }
    printf("\nTotal suppliers: %d\n", supplierCount);
}

void searchSupplier(void)
{
    int choice, id, i;
    int found = 0;
    char term[NAME_LEN];

    printf("\n===== SEARCH SUPPLIER =====\n");
    if (supplierCount == 0) {
        printf("No suppliers registered.\n");
        return;
    }
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("3. Search by Location\n");
    choice = promptInt("Enter your choice: ", 1, 3);

    if (choice == 1) {
        id = promptInt("Enter Supplier ID to search: ", 1, 999999);
        i = findSupplierById(id);
        if (i >= 0) {
            printf("\nSupplier Found");
            printSupplier(&suppliers[i]);
        } else {
            printf("Supplier not found.\n");
        }
        return;
    }

    if (choice == 2) {
        promptText("Enter name (or part of a name): ", term, sizeof term);
    } else {
        promptText("Enter town/location: ", term, sizeof term);
    }

    for (i = 0; i < supplierCount; i++) {
        const char *field = (choice == 2) ? suppliers[i].name : suppliers[i].location;
        if (containsIgnoreCase(field, term)) {
            printSupplier(&suppliers[i]);
            found++;
        }
    }
    if (found == 0) {
        printf("No supplier found matching \"%s\".\n", term);
    } else {
        printf("\n%d supplier(s) found.\n", found);
    }
}

void supplierMenu(void)
{
    int choice;

    do {
        printf("\n===== SUPPLIER MANAGEMENT =====\n");
        printf("1. Add Supplier\n");
        printf("2. Display All Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Back to Main Menu\n");
        choice = promptInt("Enter your choice: ", 1, 4);

        switch (choice) {
        case 1: addSupplier();      break;
        case 2: displaySuppliers(); break;
        case 3: searchSupplier();   break;
        case 4:                     break;
        }
    } while (choice != 4);
}

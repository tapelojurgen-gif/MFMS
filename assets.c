/* assets.c - Asset Management module
 * Owner: Diogenus A. (Asset Management)
 */
#include <stdio.h>
#include <string.h>
#include "assets.h"

static Asset assets[MAX_ASSETS];
static int assetCount = 0;

static const char *conditionNames[] = { "Good", "Fair", "Poor" };

int findAssetById(int id)
{
    int i;
    for (i = 0; i < assetCount; i++) {
        if (assets[i].id == id) {
            return i;
        }
    }
    return -1;
}

int getAssetCount(void)
{
    return assetCount;
}

const Asset *getAsset(int index)
{
    if (index < 0 || index >= assetCount) {
        return NULL;
    }
    return &assets[index];
}

static void printAsset(const Asset *a)
{
    printf("\nAsset ID:       %d\n", a->id);
    printf("Asset Name:     %s\n", a->name);
    printf("Asset Type:     %s\n", a->type);
    printf("Purchase Value: N$%.2f\n", a->purchaseValue);
    printf("Department:     %s\n", a->department);
    printf("Condition:      %s\n", a->condition);
}

int addAsset(void)
{
    Asset *a;
    int id, choice;

    if (assetCount >= MAX_ASSETS) {
        printf("Asset storage is full.\n");
        return 0;
    }

    printf("\n===== ADD ASSET =====\n");
    for (;;) {
        id = promptInt("Enter Asset ID (positive number): ", 1, 999999);
        if (findAssetById(id) == -1) {
            break;
        }
        printf("  Error: an asset with ID %d already exists.\n", id);
    }

    a = &assets[assetCount];
    a->id = id;
    promptText("Enter Asset Name: ", a->name, sizeof a->name);
    promptText("Enter Asset Type: ", a->type, sizeof a->type);
    a->purchaseValue = promptMoney("Enter Purchase Value (N$): ");
    promptText("Enter Department: ", a->department, sizeof a->department);

    printf("Condition: 1. Good  2. Fair  3. Poor\n");
    choice = promptInt("Select condition: ", 1, 3);
    strcpy(a->condition, conditionNames[choice - 1]);

    assetCount++;
    printf("Asset added successfully.\n");
    return 1;
}

void displayAssets(void)
{
    int i;

    printf("\n===== ASSET REGISTER =====\n");
    if (assetCount == 0) {
        printf("No assets registered.\n");
        return;
    }
    for (i = 0; i < assetCount; i++) {
        printAsset(&assets[i]);
    }
    printf("\nTotal assets: %d\n", assetCount);
}

void searchAsset(void)
{
    int choice, id, i;
    int found = 0;
    char term[NAME_LEN];

    printf("\n===== SEARCH ASSET =====\n");
    if (assetCount == 0) {
        printf("No assets registered.\n");
        return;
    }
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    choice = promptInt("Enter your choice: ", 1, 2);

    if (choice == 1) {
        id = promptInt("Enter Asset ID to search: ", 1, 999999);
        i = findAssetById(id);
        if (i >= 0) {
            printf("\nAsset Found");
            printAsset(&assets[i]);
        } else {
            printf("Asset not found.\n");
        }
    } else {
        promptText("Enter name (or part of a name): ", term, sizeof term);
        for (i = 0; i < assetCount; i++) {
            if (containsIgnoreCase(assets[i].name, term)) {
                printAsset(&assets[i]);
                found++;
            }
        }
        if (found == 0) {
            printf("No asset found matching \"%s\".\n", term);
        } else {
            printf("\n%d asset(s) found.\n", found);
        }
    }
}

void assetMenu(void)
{
    int choice;

    do {
        printf("\n===== ASSET MANAGEMENT =====\n");
        printf("1. Register Asset\n");
        printf("2. Display All Assets\n");
        printf("3. Search Asset\n");
        printf("4. Back to Main Menu\n");
        choice = promptInt("Enter your choice: ", 1, 4);

        switch (choice) {
        case 1: addAsset();      break;
        case 2: displayAssets(); break;
        case 3: searchAsset();   break;
        case 4:                  break;
        }
    } while (choice != 4);
}

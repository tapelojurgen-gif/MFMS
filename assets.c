/* ========================= ASSET MANAGEMENT ========================= */
void addAsset() {
if (assetCount >= MAX_ASSETS) {
printf("Asset storage is full.\n");
return;
}
printf("\n===== ADD ASSET =====\n");
printf("Enter Asset ID: ");
scanf("%d", &assets[assetCount].id);
printf("Enter Asset Name: ");
scanf(" %[^\n]", assets[assetCount].name);
printf("Enter Asset Type: ");
scanf(" %[^\n]", assets[assetCount].type);
printf("Enter Purchase Value: ");
scanf("%f", &assets[assetCount].purchaseValue);
printf("Enter Department: ");
scanf(" %[^\n]", assets[assetCount].department);
printf("Enter Condition: ");
scanf(" %[^\n]", assets[assetCount].condition);
if (assets[assetCount].purchaseValue < 0) {
printf("Purchase value cannot be negative.\n");
return;
}
assetCount++;
printf("Asset added successfully.\n");
}
void displayAssets() {
int i;
printf("\n===== ASSET REGISTER =====\n");
if (assetCount == 0) {
printf("No assets registered.\n");
return;
}
for (i = 0; i < assetCount; i++) {
printf("\nAsset ID: %d\n", assets[i].id);
printf("Asset Name: %s\n", assets[i].name);
printf("Asset Type: %s\n", assets[i].type);
printf("Purchase Value: N$%.2f\n", assets[i].purchaseValue);
printf("Department: %s\n", assets[i].department);
printf("Condition: %s\n", assets[i].condition);
}
}
void searchAsset() {
int id;
int i;
printf("\nEnter Asset ID to search: ");
scanf("%d", &id);
for (i = 0; i < assetCount; i++) {
if (assets[i].id == id) {
printf("\nAsset Found\n");
printf("Name: %s\n", assets[i].name);
printf("Type: %s\n",
assets[i].type);
printf("Value: N$%.2f\n", assets[i].purchaseValue);
printf("Department: %s\n", assets[i].department);
printf("Condition: %s\n", assets[i].condition);
return;
}
}
printf("Asset not found.\n");
}
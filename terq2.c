#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for an item in the inventory
struct Item {
    char name[100];
    int quantity;
    struct Item* left;
    struct Item* right;
};

// Function to create a new item
struct Item* createItem(const char* name, int quantity) {
    struct Item* newItem = (struct Item*)malloc(sizeof(struct Item));
    strcpy(newItem->name, name);
    newItem->quantity = quantity;
    newItem->left = newItem->right = NULL;
    return newItem;
}

// Function to insert an item into the inventory
struct Item* insert(struct Item* root, const char* name, int quantity) {
    if (root == NULL) {
        return createItem(name, quantity);
    }

    int cmp = strcmp(name, root->name);
    if (cmp < 0) {
        root->left = insert(root->left, name, quantity);
    } else if (cmp > 0) {
        root->right = insert(root->right, name, quantity);
    }

    return root;
}

// Function to perform postorder traversal and update inventory
void updateInventory(struct Item* root) {
    if (root != NULL) {
        updateInventory(root->left);
        updateInventory(root->right);

        // Perform inventory update operation
        printf("Updating inventory: %s (Quantity: %d)\n", root->name, root->quantity);
        // Your inventory update logic goes here
        // For example, you can update the quantity of the item in a database or file
    }
}

int main() {
    struct Item* root = NULL;
    char name[100];
    int quantity;

    int choice;
    do {
        printf("1. Add Item\n");
        printf("2. Update Inventory\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the item name: ");
                scanf(" %[^\n]s", name);
                printf("Enter the item quantity: ");
                scanf("%d", &quantity);
                root = insert(root, name, quantity);
                printf("Item added successfully.\n");
                break;
            case 2:
                printf("Updating inventory using postorder traversal:\n");
                updateInventory(root);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
        printf("\n");
    } while (choice != 3);

    return 0;
}


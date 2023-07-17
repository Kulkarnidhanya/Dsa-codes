#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a student
struct Student {
    char name[100];
    struct Student* left;
    struct Student* right;
};

// Function to create a new student
struct Student* createStudent(const char* name) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    strcpy(newStudent->name, name);
    newStudent->left = newStudent->right = NULL;
    return newStudent;
}

// Function to insert a student into the BST
struct Student* insert(struct Student* root, const char* name) {
    if (root == NULL) {
        return createStudent(name);
    }

    int cmp = strcmp(name, root->name);
    if (cmp < 0) {
        root->left = insert(root->left, name);
    } else if (cmp > 0) {
        root->right = insert(root->right, name);
    }

    return root;
}

// Function to perform inorder traversal
void inorderTraversal(struct Student* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%s\n", root->name);
        inorderTraversal(root->right);
    }
}

int main() {
    struct Student* root = NULL;
    char name[100];

    int choice;
    do {
        printf("1. Add Student\n");
        printf("2. View Students (In alphabetical order)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the student name: ");
                scanf(" %[^\n]s", name);
                root = insert(root, name);
                printf("Student added successfully.\n");
                break;
            case 2:
                printf("Students (In alphabetical order):\n");
                inorderTraversal(root);
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char word[50];
    char meaning[200];
    struct Node* left;
    struct Node* right;
};

// Create new node
struct Node* createNode(char* word, char* meaning) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->word, word);
    strcpy(newNode->meaning, meaning);
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert new word
struct Node* insert(struct Node* root, char* word, char* meaning) {
    if (root == NULL)
        return createNode(word, meaning);

    int cmp = strcmp(word, root->word);
    if (cmp < 0)
        root->left = insert(root->left, word, meaning);
    else if (cmp > 0)
        root->right = insert(root->right, word, meaning);
    else
        printf("Word already exists.\n");
    return root;
}

// Search for word
struct Node* search(struct Node* root, char* word) {
    if (root == NULL || strcmp(root->word, word) == 0)
        return root;
    if (strcmp(word, root->word) < 0)
        return search(root->left, word);
    else
        return search(root->right, word);
}

// Update meaning
void update(struct Node* root, char* word, char* newMeaning) {
    struct Node* temp = search(root, word);
    if (temp == NULL)
        printf("Word not found.\n");
    else {
        strcpy(temp->meaning, newMeaning);
        printf("Meaning updated successfully.\n");
    }
}

// Find minimum node
struct Node* findMin(struct Node* node) {
    while (node && node->left != NULL)
        node = node->left;
    return node;
}

// Delete word
struct Node* delete(struct Node* root, char* word) {
    if (root == NULL) {
        printf("Word not found.\n");
        return root;
    }

    int cmp = strcmp(word, root->word);
    if (cmp < 0)
        root->left = delete(root->left, word);
    else if (cmp > 0)
        root->right = delete(root->right, word);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = findMin(root->right);
        strcpy(root->word, temp->word);
        strcpy(root->meaning, temp->meaning);
        root->right = delete(root->right, temp->word);
    }
    return root;
}

// Display dictionary (in-order traversal)
void display(struct Node* root) {
    if (root == NULL)
        return;
    display(root->left);
    printf("%s : %s\n", root->word, root->meaning);
    display(root->right);
}

// Free tree
void freeTree(struct Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Menu-driven main
int main() {
    struct Node* root = NULL;
    int choice;
    char word[50], meaning[200];

    while (1) {
        printf("\n--- Dictionary Menu ---\n");
        printf("1. Insert word\n");
        printf("2. Search word\n");
        printf("3. Update meaning\n");
        printf("4. Delete word\n");
        printf("5. Display dictionary\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
        case 1:
            printf("Enter word: ");
            fgets(word, sizeof(word), stdin);
            word[strcspn(word, "\n")] = '\0';
            printf("Enter meaning: ");
            fgets(meaning, sizeof(meaning), stdin);
            meaning[strcspn(meaning, "\n")] = '\0';
            root = insert(root, word, meaning);
            break;

        case 2:
            printf("Enter word to search: ");
            fgets(word, sizeof(word), stdin);
            word[strcspn(word, "\n")] = '\0';
            {
                struct Node* found = search(root, word);
                if (found)
                    printf("%s : %s\n", found->word, found->meaning);
                else
                    printf("Word not found.\n");
            }
            break;

        case 3:
            printf("Enter word to update: ");
            fgets(word, sizeof(word), stdin);
            word[strcspn(word, "\n")] = '\0';
            printf("Enter new meaning: ");
            fgets(meaning, sizeof(meaning), stdin);
            meaning[strcspn(meaning, "\n")] = '\0';
            update(root, word, meaning);
            break;

        case 4:
            printf("Enter word to delete: ");
            fgets(word, sizeof(word), stdin);
            word[strcspn(word, "\n")] = '\0';
            root = delete(root, word);
            break;

        case 5:
            printf("\n--- Dictionary (A–Z) ---\n");
            display(root);
            break;

        case 6:
            freeTree(root);
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid choice. Try again.\n");
        }
    }
}

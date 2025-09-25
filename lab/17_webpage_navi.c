#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char url[100];
    struct Node* prev;
    struct Node* next;
};

struct Node* current = NULL;

// Create new webpage node
struct Node* createNode(const char* url) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy_s(newNode->url, sizeof(newNode->url), url);  // fix
    newNode->prev = newNode->next = NULL;
    return newNode;
}

// Visit a new page
void visitPage(const char* url) {
    struct Node* newNode = createNode(url);
    if (current != NULL) {
        // clear forward history
        struct Node* temp = current->next;
        while (temp != NULL) {
            struct Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
        current->next = newNode;
        newNode->prev = current;
    }
    current = newNode;
    printf("Visited: %s\n", url);
}

// Go back
void goBack() {
    if (current == NULL || current->prev == NULL) {
        printf("No previous page.\n");
        return;
    }
    current = current->prev;
    printf("Back to: %s\n", current->url);
}

// Go forward
void goForward() {
    if (current == NULL || current->next == NULL) {
        printf("No forward page.\n");
        return;
    }
    current = current->next;
    printf("Forward to: %s\n", current->url);
}

// Show current page
void showCurrent() {
    if (current == NULL) {
        printf("No page visited yet.\n");
        return;
    }
    printf("Current page: %s\n", current->url);
}

int main() {
    int choice;
    char url[100];

    while (1) {
        printf("\n1. Visit new page\n2. Back\n3. Forward\n4. Show current page\n5. Exit\n");
        printf("Enter choice: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter URL: ");
            scanf_s("%s", url, (unsigned)_countof(url));  // fix
            visitPage(url);
            break;
        case 2:
            goBack();
            break;
        case 3:
            goForward();
            break;
        case 4:
            showCurrent();
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice.\n");
        }
    }
    return 0;
}



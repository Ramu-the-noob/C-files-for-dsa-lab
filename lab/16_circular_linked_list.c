#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* last = NULL;  // last node pointer

// Create new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Insert at end
void insertEnd(int value) {
    struct Node* newNode = createNode(value);
    if (last == NULL) {
        last = newNode;
        last->next = last;  // circular link
        return;
    }
    newNode->next = last->next;
    last->next = newNode;
    last = newNode;
}

// Insert at beginning
void insertBegin(int value) {
    struct Node* newNode = createNode(value);
    if (last == NULL) {
        last = newNode;
        last->next = last;
        return;
    }
    newNode->next = last->next;
    last->next = newNode;
}

// Delete a node by value
void deleteNode(int value) {
    if (last == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node* temp = last->next; // first node
    struct Node* prev = last;

    // Search node
    do {
        if (temp->data == value) break;
        prev = temp;
        temp = temp->next;
    } while (temp != last->next);

    if (temp->data != value) {
        printf("Value not found\n");
        return;
    }

    if (temp == last && temp->next == last) {
        // single node
        last = NULL;
    }
    else {
        prev->next = temp->next;
        if (temp == last) last = prev;
    }
    free(temp);
    printf("%d deleted\n", value);
}

// Display the circular list
void display() {
    if (last == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Node* temp = last->next;
    printf("Circular List: ");
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != last->next);
    printf("(back to head)\n");
}

int main() {
    int choice, value;
    while (1) {
        printf("\n1. Insert at Beginning\n2. Insert at End\n3. Delete Node\n4. Display\n5. Exit\n");
        printf("Enter choice: ");
        scanf_s("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter value: ");
            scanf_s("%d", &value);
            insertBegin(value);
            break;
        case 2:
            printf("Enter value: ");
            scanf_s("%d", &value);
            insertEnd(value);
            break;
        case 3:
            printf("Enter value to delete: ");
            scanf_s("%d", &value);
            deleteNode(value);
            break;
        case 4:
            display();
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}

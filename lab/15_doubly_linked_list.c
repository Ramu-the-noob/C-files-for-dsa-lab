#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Create new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

// Insert at end
void insertEnd(int value, struct Node** head) {
    struct Node* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
}

// Insert at beginning
void insertBegin(int value, struct Node** head) {
    struct Node* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    newNode->next = *head;
    (*head)->prev = newNode;
    *head = newNode;
}

// Delete a node by value
void deleteNode(int value, struct Node** head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Node* temp = *head;
    while (temp != NULL && temp->data != value)
        temp = temp->next;
    if (temp == NULL) {
        printf("Value not found\n");
        return;
    }
    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    else
        *head = temp->next;
    if (temp->next != NULL)
        temp->next->prev = temp->prev;
    free(temp);
    printf("%d deleted\n", value);
}

// Display forward
void displayForward(struct Node* head) {
    struct Node* temp = head;
    if (temp == NULL) {
        printf("List is empty\n");
        return;
    }
    printf("Forward: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Display backward
void displayBackward(struct Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    printf("Backward: NULL <- ");
    while (temp != NULL) {
        printf("%d <- ", temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int choice, value;
    while (1) {
        printf("\n1. Insert at Beginning\n2. Insert at End\n3. Delete Node\n4. Display Forward\n5. Display Backward\n6. Exit\n");
        printf("Enter choice: ");
        scanf_s("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter value: ");
            scanf_s("%d", &value);
            insertBegin(value, &head);
            break;
        case 2:
            printf("Enter value: ");
            scanf_s("%d", &value);
            insertEnd(value, &head);
            break;
        case 3:
            printf("Enter value to delete: ");
            scanf_s("%d", &value);
            deleteNode(value, &head);
            break;
        case 4:
            displayForward(head);
            break;
        case 5:
            displayBackward(head);
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}


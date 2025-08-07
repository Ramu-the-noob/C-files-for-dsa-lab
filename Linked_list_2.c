#include <stdio.h>
#include <stdlib.h>

// Define the node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to insert at the end
void insertAtEnd(struct Node** head_ref, int new_data) {
    // Step 1: Allocate memory for new node
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head_ref; // Used to traverse to the last node

    // Step 2: Assign data and set next to NULL
    new_node->data = new_data;
    new_node->next = NULL;

    // Step 3: If the list is empty, new node becomes the head
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    // Step 4: Traverse to the last node
    while (last->next != NULL) {
        last = last->next;
    }

    // Step 5: Change the next of last node
    last->next = new_node;
}

// Function to print the list
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Main function
int main() {
    struct Node* head = NULL; // Start with empty list

    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);

    printList(head); // Output: 10 -> 20 -> 30 -> NULL

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

// Define the node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to insert at beginning
void insertAtBeginning(struct Node** head_ref, int new_data) {
    // Step 1: Allocate memory for new node
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    // Step 2: Assign data to the new node
    new_node->data = new_data;

    // Step 3: Make next of new node as head
    new_node->next = *head_ref;

    // Step 4: Move the head to point to the new node
    *head_ref = new_node;
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

    insertAtBeginning(&head, 30);
    insertAtBeginning(&head, 20);
    insertAtBeginning(&head, 10);

    printList(head); // Output: 10 -> 20 -> 30 -> NULL

    return 0;
}

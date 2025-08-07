#include <stdio.h>
#include <stdlib.h>

// Define the node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to insert at any position (1-based indexing)
void insertAtPosition(struct Node** head_ref, int new_data, int position) {
    // Create new node
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;

    // If inserting at the beginning
    if (position == 1) {
        new_node->next = *head_ref;
        *head_ref = new_node;
        return;
    }

    struct Node* temp = *head_ref;
    int i;

    // Traverse to the node just before the desired position
    for (i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    // If position is invalid (i.e., too far)
    if (temp == NULL) {
        printf("Error: Position %d is out of bounds.\n", position);
        free(new_node);
        return;
    }

    // Insert the node
    new_node->next = temp->next;
    temp->next = new_node;
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

// Main function to test
int main() {
    struct Node* head = NULL;

    insertAtPosition(&head, 10, 1); // Insert at beginning
    insertAtPosition(&head, 20, 2); // Insert at end
    insertAtPosition(&head, 15, 2); // Insert in the middle
    insertAtPosition(&head, 25, 5); // Invalid position

    printList(head); // Output: 10 -> 15 -> 20 -> NULL

    return 0;
}

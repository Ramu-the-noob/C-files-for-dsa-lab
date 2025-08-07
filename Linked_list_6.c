#include <stdio.h>
#include <stdlib.h>

// Define the node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to delete the last node
void deleteLast(struct Node** head_ref) {
    if (*head_ref == NULL) {
        printf("List is already empty.\n");
        return;
    }

    // If there's only one node
    if ((*head_ref)->next == NULL) {
        free(*head_ref);
        *head_ref = NULL;
        return;
    }

    // Traverse to second last node
    struct Node* temp = *head_ref;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    // temp is now second last node
    free(temp->next);       // Free the last node
    temp->next = NULL;      // Update second last's next to NULL
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

// Utility function to insert at the end (for testing)
void insertAtEnd(struct Node** head_ref, int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    struct Node* temp = *head_ref;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

// Main function to demonstrate deletion
int main() {
    struct Node* head = NULL;

    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30); // List: 10 -> 20 -> 30 -> NULL

    printf("Original list: ");
    printList(head);

    deleteLast(&head); // Deletes 30

    printf("After deleting last node: ");
    printList(head); // Output: 10 -> 20 -> NULL

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

// Define the node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to delete the first node
void deleteFirst(struct Node** head_ref) {
    if (*head_ref == NULL) {
        printf("List is already empty.\n");
        return;
    }

    struct Node* temp = *head_ref;  // Store current head
    *head_ref = temp->next;         // Move head to next node
    free(temp);                     // Free old head
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

// Utility function to insert at the beginning (for testing)
void insertAtBeginning(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = *head_ref;
    *head_ref = new_node;
}

// Main function to demonstrate deletion
int main() {
    struct Node* head = NULL;

    // Insert some test data
    insertAtBeginning(&head, 30);
    insertAtBeginning(&head, 20);
    insertAtBeginning(&head, 10); // List: 10 -> 20 -> 30 -> NULL

    printf("Original List: ");
    printList(head);

    // Delete first element
    deleteFirst(&head); // Should remove 10

    printf("After deleting first node: ");
    printList(head); // Output: 20 -> 30 -> NULL

    return 0;
}

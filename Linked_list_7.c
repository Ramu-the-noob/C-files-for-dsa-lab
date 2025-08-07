#include <stdio.h>
#include <stdlib.h>

// Define node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to delete node at a given position (1-based indexing)
void deleteAtPosition(struct Node** head_ref, int position) {
    if (*head_ref == NULL) {
        printf("List is already empty.\n");
        return;
    }

    // Deleting the first node
    if (position == 1) {
        struct Node* temp = *head_ref;
        *head_ref = temp->next;
        free(temp);
        return;
    }

    struct Node* temp = *head_ref;
    int i;

    // Traverse to the node just before the target
    for (i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    // If position is out of bounds
    if (temp == NULL || temp->next == NULL) {
        printf("Error: Position %d is out of bounds.\n", position);
        return;
    }

    // temp points to (position - 1)th node
    struct Node* node_to_delete = temp->next;
    temp->next = node_to_delete->next;
    free(node_to_delete);
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

// Utility function to insert at end
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

// Main function to test deletion
int main() {
    struct Node* head = NULL;

    // Create list: 10 -> 20 -> 30 -> 40
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);
    insertAtEnd(&head, 40);

    printf("Original list: ");
    printList(head);

    deleteAtPosition(&head, 2); // Deletes 20

    printf("After deleting position 2: ");
    printList(head); // Expected: 10 -> 30 -> 40 -> NULL

    deleteAtPosition(&head, 1); // Deletes 10 (head)

    printf("After deleting position 1: ");
    printList(head); // Expected: 30 -> 40 -> NULL

    deleteAtPosition(&head, 5); // Invalid

    return 0;
}

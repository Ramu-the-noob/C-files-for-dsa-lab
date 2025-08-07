#include <stdio.h>
#include <stdlib.h>

// Define the node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to traverse and print the list
void traverseList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);  // Visit the node
        temp = temp->next;             // Move to the next node
    }
    printf("NULL\n"); // End of list
}

// Utility function to create a new node
struct Node* createNode(int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Main function to demonstrate traversal
int main() {
    // Manually creating a linked list: 10 -> 20 -> 30 -> NULL
    struct Node* head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);

    // Traverse and print the list
    traverseList(head); // Output: 10 -> 20 -> 30 -> NULL

    return 0;
}

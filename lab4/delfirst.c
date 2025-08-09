#include <stdio.h>
#include <stdlib.h>

// Define node
struct Node {
    int data;
    struct Node* next;
};

// delete function
void del(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* temp = *head; 
    *head = temp->next;         
    free(temp);                    
}

// display
void display(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// adding data 
void insert(struct Node** head, int val) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = val;
    node->next = *head;
    *head = node;
}

// Main function 
int main() {
    struct Node* head = NULL;

    // Insert some test data
    insert(&head, 10);
    insert(&head, 20);
    insert(&head, 30); 

    printf("Original List: ");
    display(head);

    // Delete first element
    del(&head);

    printf("After deleting first node: ");
    display(head); 

    return 0;
}

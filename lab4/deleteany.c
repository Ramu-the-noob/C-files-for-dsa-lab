#include <stdio.h>
#include <stdlib.h>

// Define node 
struct Node 
{
    int data;
    struct Node* next;
};

// delete function
void delany(struct Node** head, int pos) 
{
    if (*head == NULL) 
    {
        printf("List is empty.\n");
        return;
    }

    // if first node
    if (pos == 1) 
    {
        struct Node* temp = *head;
        *head = temp->next;
        free(temp);
        return;
    }

    struct Node* temp = *head;

    // set node to pos - 1
    for (int i = 1; i < pos - 1 && temp != NULL; i++)
    {
        temp = temp->next;
    }

    // If position is out of bounds
    if (temp == NULL || temp->next == NULL) 
    {
        printf("Error: Position %d is out of bounds.\n", pos);
        return;
    }

    // delete 
    struct Node* node_to_delete = temp->next;
    temp->next = node_to_delete->next;
    free(node_to_delete);
}

// display function
void display(struct Node* head) 
{
    struct Node* temp = head;
    while (temp != NULL) 
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// insert some val function
void insert(struct Node** head, int val) 
{
    
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = val;
    node->next = *head;

    *head = node;
}

// Main function
int main() 
{
    struct Node* head = NULL;

    insert(&head, 10);
    insert(&head, 20);
    insert(&head, 30);
    insert(&head, 40);

    printf("Original list: ");
    display(head);

    delany(&head, 2); 

    printf("After deleting position 2: ");
    display(head); 

    delany(&head, 1); 

    printf("After deleting position 1: ");
    display(head); 

    delany(&head, 5); 
    return 0;
}

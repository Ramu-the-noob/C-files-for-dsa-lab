#include <stdio.h>
#include <stdlib.h>

//define struct
struct Node 
{
    int data;
    struct Node* next;
};

// insert function
void insert(struct Node** head, int val, int pos) 
{
    // Create new node
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = val;
    node->next = NULL;

    // If inserting at the beginning
    if (pos == 1) 
    {
        node->next = *head;
        *head = node;
        return;
    }

    struct Node* temp = *head;
    int i;

    // Traverse to the node just before the desired position
    for (i = 1; i < pos - 1 && temp != NULL; i++) 
    {
        temp = temp->next;
    }

    // If position is too far
    if (temp == NULL) 
    {
        printf("Error: Position %d is out of bounds.\n", pos);
        free(node);
        return;
    }

    // Insert the node
    node->next = temp->next;
    temp->next = node;
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

// Main function
int main() 
{
    struct Node* head = NULL;

    insert(&head, 10, 1); 
    insert(&head, 20, 2); 
    insert(&head, 15, 3); 
    insert(&head, 25, 5); 

    display(head); 

    return 0;
}

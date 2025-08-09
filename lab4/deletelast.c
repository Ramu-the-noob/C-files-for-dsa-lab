#include <stdio.h>
#include <stdlib.h>

// Define node
struct Node 
{
    int data;
    struct Node* next;
};

//delete function
void delLast(struct Node** head) 
{
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    // If there's only one node
    if ((*head)->next == NULL) 
    {
        free(*head);
        *head = NULL;
        return;
    }

    // if there are two or more nodes
    struct Node* temp = *head;
    while (temp->next->next != NULL) 
    {
        temp = temp->next;
    }

    // delete last
    free(temp->next);       
    temp->next = NULL;      
}

// display function
void display(struct Node* head) 
{
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// inserting value function
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

    printf("Original list: ");
    display(head);

    delLast(&head); 

    printf("After deleting last node: ");
    display(head); 

    return 0;
}

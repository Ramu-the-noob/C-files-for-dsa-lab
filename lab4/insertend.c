#include <stdio.h>
#include <stdlib.h>

// Define struct
struct Node 
{
    int data;
    struct Node* next;
};

//insert function
void insert(struct Node** head, int val) 
{
    //Allocate memory
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head; // Used to traverse to the last node

    //Assign data
    node->data = val;
    node->next = NULL;

    //If the list is empty
    if (*head == NULL) 
    {
        *head = node;
        return;
    }

    //Traverse to the last node
    while (last->next != NULL) 
    {
        last = last->next;
    }

    //Change the next of last node
    last->next = node;
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

    insert(&head, 10);
    insert(&head, 20);
    insert(&head, 30);

    display(head); 
    return 0;
}

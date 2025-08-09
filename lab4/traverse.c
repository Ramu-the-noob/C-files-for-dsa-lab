#include <stdio.h>
#include <stdlib.h>

//define node
struct Node 
{
    int data;
    struct Node* next;
};

//travese function
void traverse(struct Node* head) 
{
    struct Node* temp = head;
    while (temp != NULL) 
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n"); 
}

//data creation for traversal
struct Node* createNode(int data) 
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Main function 
int main() 
{

    struct Node* head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);

    // Traverse and print the list
    traverse(head); 

    return 0;
}

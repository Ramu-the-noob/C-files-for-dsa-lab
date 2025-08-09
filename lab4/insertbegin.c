#include <stdio.h>
#include <stdlib.h>

// Define the node structure
struct Node {
    int data;
    struct Node* next;
};

//insert function
void insert(struct Node** head, int val) {
    //Allocate memory de
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    //Assign data 
    node->data = val;
    node->next = *head;

   //head = new node
    *head = node;
}

// display Function
void display(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Main 
int main() {
    struct Node* head = NULL; 

    insert(&head, 10);
    insert(&head, 20);
    insert(&head, 30);

    display(head); 

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

// Definition of a node
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Create a new node with given data
Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Insert at head
void insert_at_head(Node **head, int data) {
    Node *new_node = create_node(data);
    new_node->next = *head;
    *head = new_node;
}

// Insert at tail
void insert_at_tail(Node **head, int data) {
    Node *new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

// Insert at given position (0-based). If position is greater than length, insert at tail.
void insert_at_position(Node **head, int data, int position) {
    if (position <= 0 || *head == NULL) {
        // treat as insert at head
        insert_at_head(head, data);
        return;
    }
    Node *temp = *head;
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        // position beyond end, insert at tail
        insert_at_tail(head, data);
        return;
    }
    Node *new_node = create_node(data);
    new_node->next = temp->next;
    temp->next = new_node;
}

// Delete at head
void delete_head(Node **head) {
    if (*head == NULL) return;
    Node *to_delete = *head;
    *head = (*head)->next;
    free(to_delete);
}

// Delete at tail
void delete_tail(Node **head) {
    if (*head == NULL) return;
    if ((*head)->next == NULL) {
        // only one node
        free(*head);
        *head = NULL;
        return;
    }
    Node *temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    // temp->next is last node
    free(temp->next);
    temp->next = NULL;
}

// Delete at position (0-based). If position out of range no deletion.
void delete_at_position(Node **head, int position) {
    if (*head == NULL) return;
    if (position == 0) {
        delete_head(head);
        return;
    }
    Node *temp = *head;
    for (int i = 0; temp->next != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        // nothing to delete
        return;
    }
    Node *to_delete = temp->next;
    temp->next = to_delete->next;
    free(to_delete);
}

// Search for first node containing key. Returns pointer or NULL if not found.
Node *search(Node *head, int key) {
    Node *temp = head;
    while (temp != NULL) {
        if (temp->data == key) return temp;
        temp = temp->next;
    }
    return NULL;
}

// Traverse and print list
void print_list(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Free entire list
void free_list(Node **head) {
    Node *current = *head;
    Node *next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    *head = NULL;
}

// Example usage
int main(void) {
    Node *head = NULL;

    insert_at_head(&head, 5);       // List: 5
    insert_at_tail(&head, 10);      // List: 5 -> 10
    insert_at_head(&head, 3);       // List: 3 -> 5 -> 10
    insert_at_position(&head, 7, 2);// List: 3 -> 5 -> 7 -> 10

    print_list(head);

    delete_at_position(&head, 2);   // deletes "7". List: 3 -> 5 -> 10
    print_list(head);

    delete_head(&head);             // deletes "3". List: 5 -> 10
    print_list(head);

    delete_tail(&head);             // deletes "10". List: 5
    print_list(head);

    Node *found = search(head, 5);
    if (found) {
        printf("Found: %d\n", found->data);
    } else {
        printf("Not found\n");
    }

    free_list(&head);
    return 0;
}


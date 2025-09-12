#include <stdio.h>
#include <stdlib.h>

/* Node structure */
struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
};

/* Create a new node, data initialized, links null */
struct Node *create_node(int data) {
    struct Node *p = malloc(sizeof *p);
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    p->data = data;
    p->prev = NULL;
    p->next = NULL;
    return p;
}

/* Insert at head */
void insert_head(struct Node **head_ref, int data) {
    struct Node *new_node = create_node(data);
    new_node->next = *head_ref;
    if (*head_ref != NULL) {
        (*head_ref)->prev = new_node;
    }
    *head_ref = new_node;
}

/* Insert at tail */
void insert_tail(struct Node **head_ref, int data) {
    struct Node *new_node = create_node(data);
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    struct Node *temp = *head_ref;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
    new_node->prev = temp;
}

/* Insert at position (0-based). If position <= 0, at head. If beyond end, at tail */
void insert_at_position(struct Node **head_ref, int data, int position) {
    if (position <= 0 || *head_ref == NULL) {
        insert_head(head_ref, data);
        return;
    }
    struct Node *temp = *head_ref;
    int i;
    for (i = 0; temp->next != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp->next == NULL && i < position - 1) {
        /* reached tail before desired position */
        insert_tail(head_ref, data);
        return;
    }
    struct Node *new_node = create_node(data);
    new_node->next = temp->next;
    new_node->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = new_node;
    }
    temp->next = new_node;
}

/* Delete head node */
void delete_head(struct Node **head_ref) {
    if (*head_ref == NULL) return;
    struct Node *to_delete = *head_ref;
    *head_ref = to_delete->next;
    if (*head_ref != NULL) {
        (*head_ref)->prev = NULL;
    }
    free(to_delete);
}

/* Delete tail node */
void delete_tail(struct Node **head_ref) {
    if (*head_ref == NULL) return;
    struct Node *temp = *head_ref;
    /* If only one node */
    if (temp->next == NULL) {
        free(temp);
        *head_ref = NULL;
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    /* temp is tail */
    temp->prev->next = NULL;
    free(temp);
}

/* Delete at position (0-based). If position <=0, delete head. If beyond tail, no change */
void delete_at_position(struct Node **head_ref, int position) {
    if (*head_ref == NULL) return;
    if (position <= 0) {
        delete_head(head_ref);
        return;
    }
    struct Node *temp = *head_ref;
    int i;
    for (i = 0; temp != NULL && i < position; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        /* position beyond list */
        return;
    }
    /* Remove temp */
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    free(temp);
}

/* Search for first node with given key, return pointer or NULL */
struct Node *search(struct Node *head, int key) {
    struct Node *temp = head;
    while (temp != NULL) {
        if (temp->data == key) return temp;
        temp = temp->next;
    }
    return NULL;
}

/* Print list forward */
void print_forward(struct Node *head) {
    struct Node *temp = head;
    printf("Forward: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

/* Print list backward: given head, find tail then backward */
void print_backward(struct Node *head) {
    if (head == NULL) {
        printf("Backward: \n");
        return;
    }
    struct Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    printf("Backward: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

/* Free whole list */
void free_list(struct Node **head_ref) {
    struct Node *current = *head_ref;
    struct Node *next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    *head_ref = NULL;
}

/* Example usage */
int main(void) {
    struct Node *head = NULL;

    insert_head(&head, 10);   // list: 10
    insert_tail(&head, 20);   // 10 <-> 20
    insert_head(&head, 5);    // 5 <-> 10 <-> 20
    insert_at_position(&head, 15, 2);  // 5 <-> 10 <-> 15 <-> 20
    print_forward(head);
    print_backward(head);

    delete_at_position(&head, 1);      // delete 10: 5 <-> 15 <-> 20
    print_forward(head);
    print_backward(head);

    delete_head(&head);                // delete 5
    print_forward(head);

    delete_tail(&head);                // delete 20
    print_forward(head);

    struct Node *found = search(head, 15);
    if (found != NULL) {
        printf("Found %d\n", found->data);
    } else {
        printf("Not found\n");
    }

    free_list(&head);
    return 0;
}

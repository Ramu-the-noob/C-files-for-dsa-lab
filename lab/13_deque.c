#include <stdio.h>
#include <stdlib.h>

// Struct node
struct Node {
    int data;
    struct Node* next;
};

// front and rear pointers
struct Deque {
    struct Node* front;
    struct Node* rear;
};

// first node
struct Node* createNode(int val) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = val;
    node->next = NULL;
    return node;
}
// creating double ended queue
struct Deque* createDeque() {
    struct Deque* dq = (struct Deque*)malloc(sizeof(struct Deque));
    dq->front = dq->rear = NULL;
    return dq;
}

// Insert at front 
void insertFront(struct Deque* dq, int value) {
    struct Node* node = createNode(value);
    node->next = dq->front;
    dq->front = node;
    printf("add %d to front \n", value);
    if (dq->rear == NULL) dq->rear = node; // if first node
}

// Insert at rear 
void insertRear(struct Deque* dq, int value) {
    struct Node* node = createNode(value);
    if (dq->rear == NULL) {
        dq->front = dq->rear = node; // if first node
        return;
    }
    dq->rear->next = node;
    dq->rear = node;
    printf("added %d to rear \n", value);
}

// Delete from front 
void deleteFront(struct Deque* dq) {
    if (dq->front == NULL) {
        printf("Deque is empty");
            return;
    }
    // temp node to free up and disconnect deleted nodes
    struct Node* temp = dq->front;
    printf("removed %d from front \n", temp->data);
    dq->front = dq->front->next;
    if (dq->front == NULL) dq->rear = NULL;
    free(temp);
}

// Delete from rear 
void deleteRear(struct Deque* dq) {
    if (dq->rear == NULL) {
        printf("Deque is empty");
            return;
    }
    if (dq->front == dq->rear) { // if single node
        free(dq->rear);
        dq->front = dq->rear = NULL;
        return;
    }
    // traversing to last node
    struct Node* cur = dq->front;
    while (cur->next != dq->rear) cur = cur->next; // find last node
    free(dq->rear);
    dq->rear = cur;
    dq->rear->next = NULL;
}

void display(struct Deque* dq) {
    struct Node* cur = dq->front;
    printf("Deque: ");
    while (cur) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

void delDeque(struct Deque* dq) {
    while (dq->front) {
        deleteFront(dq);
    }
    free(dq);
}

int main(void) {
    struct Deque* dq = createDeque();

    insertRear(dq, 10);
    insertRear(dq, 20);
    insertFront(dq, 5);
    insertFront(dq, 2);

    display(dq);

    deleteFront(dq);
    display(dq);

    deleteRear(dq);
    display(dq);

    delDeque(dq);
    return 0;
}

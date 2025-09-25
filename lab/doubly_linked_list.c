#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

// queue declarations
int queue[SIZE];
int front = -1, rear = -1;

int isFull() {
    return ((front == 0 && rear == SIZE - 1) || (rear + 1) % SIZE == front);
}

int isEmpty() {
    return (front == -1);
}

void enqueue(int value) {
    if (isFull()) {
        printf("Queue is full\n");
        return;
    }
    if (front == -1)  // first element
        front = 0;
    rear = (rear + 1) % SIZE;
    queue[rear] = value;
    printf("%d enqueued\n", value);
}

void dequeue() {
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }
    int data = queue[front];
    if (front == rear) {
        front = rear = -1; // queue becomes empty
    }
    else {
        front = (front + 1) % SIZE;
    }
    printf("%d dequeued\n", data);
}

void display() {
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    int i = front;
    while (1) {
        printf("%d ->", queue[i]);
        if (i == rear) break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main() {
    int choice, value;
    while (1) {
        printf("\n1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
        printf("Enter choice: ");
        scanf_s("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter value: ");
            scanf_s("%d", &value);
            enqueue(value);
            break;
        case 2:
            dequeue();
            break;
        case 3:
            display();
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}

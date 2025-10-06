#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y, z;
} State;

typedef struct Node {
    State s;
    struct Node *next;
} Node;

int visited[11][8][5];  // for marking visited states

// Enqueue/Dequeue linked queue
typedef struct Queue {
    Node *front, *rear;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

int isEmpty(Queue* q) {
    return q->front == NULL;
}

void enqueue(Queue* q, State s) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->s = s;
    temp->next = NULL;
    if (q->rear == NULL)
        q->front = q->rear = temp;
    else {
        q->rear->next = temp;
        q->rear = temp;
    }
}

State dequeue(Queue* q) {
    State s = {-1, -1, -1};
    if (isEmpty(q)) return s;
    Node* temp = q->front;
    s = temp->s;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return s;
}

// Pour from A->B
void pour(int *from, int *to, int capTo) {
    int space = capTo - *to;
    int transfer = (*from < space) ? *from : space;
    *from -= transfer;
    *to += transfer;
}

// Print state
void printState(State s) {
    printf("(%d, %d, %d)\n", s.x, s.y, s.z);
}

// BFS to find solution
void solve() {
    int cap[3] = {10, 7, 4};
    State start = {0, 7, 4};
    Queue* q = createQueue();
    enqueue(q, start);
    visited[start.x][start.y][start.z] = 1;

    printf("\nExploring states:\n");

    while (!isEmpty(q)) {
        State cur = dequeue(q);
        printState(cur);

        if (cur.y == 2 || cur.z == 2) {
            printf("\nGoal reached at state ");
            printState(cur);
            return;
        }

        // Try all six pour directions (A->B, A->C, B->A, B->C, C->A, C->B)
        int i, j;
        int caps[3] = {10, 7, 4};
        int vals[3] = {cur.x, cur.y, cur.z};

        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (i != j && vals[i] > 0 && vals[j] < caps[j]) {
                    int from = vals[i], to = vals[j];
                    pour(&from, &to, caps[j]);

                    int nextVals[3] = {vals[0], vals[1], vals[2]};
                    nextVals[i] = from;
                    nextVals[j] = to;

                    if (!visited[nextVals[0]][nextVals[1]][nextVals[2]]) {
                        visited[nextVals[0]][nextVals[1]][nextVals[2]] = 1;
                        State next = {nextVals[0], nextVals[1], nextVals[2]};
                        enqueue(q, next);
                    }
                }
            }
        }
    }

    printf("\nNo solution found.\n");
}

// Reset visited
void resetVisited() {
    for (int i = 0; i <= 10; i++)
        for (int j = 0; j <= 7; j++)
            for (int k = 0; k <= 4; k++)
                visited[i][j][k] = 0;
}

int main() {
    int choice;
    while (1) {
        printf("\n--- Water Jug Problem Menu ---\n");
        printf("1. Solve problem\n");
        printf("2. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            resetVisited();
            solve();
            break;
        case 2:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice.\n");
        }
    }
}

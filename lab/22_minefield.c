#include <stdio.h>
#include <stdlib.h>

#define MAX 50

// Binary-linked queue node
struct QNode {
    int x, y, dist;
    struct QNode *left, *right;
};

// Queue with front and rear
struct Queue {
    struct QNode *front, *rear;
};

// Queue functions
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

int isEmpty(struct Queue* q) {
    return q->front == NULL;
}

void enqueue(struct Queue* q, int x, int y, int dist) {
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp->x = x;
    temp->y = y;
    temp->dist = dist;
    temp->left = temp->right = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->right = temp;
    temp->left = q->rear;
    q->rear = temp;
}

struct QNode* dequeue(struct Queue* q) {
    if (isEmpty(q)) return NULL;
    struct QNode* temp = q->front;
    q->front = q->front->right;
    if (q->front == NULL)
        q->rear = NULL;
    else
        q->front->left = NULL;
    return temp;
}

// Global maze and result matrix
int maze[MAX][MAX], dist[MAX][MAX];
int m, n;

// Directions: up, down, left, right
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Check valid cell
int isValid(int x, int y) {
    return (x >= 0 && x < m && y >= 0 && y < n);
}

// BFS from all landmines
void findShortestDistances() {
    struct Queue* q = createQueue();

    // Initialize distances and enqueue all landmines
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (maze[i][j] == 0) {
                dist[i][j] = 0;
                enqueue(q, i, j, 0);
            } else {
                dist[i][j] = -1;
            }
        }
    }

    // BFS traversal
    while (!isEmpty(q)) {
        struct QNode* node = dequeue(q);
        for (int k = 0; k < 4; k++) {
            int nx = node->x + dx[k];
            int ny = node->y + dy[k];

            if (isValid(nx, ny) && maze[nx][ny] == 1 && dist[nx][ny] == -1) {
                dist[nx][ny] = node->dist + 1;
                enqueue(q, nx, ny, node->dist + 1);
            }
        }
        free(node);
    }
    free(q);
}

// Display matrix
void displayMatrix(int mat[MAX][MAX]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            printf("%3d ", mat[i][j]);
        printf("\n");
    }
}

// Input maze
void inputMaze() {
    printf("Enter rows and columns: ");
    scanf("%d %d", &m, &n);
    printf("Enter maze elements (-1 for blocked, 0 for landmine, 1 for safe cell):\n");
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &maze[i][j]);
}

// Menu-driven main
int main() {
    int choice;
    while (1) {
        printf("\n--- Landmine Distance Menu ---\n");
        printf("1. Input maze\n");
        printf("2. Display maze\n");
        printf("3. Find shortest distances\n");
        printf("4. Display distance matrix\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            inputMaze();
            break;
        case 2:
            printf("Maze:\n");
            displayMatrix(maze);
            break;
        case 3:
            findShortestDistances();
            printf("Shortest distances computed.\n");
            break;
        case 4:
            printf("Distance Matrix:\n");
            displayMatrix(dist);
            break;
        case 5:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
}

#include <stdio.h>
#define MAX 50

typedef struct {
    int row;
    int col;
    int val;
} term;

int main() {
    int m, n;
    int mat[20][20];
    term a[MAX], t[MAX];
    int i, j, k = 1;

    // Input
    printf("Enter number of rows and columns: ");
    scanf("%d %d", &m, &n);

    printf("Enter the elements of the matrix (%d x %d):\n", m, n);
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    // Convert to sparse
    int count = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (mat[i][j] != 0) {
                a[k].row = i;
                a[k].col = j;
                a[k].val = mat[i][j];
                k++;
                count++;
            }
        }
    }

    a[0].row = m;
    a[0].col = n;
    a[0].val = count;

    // Transpose with fast method
    t[0].row = a[0].col;
    t[0].col = a[0].row;
    t[0].val = a[0].val;

    int total = a[0].val;
    int row_terms[n], starting_pos[n];

    for (i = 0; i < n; i++)
        row_terms[i] = 0;

    // Count number of elements in each column (of original)
    for (i = 1; i <= total; i++)
        row_terms[a[i].col]++;

    starting_pos[0] = 1;
    for (i = 1; i < n; i++)
        starting_pos[i] = starting_pos[i-1] + row_terms[i-1];

    for (i = 1; i <= total; i++) {
        int pos = starting_pos[a[i].col]++;
        t[pos].row = a[i].col;
        t[pos].col = a[i].row;
        t[pos].val = a[i].val;
    }

    // Print original sparse
    printf("\nSparse Matrix Representation:\n");
    for (i = 0; i <= count; i++) {
        printf("(%d, %d, %d)\n", a[i].row, a[i].col, a[i].val);
    }

    // Print transpose sparse
    printf("\nTranspose Sparse Matrix Representation:\n");
    for (i = 0; i <= count; i++) {
        printf("(%d, %d, %d)\n", t[i].row, t[i].col, t[i].val);
    }

    return 0;
}

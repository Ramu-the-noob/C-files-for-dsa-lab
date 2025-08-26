#include <stdio.h>

struct Sparse {
    int row;
    int col;
    int value;
};

int main() {
    int rows, cols;
    printf("Enter number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    int matrix[20][20];
    printf("Enter the elements of the matrix (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    struct Sparse sparse[100];
    int k = 1;

    sparse[0].row = rows;
    sparse[0].col = cols;
    sparse[0].value = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                sparse[k].row = i;
                sparse[k].col = j;
                sparse[k].value = matrix[i][j];
                k++;
            }
        }
    }

    sparse[0].value = k - 1;

    printf("\nOriginal Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nSparse Matrix Representation (row col value):\n");
    for (int i = 0; i < k; i++) {
        printf("%d %d %d\n", sparse[i].row, sparse[i].col, sparse[i].value);
    }

    return 0;
}

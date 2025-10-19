#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row;
    int col;
    int value;
} Term;

typedef struct {
    int numRows;
    int numCols;
    int numTerms;
    Term terms[200];
} Matrix;

void createMatrix(Matrix* matrix);
void display(Matrix* matrix, const char* title);
void transpose(Matrix* a, Matrix* b);
void addMatrices(Matrix* a, Matrix* b, Matrix* sum);

int main() {
    Matrix A, B, Sum, TransposeResult;
    int choice;
    int isACreated = 0;
    int isBCreated = 0;

    do {
        system("cls");
        printf("SPARSE MATRIX OPERATIONS MENU\n");
        printf("1. Create Matrix A\n");
        printf("2. Create Matrix B\n");
        printf("3. Display Matrix A\n");
        printf("4. Display Matrix B\n");
        printf("5. Add Matrix A and Matrix B\n");
        printf("6. Find Transpose of Matrix A\n");
        printf("7. Find Transpose of Matrix B\n");
        printf("8. Add Matrix A to its Transpose\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            createMatrix(&A);
            isACreated = 1;
            break;
        case 2:
            createMatrix(&B);
            isBCreated = 1;
            break;
        case 3:
            if (isACreated) {
                display(&A, "Matrix A");
            }
            else {
                printf("\nError: Matrix A has not been created yet.\n");
            }
            break;
        case 4:
            if (isBCreated) {
                display(&B, "Matrix B");
            }
            else {
                printf("\nError: Matrix B has not been created yet.\n");
            }
            break;
        case 5:
            if (isACreated && isBCreated) {
                if (A.numRows != B.numRows || A.numCols != B.numCols) {
                    printf("\nError: Matrices must have the same dimensions to be added.\n");
                }
                else {
                    addMatrices(&A, &B, &Sum);
                    display(&Sum, "Sum of A and B");
                }
            }
            else {
                printf("\nError: Both Matrix A and B must be created first.\n");
            }
            break;
        case 6:
            if (isACreated) {
                transpose(&A, &TransposeResult);
                display(&TransposeResult, "Transpose of A");
            }
            else {
                printf("\nError: Matrix A has not been created yet.\n");
            }
            break;
        case 7:
            if (isBCreated) {
                transpose(&B, &TransposeResult);
                display(&TransposeResult, "Transpose of B");
            }
            else {
                printf("\nError: Matrix B has not been created yet.\n");
            }
            break;
        case 8:
            if (isACreated) {
                if (A.numRows != A.numCols) {
                    printf("\nError: Matrix A must be a square matrix to be added to its transpose.\n");
                }
                else {
                    transpose(&A, &TransposeResult);
                    addMatrices(&A, &TransposeResult, &Sum);
                    display(&Sum, "Sum of A and its Transpose");
                }
            }
            else {
                printf("\nError: Matrix A has not been created yet.\n");
            }
            break;
        case 9:
            printf("\nExiting program.\n");
            break;
        default:
            printf("\nInvalid choice. Please try again.\n");
        }

        if (choice != 9) {
            printf("\n");
            system("pause");
        }
    } while (choice != 9);

    return 0;
}

void createMatrix(Matrix* matrix) {
    printf("\nEnter number of rows: ");
    scanf("%d", &matrix->numRows);

    printf("Enter number of columns: ");
    scanf("%d", &matrix->numCols);

    printf("Enter number of non-zero terms: ");
    scanf("%d", &matrix->numTerms);

    if (matrix->numTerms > 200) {
        printf("Error: Term count exceeds array capacity. Exiting.\n");
        exit(1);
    }

    printf("Enter the terms (row col value) in row-major order:\n");
    for (int i = 0; i < matrix->numTerms; i++) {
        printf("Term %d: ", i + 1);
        scanf("%d %d %d", &matrix->terms[i].row, &matrix->terms[i].col, &matrix->terms[i].value);
    }
    printf("Matrix created successfully.\n");
}

void display(Matrix* matrix, const char* title) {
    printf("\n--- %s ---\n", title);
    printf("Dimensions: %d rows, %d cols\n", matrix->numRows, matrix->numCols);
    printf("Non-zero terms: %d\n", matrix->numTerms);
    printf("---------------------\n");
    printf("Row | Col | Value\n");
    printf("---------------------\n");
    for (int i = 0; i < matrix->numTerms; i++) {
        printf("%-3d | %-3d | %d\n",
            matrix->terms[i].row,
            matrix->terms[i].col,
            matrix->terms[i].value);
    }
}

void transpose(Matrix* a, Matrix* b) {
    b->numRows = a->numCols;
    b->numCols = a->numRows;
    b->numTerms = a->numTerms;
    if (a->numTerms == 0) {
        return;
    }
    int k = 0;
    for (int c = 0; c < a->numCols; c++) {
        for (int i = 0; i < a->numTerms; i++) {
            if (a->terms[i].col == c) {
                b->terms[k].row = a->terms[i].col;
                b->terms[k].col = a->terms[i].row;
                b->terms[k].value = a->terms[i].value;
                k++;
            }
        }
    }
}

void addMatrices(Matrix* a, Matrix* b, Matrix* sum) {
    int i = 0, j = 0, k = 0;

    sum->numRows = a->numRows;
    sum->numCols = a->numCols;

    while (i < a->numTerms && j < b->numTerms) {
        if (a->terms[i].row < b->terms[j].row) {
            sum->terms[k++] = a->terms[i++];
        }
        else if (a->terms[i].row > b->terms[j].row) {
            sum->terms[k++] = b->terms[j++];
        }
        else {
            if (a->terms[i].col < b->terms[j].col) {
                sum->terms[k++] = a->terms[i++];
            }
            else if (a->terms[i].col > b->terms[j].col) {
                sum->terms[k++] = b->terms[j++];
            }
            else {
                int addedValue = a->terms[i].value + b->terms[j].value;
                if (addedValue != 0) {
                    sum->terms[k].row = a->terms[i].row;
                    sum->terms[k].col = a->terms[i].col;
                    sum->terms[k].value = addedValue;
                    k++;
                }
                i++;
                j++;
            }
        }
    }

    while (i < a->numTerms) {
        sum->terms[k++] = a->terms[i++];
    }

    while (j < b->numTerms) {
        sum->terms[k++] = b->terms[j++];
    }

    sum->numTerms = k;
}

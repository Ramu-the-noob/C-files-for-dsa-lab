#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int pow;
    struct Node* next;
};

// Create a new node
struct Node* createNode(int coeff, int pow) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->pow = pow;
    newNode->next = NULL;
    return newNode;
}

// Append term
void append(struct Node** head, int coeff, int pow) {
    struct Node* newNode = createNode(coeff, pow);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;
}

// Print polynomial
void printPoly(struct Node* head) {
    if (!head) {
        printf("Empty polynomial\n");
        return;
    }
    struct Node* temp = head;
    while (temp) {
        printf("%dx^%d", temp->coeff, temp->pow);
        if (temp->next)
            printf(" + ");
        temp = temp->next;
    }
    printf("\n");
}

// Add two polynomials
struct Node* addPoly(struct Node* p1, struct Node* p2) {
    struct Node* result = NULL;
    while (p1 && p2) {
        if (p1->pow > p2->pow) {
            append(&result, p1->coeff, p1->pow);
            p1 = p1->next;
        }
        else if (p1->pow < p2->pow) {
            append(&result, p2->coeff, p2->pow);
            p2 = p2->next;
        }
        else {
            append(&result, p1->coeff + p2->coeff, p1->pow);
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    while (p1) {
        append(&result, p1->coeff, p1->pow);
        p1 = p1->next;
    }
    while (p2) {
        append(&result, p2->coeff, p2->pow);
        p2 = p2->next;
    }
    return result;
}

// Multiply two polynomials
struct Node* multiplyPoly(struct Node* p1, struct Node* p2) {
    struct Node* result = NULL;
    for (struct Node* a = p1; a != NULL; a = a->next) {
        for (struct Node* b = p2; b != NULL; b = b->next) {
            int coeff = a->coeff * b->coeff;
            int pow = a->pow + b->pow;

            struct Node* temp = result;
            struct Node* prev = NULL;
            while (temp && temp->pow > pow) {
                prev = temp;
                temp = temp->next;
            }
            if (temp && temp->pow == pow)
                temp->coeff += coeff;
            else {
                struct Node* newNode = createNode(coeff, pow);
                if (prev == NULL) {
                    newNode->next = result;
                    result = newNode;
                }
                else {
                    newNode->next = prev->next;
                    prev->next = newNode;
                }
            }
        }
    }
    return result;
}

// Input polynomial from user
void inputPoly(struct Node** poly) {
    int n, coeff, pow;
    printf("Enter number of terms: ");
    scanf_s("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and power for term %d: ", i + 1);
        scanf_s("%d %d", &coeff, &pow);
        append(poly, coeff, pow);
    }
}

// Free memory
void freePoly(struct Node* head) {
    struct Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* result = NULL;

    int choice;
    while (1) {
        printf("\n--- Polynomial Operations Menu ---\n");
        printf("1. Enter first polynomial\n");
        printf("2. Enter second polynomial\n");
        printf("3. Display polynomials\n");
        printf("4. Add polynomials\n");
        printf("5. Multiply polynomials\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            freePoly(poly1);
            poly1 = NULL;
            inputPoly(&poly1);
            break;
        case 2:
            freePoly(poly2);
            poly2 = NULL;
            inputPoly(&poly2);
            break;
        case 3:
            printf("\nPolynomial 1: ");
            printPoly(poly1);
            printf("Polynomial 2: ");
            printPoly(poly2);
            break;
        case 4:
            freePoly(result);
            result = addPoly(poly1, poly2);
            printf("\nSum: ");
            printPoly(result);
            break;
        case 5:
            freePoly(result);
            result = multiplyPoly(poly1, poly2);
            printf("\nProduct: ");
            printPoly(result);
            break;
        case 6:
            freePoly(poly1);
            freePoly(poly2);
            freePoly(result);
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
}

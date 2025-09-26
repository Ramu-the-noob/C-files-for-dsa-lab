#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    int pow;
    struct node *next;
};

// Insert at end (for direct insertion)
void insert_end(int val, int pow, struct node **head) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->val = val;
    new_node->pow = pow;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        struct node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }

    printf("Polynomial with coefficient %d and power %d inserted\n", val, pow);
}

// Delete from end
void del_end(struct node **head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct node *temp = *head;

    if (temp->next == NULL) {
        free(temp);
        *head = NULL;
    } else {
        struct node *prev = NULL;
        while (temp->next != NULL) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = NULL;
        free(temp);
    }

    printf("Deleted from end\n");
}

// Display polynomial
void display(struct node *head) {
    if (head == NULL) {
        printf("Polynomial is empty\n");
        return;
    }

    while (head != NULL) {
        printf("%d", head->val);
        if (head->pow != 0) {
            printf("x^%d", head->pow);
        }
        if (head->next != NULL) printf(" + ");
        head = head->next;
    }
    printf("\n");
}

// Insert a term in sorted order (descending by power), merge like powers
void insert_term_sorted(int val, int pow, struct node **head) {
    if (val == 0) return; // Skip zero terms

    struct node *new_node = malloc(sizeof(struct node));
    new_node->val = val;
    new_node->pow = pow;
    new_node->next = NULL;

    if (*head == NULL || (*head)->pow < pow) {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    struct node *current = *head;
    struct node *prev = NULL;

    while (current != NULL && current->pow > pow) {
        prev = current;
        current = current->next;
    }

    if (current != NULL && current->pow == pow) {
        current->val += val;
        free(new_node);
        if (current->val == 0) {  // Remove zero coefficient
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
        }
    } else {
        new_node->next = current;
        if (prev == NULL) {
            *head = new_node;
        } else {
            prev->next = new_node;
        }
    }
}

// Polynomial Addition
void polysum(struct node *poly1, struct node *poly2, struct node **poly3) {
    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->pow == poly2->pow) {
            insert_end(poly1->val + poly2->val, poly1->pow, poly3);
            poly1 = poly1->next;
            poly2 = poly2->next;
        } else if (poly1->pow > poly2->pow) {
            insert_end(poly1->val, poly1->pow, poly3);
            poly1 = poly1->next;
        } else {
            insert_end(poly2->val, poly2->pow, poly3);
            poly2 = poly2->next;
        }
    }

    while (poly1 != NULL) {
        insert_end(poly1->val, poly1->pow, poly3);
        poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        insert_end(poly2->val, poly2->pow, poly3);
        poly2 = poly2->next;
    }
}

// Polynomial Multiplication
void polymul(struct node *poly1, struct node *poly2, struct node **poly3) {
    struct node *ptr1 = poly1;
    while (ptr1 != NULL) {
        struct node *ptr2 = poly2;
        while (ptr2 != NULL) {
            int coeff = ptr1->val * ptr2->val;
            int power = ptr1->pow + ptr2->pow;
            insert_term_sorted(coeff, power, poly3);
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
}

// User input loop for polynomial creation
void input_poly(struct node **poly, const char *name) {
    char ch = 'y';
    while (ch == 'y' || ch == 'Y') {
        printf("\n%s MENU:\n", name);
        printf("0. See the %s\n", name);
        printf("1. Enter a term\n");
        printf("2. Undo (delete last term)\n");
        printf("3. Finish %s\n", name);
        printf("Enter choice: ");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 0:
                display(*poly);
                break;
            case 1: {
                int val, pow;
                printf("Enter the coefficient: ");
                scanf("%d", &val);
                printf("Enter the power: ");
                scanf("%d", &pow);
                insert_end(val, pow, poly);
                break;
            }
            case 2:
                del_end(poly);
                break;
            case 3:
                ch = 'n';
                break;
            default:
                printf("Enter a valid choice\n");
        }
    }
}

int main() {
    struct node *poly1 = NULL;
    struct node *poly2 = NULL;
    struct node *result = NULL;

    printf("Enter Polynomial 1:\n");
    input_poly(&poly1, "Polynomial 1");

    printf("\nEnter Polynomial 2:\n");
    input_poly(&poly2, "Polynomial 2");

    printf("\nChoose Operation:\n1. Add\n2. Multiply\nYour choice: ");
    int op;
    scanf("%d", &op);

    if (op == 1) {
        polysum(poly1, poly2, &result);
        printf("\nResultant Polynomial (Addition):\n");
        display(result);
    } else if (op == 2) {
        polymul(poly1, poly2, &result);
        printf("\nResultant Polynomial (Multiplication):\n");
        display(result);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}


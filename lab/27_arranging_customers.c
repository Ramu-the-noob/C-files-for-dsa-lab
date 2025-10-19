#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Define a structure to hold customer data */
struct Customer {
    char name[100];
    int priority; /* 1 = highest priority, 4 = lowest */
};

void swap(struct Customer* xp, struct Customer* yp) {
    struct Customer temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sortCustomersByPriority(struct Customer customers[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (customers[j].priority > customers[j + 1].priority) {
                swap(&customers[j], &customers[j + 1]);
            }
        }
    }
}

const char* getCategoryName(int priority) {
    switch (priority) {
    case 1: return "Differently abled";
    case 2: return "Senior citizen";
    case 3: return "Defence personnel";
    case 4: return "Normal person";
    default: return "Unknown";
    }
}

/* Helper to flush rest of stdin line */
static void flush_stdin_line(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* discard */ }
}

int main(void) {
    int n;

    printf("Enter the number of customers in the queue: ");
    if (scanf_s("%d", &n) != 1) {
        fprintf(stderr, "Invalid number entered.\n");
        return 1;
    }
    flush_stdin_line();

    if (n <= 0 || n > 100) {
        printf("Can only handle 1-100 customers.\n");
        return 1;
    }

    struct Customer customers[100];
    int i;

    for (i = 0; i < n; i++) {
        int choice = 4; /* default */

        printf("\n--- Enter details for Customer %d ---\n", i + 1);

        /* Read a single-word name safely with buffer size.
           scanf_s requires the buffer size argument for %s on MSVC. */
        printf("Enter customer's name (single word): ");
        if (scanf_s("%99s", customers[i].name, (unsigned)sizeof(customers[i].name)) != 1) {
            fprintf(stderr, "Failed to read name.\n");
            return 1;
        }

        printf("Select customer category:\n");
        printf("  1: Differently abled\n");
        printf("  2: Senior citizen\n");
        printf("  3: Defence personnel\n");
        printf("  4: Normal person\n");
        printf("Enter choice (1-4): ");

        if (scanf_s("%d", &choice) != 1) {
            /* invalid input, clear the rest of the line and default */
            fprintf(stderr, "Invalid category input; defaulting to 'Normal person'.\n");
            flush_stdin_line();
            choice = 4;
        } else {
            flush_stdin_line();
            if (choice < 1 || choice > 4) {
                printf("Invalid choice. Defaulting to 'Normal person'.\n");
                choice = 4;
            }
        }

        customers[i].priority = choice;
    }

    sortCustomersByPriority(customers, n);

    printf("\n\n=========================================\n");
    printf("   Post Office Completion Sequence\n");
    printf("   (Highest to Lowest Priority)\n");
    printf("=========================================\n");
    printf("%-20s %-20s\n", "Customer Name", "Category");
    printf("-----------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-20s %-20s\n",
            customers[i].name,
            getCategoryName(customers[i].priority));
    }

    return 0;
}

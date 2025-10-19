#include <stdio.h>
#include <stdlib.h> // For qsort

/**
 * @brief Comparison function for qsort to sort integers in DESCENDING order.
 */
int compare_desc(const void *a, const void *b) {
    // We cast the void pointers to integer pointers and dereference them
    // (b - a) gives descending order
    return (*(int*)b - *(int*)a);
}

/**
 * @brief Clears the stdin input buffer, used after a failed scanf_s.
 */
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int events[100]; // Assume a max of 100 events
    int n, k;
    long long max_points = 0; // Use long long in case the sum is large

    // --- 1. Get number of events ---
    printf("Enter the total number of events (n): ");
    if (scanf_s("%d", &n) != 1 || n <= 0 || n > 100) {
        printf("Invalid input. Please enter a number between 1 and 100.\n");
        clear_input_buffer();
        return 1;
    }
    clear_input_buffer();

    // --- 2. Get points for each event ---
    printf("Enter the activity points for each of the %d events:\n", n);
    for (int i = 0; i < n; i++) {
        printf("  Event %d points: ", i + 1);
        if (scanf_s("%d", &events[i]) != 1) {
            printf("Invalid input.\n");
            clear_input_buffer();
            return 1;
        }
        clear_input_buffer();
    }

    // --- 3. Get number of events to participate in ---
    printf("\nEnter the max number of events you can join (k): ");
    if (scanf_s("%d", &k) != 1 || k <= 0) {
        printf("Invalid input. 'k' must be a positive number.\n");
        clear_input_buffer();
        return 1;
    }
    clear_input_buffer();

    // --- 4. Handle edge case (k > n) ---
    if (k > n) {
        printf("\nNote: k (%d) is greater than total events (%d).\n", k, n);
        printf("You will participate in all %d events.\n", n);
        k = n; // You can't join more events than exist
    }

    // --- 5. Sort the array ---
    // qsort(array, num_elements, size_of_element, compare_function)
    qsort(events, n, sizeof(int), compare_desc);

    // --- 6. Sum the top k elements ---
    for (int i = 0; i < k; i++) {
        max_points += events[i];
    }

    // --- 7. Print the result ---
    printf("\n--- Calculation ---\n");
    printf("The top %d events give these points:\n", k);
    for (int i = 0; i < k; i++) {
        printf("  %d points\n", events[i]);
    }
    printf("\nMaximum points you can earn: %lld\n", max_points);

    return 0;
}

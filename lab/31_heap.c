#include <stdio.h>
#include <stdlib.h> // For exit()

// --- 1. Define Constants and Structures ---

#define MAX_K 10  // Max 10 lists
#define MAX_N 50  // Max 50 elements per list

// Node structure for the Min-Heap
// Stores the value and its original location
typedef struct HeapNode {
    int value;
    int list_index;    // Which list it came from (0 to k-1)
    int element_index; // Its index in that list
} HeapNode;


// --- 2. Min-Heap Utility Functions ---

/**
 * @brief Swaps two HeapNode elements.
 */
void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Sifts an element down to its correct position (Min-Heapify Down).
 * Used after extracting the minimum element.
 */
void min_heapify_down(HeapNode heap[], int size, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Find the smallest among node, left child, and right child
    if (left < size && heap[left].value < heap[smallest].value) {
        smallest = left;
    }
    if (right < size && heap[right].value < heap[smallest].value) {
        smallest = right;
    }

    // If smallest is not the root, swap and recurse
    if (smallest != index) {
        swap(&heap[index], &heap[smallest]);
        min_heapify_down(heap, size, smallest);
    }
}

/**
 * @brief Sifts an element up to its correct position (Min-Heapify Up).
 * Used after inserting a new element.
 */
void min_heapify_up(HeapNode heap[], int index) {
    int parent = (index - 1) / 2;
    // While not at the root and child is smaller than parent
    while (index > 0 && heap[index].value < heap[parent].value) {
        swap(&heap[index], &heap[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

/**
 * @brief Inserts a new node into the min-heap.
 */
void insert_to_heap(HeapNode heap[], int *size, HeapNode node) {
    if (*size >= MAX_K) {
        printf("Heap is full!\n");
        return;
    }
    // Insert at the end and heapify up
    heap[*size] = node;
    (*size)++;
    min_heapify_up(heap, *size - 1);
}

/**
 * @brief Extracts the minimum node (root) from the min-heap.
 */
HeapNode extract_min(HeapNode heap[], int *size) {
    if (*size <= 0) {
        printf("Heap is empty!\n");
        // Return a dummy node (in a real app, handle this error better)
        HeapNode error_node = {-1, -1, -1};
        return error_node;
    }

    // Store the root (minimum)
    HeapNode min_node = heap[0];

    // Replace root with the last element
    heap[0] = heap[*size - 1];
    (*size)--;

    // Heapify down from the new root
    min_heapify_down(heap, *size, 0);

    return min_node;
}

// --- 3. Helper and Main Functions ---

/**
 * @brief Clears the stdin input buffer.
 */
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    // 1. Declare all variables
    int k; // Number of lists
    int lists[MAX_K][MAX_N];
    int list_sizes[MAX_K];
    int total_elements = 0;
    
    // The heap itself
    HeapNode heap[MAX_K];
    int heap_size = 0;

    // The final result
    int merged_list[MAX_K * MAX_N];
    int merged_count = 0;

    // --- 2. Get User Input ---
    printf("Enter the number of sorted lists (K) (max %d): ", MAX_K);
    if (scanf_s("%d", &k) != 1 || k <= 0 || k > MAX_K) {
        printf("Invalid input for K.\n");
        return 1;
    }
    clear_input_buffer();

    for (int i = 0; i < k; i++) {
        printf("\nEnter size of list %d (max %d): ", i, MAX_N);
        if (scanf_s("%d", &list_sizes[i]) != 1 || list_sizes[i] < 0 || list_sizes[i] > MAX_N) {
            printf("Invalid size.\n");
            return 1;
        }
        clear_input_buffer();
        total_elements += list_sizes[i];

        if (list_sizes[i] > 0) {
            printf("Enter %d sorted elements for list %d:\n", list_sizes[i], i);
            for (int j = 0; j < list_sizes[i]; j++) {
                printf("  Element %d: ", j);
                scanf_s("%d", &lists[i][j]);
                clear_input_buffer();
            }

            // --- 3. Initial Heap Load ---
            // Add the first element of this non-empty list to the heap
            HeapNode node = { lists[i][0], i, 0 };
            insert_to_heap(heap, &heap_size, node);
        }
    }
    
    if (total_elements > MAX_K * MAX_N) {
         printf("Total elements exceed array capacity. Exiting.\n");
         return 1;
    }

    // --- 4. Main Merge Algorithm ---
    printf("\nMerging lists...\n");
    while (heap_size > 0) {
        // 1. Extract the smallest element
        HeapNode min_node = extract_min(heap, &heap_size);
        
        // 2. Add its value to the result list
        merged_list[merged_count++] = min_node.value;

        // 3. Find the next element from the *same list*
        int list_idx = min_node.list_index;
        int next_element_idx = min_node.element_index + 1;

        // 4. If that list has a next element, insert it into the heap
        if (next_element_idx < list_sizes[list_idx]) {
            HeapNode next_node = {
                lists[list_idx][next_element_idx], // value
                list_idx,                          // list_index
                next_element_idx                   // element_index
            };
            insert_to_heap(heap, &heap_size, next_node);
        }
    }

    // --- 5. Print the Final Merged List ---
    printf("\n--- Final Merged List ---\n");
    for (int i = 0; i < total_elements; i++) {
        printf("%d ", merged_list[i]);
    }
    printf("\n");

    return 0;
}

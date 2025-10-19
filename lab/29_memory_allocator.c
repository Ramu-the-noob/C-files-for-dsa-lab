#include <stdio.h>
#include <stdlib.h> // For size_t, NULL

// --- 1. Heap and Block Structure Definition ---

#define HEAP_SIZE 65536 // 64k simulated heap
static char g_heap[HEAP_SIZE];

// Header for ALL blocks (allocated or free)
typedef struct BlockHeader {
    size_t size;  // Total size of this block (header + data)
    int is_free;
} BlockHeader;

// Structure for a node in the free list.
// This overlays a free block's memory.
typedef struct FreeListNode {
    BlockHeader header;
    struct FreeListNode *prev_free; // Doubly linked list pointers
    struct FreeListNode *next_free;
} FreeListNode;

// The head of the explicit doubly linked free list
static FreeListNode *g_free_list_head = NULL;

// Minimum size of any block (must be able to hold free list node)
#define MIN_BLOCK_SIZE sizeof(FreeListNode)

// --- 2. Allocation Tracking ---
#define MAX_ALLOCATIONS 100
// Our "allocation table" to track what we've malloc'd
void *g_allocations[MAX_ALLOCATIONS] = {NULL}; 

// --- 3. Free List Helper Functions ---

/**
 * @brief Adds a block to the front of the doubly linked free list.
 */
void add_to_free_list(FreeListNode *node) {
    node->header.is_free = 1;
    node->prev_free = NULL;
    node->next_free = g_free_list_head;
    if (g_free_list_head != NULL) {
        g_free_list_head->prev_free = node;
    }
    g_free_list_head = node;
}

/**
 * @brief Removes a block from the doubly linked free list.
 */
void remove_from_free_list(FreeListNode *node) {
    if (node->prev_free != NULL) {
        node->prev_free->next_free = node->next_free;
    } else {
        g_free_list_head = node->next_free;
    }
    if (node->next_free != NULL) {
        node->next_free->prev_free = node->prev_free;
    }
}

// --- 4. Allocator and Garbage Collector ---

/**
 * @brief Initializes the allocator with one large free block.
 */
void init_allocator() {
    g_free_list_head = NULL;
    // Clear allocation tracker
    for(int i=0; i<MAX_ALLOCATIONS; i++) {
        g_allocations[i] = NULL;
    }

    if (HEAP_SIZE < MIN_BLOCK_SIZE) {
        return;
    }
    FreeListNode *initial_block = (FreeListNode *)g_heap;
    initial_block->header.size = HEAP_SIZE;
    initial_block->header.is_free = 1;
    add_to_free_list(initial_block);
}

/**
 * @brief Allocates memory (first-fit strategy).
 */
void *my_malloc(size_t size) {
    if (size == 0) return NULL;

    size_t total_needed = sizeof(BlockHeader) + size;
    if (total_needed < MIN_BLOCK_SIZE) {
        total_needed = MIN_BLOCK_SIZE;
    }

    FreeListNode *current = g_free_list_head;
    while (current != NULL) {
        if (current->header.size >= total_needed) break;
        current = current->next_free;
    }

    if (current == NULL) {
        printf("my_malloc: Out of memory!\n");
        return NULL;
    }

    remove_from_free_list(current);
    size_t original_size = current->header.size;

    size_t remainder = original_size - total_needed;
    if (remainder >= MIN_BLOCK_SIZE) {
        FreeListNode *new_free_block = (FreeListNode *)((char *)current + total_needed);
        new_free_block->header.size = remainder;
        add_to_free_list(new_free_block);
        current->header.size = total_needed;
    }

    current->header.is_free = 0;
    return (void *)((char *)current + sizeof(BlockHeader));
}

/**
 * @brief Frees memory and performs coalescing (garbage collection).
 */
void my_free(void *ptr) {
    if (ptr == NULL) return;

    BlockHeader *block_to_free_header = (BlockHeader *)((char *)ptr - sizeof(BlockHeader));
    if (block_to_free_header->is_free) {
        printf("Error: Double free detected!\n");
        return;
    }
    block_to_free_header->is_free = 1;

    FreeListNode *current_block = (FreeListNode *)block_to_free_header;
    size_t current_size = current_block->header.size;

    // Coalesce with NEXT block
    BlockHeader *next_block_header = (BlockHeader *)((char *)current_block + current_size);
    if ((char *)next_block_header < (g_heap + HEAP_SIZE) && next_block_header->is_free) {
        remove_from_free_list((FreeListNode *)next_block_header);
        current_block->header.size += next_block_header->size;
    }

    // Coalesce with PREVIOUS block (O(N) search)
    BlockHeader *prev_block_header = (BlockHeader *)g_heap;
    while ((char *)prev_block_header < (char *)current_block) {
        BlockHeader *next = (BlockHeader *)((char *)prev_block_header + prev_block_header->size);
        if (next == (BlockHeader*)current_block) {
            if (prev_block_header->is_free) {
                remove_from_free_list((FreeListNode *)prev_block_header);
                prev_block_header->size += current_block->header.size;
                current_block = (FreeListNode *)prev_block_header;
            }
            break;
        }
        prev_block_header = next;
    }

    add_to_free_list(current_block);
}

// --- 5. Helper Function to Print Memory Map ---

void print_memory_map() {
    printf("\n--- HEAP MEMORY MAP ---\n");
    BlockHeader *current = (BlockHeader *)g_heap;
    int i = 0;
    while ((char *)current < (g_heap + HEAP_SIZE)) {
        printf("  Block %d: Addr %p, Size %6zu, State: %s\n",
               i++,
               (void*)current,
               current->size,
               current->is_free ? "FREE" : "ALLOCATED");
        
        if (current->size == 0) {
             printf("Error: Zero size block detected!\n");
             return;
        }
        current = (BlockHeader *)((char *)current + current->size);
    }

    // Print allocation table
    printf("\n  Tracked Allocations (by ID):\n");
    int allocations_found = 0;
    for(i=0; i<MAX_ALLOCATIONS; i++) {
        if (g_allocations[i] != NULL) {
            printf("    ID %d: %p\n", i, g_allocations[i]);
            allocations_found = 1;
        }
    }
    if (!allocations_found) {
        printf("    (None)\n");
    }
    printf("--- END OF MAP ---\n");
}

// --- 6. Menu-Driven Functions ---

/**
 * @brief Clears the stdin input buffer.
 */
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Menu option 1: Allocate memory.
 */
void do_allocate() {
    printf("Enter size to allocate: ");
    int size;
    // USE scanf_s instead of scanf
    if (scanf_s("%d", &size) != 1 || size <= 0) {
        printf("Invalid size.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    // Find an empty slot in our tracker
    int i;
    for (i = 0; i < MAX_ALLOCATIONS; i++) {
        if (g_allocations[i] == NULL) {
            break; // Found slot i
        }
    }

    if (i == MAX_ALLOCATIONS) {
        printf("Allocation table is full. Free some memory first.\n");
        return;
    }

    // Perform allocation
    void *ptr = my_malloc(size);
    if (ptr == NULL) {
        // my_malloc already prints "Out of memory"
    } else {
        g_allocations[i] = ptr;
        printf("Success: Memory allocated with ID %d.\n", i);
    }
}

/**
 * @brief Menu option 2: Free memory.
 */
void do_free() {
    printf("Enter allocation ID to free: ");
    int id;
    // USE scanf_s instead of scanf
    if (scanf_s("%d", &id) != 1) {
        printf("Invalid ID.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    if (id < 0 || id >= MAX_ALLOCATIONS) {
        printf("Invalid ID. Must be between 0 and %d.\n", MAX_ALLOCATIONS - 1);
        return;
    }

    if (g_allocations[id] == NULL) {
        printf("Error: No allocation found at ID %d. (Already freed?)\n", id);
    } else {
        my_free(g_allocations[id]);
        g_allocations[id] = NULL; // Mark as free in our tracker
        printf("Success: Memory at ID %d freed.\n", id);
    }
}

// --- 7. Main Simulation ---

int main() {
    init_allocator();

    int choice = 0;
    while (choice != 4) {
        printf("\n--- Memory Allocator Menu ---\n");
        printf("1. Allocate Memory\n");
        printf("2. Free Memory\n");
        printf("3. Show Memory Map\n");
        printf("4. Exit\n");
        printf("-----------------------------\n");
        printf("Your choice: ");

        // USE scanf_s instead of scanf
        if (scanf_s("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer(); // Consume the newline

        switch (choice) {
            case 1:
                do_allocate();
                break;
            case 2:
                do_free();
                break;
            case 3:
                print_memory_map();
                break;
            case 4:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a number from 1 to 4.\n");
        }
    }
    return 0;
}

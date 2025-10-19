// This define is NOT needed if you use the _s "safe" functions below.
// #define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h> // For malloc, free, _countof
#include <string.h> // For string functions
#include <ctype.h>  // For tolower

// 1. --- HASH TABLE STRUCTURE ---

// Set a large prime number for the table size for good distribution
#define TABLE_SIZE 49999

// Node structure for separate chaining (linked list)
struct Node {
    char *word;
    struct Node *next;
};

// The hash table is an array of Node pointers
struct Node *hashTable[TABLE_SIZE];

// 2. --- CORE HASH TABLE FUNCTIONS ---

/**
 * @brief Initializes the hash table, setting all buckets to NULL.
 */
void initHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

/**
 * @brief A 'djb2' hash function for strings.
 * Converts a string into an integer index for the hash table.
 */
unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        // hash * 33 + c
        hash = ((hash << 5) + hash) + c; 
    }
    return hash % TABLE_SIZE;
}

/**
 * @brief Inserts a new word into the hash table.
 */
void insertWord(char *word) {
    // 1. Find the index for this word
    unsigned long index = hash(word);
    
    // 2. Create a new node
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }
    
    // 3. Use _strdup (Visual Studio's version of strdup)
    newNode->word = _strdup(word);
    if (newNode->word == NULL) {
        printf("Error: Memory allocation failed for word.\n");
        free(newNode);
        return;
    }
    
    // 4. Insert at the beginning of the linked list (chain)
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

/**
 * @brief Frees all memory allocated for the hash table.
 */
void freeHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct Node *current = hashTable[i];
        while (current != NULL) {
            struct Node *temp = current;
            current = current->next;
            free(temp->word); // Free the string (from _strdup)
            free(temp);       // Free the node itself
        }
    }
}

// 3. --- SPELL CHECKER FUNCTIONS ---

/**
 * @brief Checks if a word is valid (exists in the hash table).
 * This is the "fast lookup" function.
 * @return 1 if found, 0 if not found.
 */
int isWordValid(char *word) {
    unsigned long index = hash(word);
    struct Node *current = hashTable[index];
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            return 1; // Word found!
        }
        current = current->next;
    }
    return 0; // Reached end of list, word not found
}

/**
 * @brief Generates and prints suggestions for a misspelled word.
 * It checks all words at "edit distance 1".
 */
void suggestCorrections(char *word) {
    // Needs to be 101 to handle insertion on a 99-char word + null terminator
    char tempWord[101]; 
    int len = (int)strlen(word);
    int foundSuggestion = 0;
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

    // 1. Check Deletions (e.g., "hellp" -> "hell")
    for (int i = 0; i < len; i++) {
        // Copy the first 'i' characters
        strncpy_s(tempWord, _countof(tempWord), word, i);
        // Append the rest of the string, skipping the char at 'i'
        strcat_s(tempWord, _countof(tempWord), word + i + 1);
        
        if (isWordValid(tempWord)) {
            printf("  -> %s\n", tempWord);
            foundSuggestion = 1;
        }
    }

    // 2. Check Substitutions (e.g., "helo" -> "hell")
    for (int i = 0; i < len; i++) {
        strcpy_s(tempWord, _countof(tempWord), word); // Reset to original word
        for (int j = 0; j < 26; j++) {
            tempWord[i] = alphabet[j]; // Make substitution
            if (strcmp(tempWord, word) != 0 && isWordValid(tempWord)) {
                printf("  -> %s\n", tempWord);
                foundSuggestion = 1;
            }
        }
    }

    // 3. Check Insertions (e.g., "hel" -> "hell")
    for (int i = 0; i <= len; i++) {
        for (int j = 0; j < 26; j++) {
            // Copy the first 'i' characters
            strncpy_s(tempWord, _countof(tempWord), word, i);
            // Add the new character
            tempWord[i] = alphabet[j];
            // Manually add null terminator for strcat_s
            tempWord[i + 1] = '\0'; 
            // Append the rest of the original string
            strcat_s(tempWord, _countof(tempWord), word + i);
            
            if (isWordValid(tempWord)) {
                printf("  -> %s\n", tempWord);
                foundSuggestion = 1;
            }
        }
    }
    
    // 4. Check Transpositions (e.g., "hlelo" -> "hello")
    for (int i = 0; i < len - 1; i++) {
        strcpy_s(tempWord, _countof(tempWord), word);
        // Swap adjacent characters
        char t = tempWord[i];
        tempWord[i] = tempWord[i+1];
        tempWord[i+1] = t;
        
        if (isWordValid(tempWord)) {
            printf("  -> %s\n", tempWord);
            foundSuggestion = 1;
        }
    }

    if (!foundSuggestion) {
        printf("  (No suggestions found)\n");
    }
}

/**
 * @brief Helper function to normalize a word (to lowercase).
 */
void normalizeWord(char *word) {
    for (int i = 0; word[i]; i++) {
        word[i] = tolower(word[i]);
    }
}

// 4. --- MAIN FUNCTION ---

int main() {
    // A small sample dictionary
    char *dictionary[] = {
        "hello", "world", "spell", "checker", "hash", "table", "store",
        "dictionary", "words", "fast", "lookup", "check", "valid",
        "suggest", "corrections", "for", "misspelled", "code", "c",
        "program", "programming", "computer", "science", "help", "hell",
        "heap", "helo", "home", "house", NULL
    };
    
    initHashTable();
    printf("Loading dictionary...\n");
    for (int i = 0; dictionary[i] != NULL; i++) {
        insertWord(dictionary[i]);
    }
    printf("Dictionary loaded.\n\n");

    char inputWord[100];

    // Main interactive loop
    while (1) {
        printf("Enter a word to check (or 'quit' to exit):\n> ");
        
        // Use scanf_s and provide the buffer size
        // _countof(inputWord) is the same as 100 in this case
        if (scanf_s("%99s", inputWord, (unsigned)_countof(inputWord)) != 1) {
            break; // End on input error
        }

        if (strcmp(inputWord, "quit") == 0) {
            break; // User requested quit
        }

        normalizeWord(inputWord);

        if (isWordValid(inputWord)) {
            printf("\n'-- %s --' is a valid word.\n\n", inputWord);
        } else {
            printf("\n'-- %s --' is MISSPELLED.\n", inputWord);
            printf("Suggestions:\n");
            suggestCorrections(inputWord);
            printf("\n");
        }
    }

    freeHashTable();
    printf("Goodbye!\n");

    return 0;
}

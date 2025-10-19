//check if works
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TEXT 10000

void find_and_replace(char *text, const char *find, const char *replace) {
    char buffer[MAX_TEXT];
    char *pos;
    int find_len = strlen(find);
    int replace_len = strlen(replace);
    int i = 0;

    buffer[0] = '\0';

    while ((pos = strstr(text, find)) != NULL) {
        // Copy text before the match
        int len = pos - text;
        strncpy(buffer + i, text, len);
        i += len;

        // Copy the replacement
        strcpy(buffer + i, replace);
        i += replace_len;

        // Move past the match
        text = pos + find_len;
    }

    // Copy remaining text
    strcpy(buffer + i, text);
    strcpy(text, buffer);
}

int main() {
    char text[MAX_TEXT], find[100], replace[100];
    FILE *fp = fopen("input.txt", "r");

    if (!fp) {
        printf("Error: could not open input.txt\n");
        return 1;
    }

    fread(text, 1, MAX_TEXT - 1, fp);
    fclose(fp);
    text[MAX_TEXT - 1] = '\0';

    printf("Enter text to find: ");
    scanf("%99[^\n]", find);
    getchar(); // clear newline

    printf("Enter replacement text: ");
    scanf("%99[^\n]", replace);

    find_and_replace(text, find, replace);

    FILE *out = fopen("output.txt", "w");
    if (!out) {
        printf("Error: could not open output.txt\n");
        return 1;
    }

    fputs(text, out);
    fclose(out);

    printf("Replacement done. Output written to output.txt\n");
    return 0;
}

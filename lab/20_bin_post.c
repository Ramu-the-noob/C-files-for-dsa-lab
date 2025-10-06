#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Tree Node
struct Node {
    char data;
    struct Node* left;
    struct Node* right;
};

// Stack for nodes
struct Stack {
    struct Node* arr[MAX];
    int top;
};

// Stack for operators
struct CharStack {
    char arr[MAX];
    int top;
};

// Stack Functions
void initNodeStack(struct Stack* s) { s->top = -1; }
void initCharStack(struct CharStack* s) { s->top = -1; }

int isNodeEmpty(struct Stack* s) { return s->top == -1; }
int isCharEmpty(struct CharStack* s) { return s->top == -1; }

void pushNode(struct Stack* s, struct Node* node) { s->arr[++s->top] = node; }
struct Node* popNode(struct Stack* s) { return s->arr[s->top--]; }

void pushChar(struct CharStack* s, char op) { s->arr[++s->top] = op; }
char popChar(struct CharStack* s) { return s->arr[s->top--]; }
char peekChar(struct CharStack* s) { return s->arr[s->top]; }

// Create node
struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Check operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Build expression tree from infix expression
struct Node* buildExpressionTree(char* infix) {
    struct Stack nodeStack;
    struct CharStack opStack;
    initNodeStack(&nodeStack);
    initCharStack(&opStack);

    for (int i = 0; i < strlen(infix); i++) {
        char ch = infix[i];

        if (isspace(ch)) continue;

        if (isalnum(ch)) { // Operand
            pushNode(&nodeStack, createNode(ch));
        } else if (ch == '(') {
            pushChar(&opStack, ch);
        } else if (ch == ')') {
            while (!isCharEmpty(&opStack) && peekChar(&opStack) != '(') {
                char op = popChar(&opStack);
                struct Node* right = popNode(&nodeStack);
                struct Node* left = popNode(&nodeStack);
                struct Node* newNode = createNode(op);
                newNode->left = left;
                newNode->right = right;
                pushNode(&nodeStack, newNode);
            }
            popChar(&opStack); // remove '('
        } else if (isOperator(ch)) {
            while (!isCharEmpty(&opStack) && precedence(peekChar(&opStack)) >= precedence(ch)) {
                char op = popChar(&opStack);
                struct Node* right = popNode(&nodeStack);
                struct Node* left = popNode(&nodeStack);
                struct Node* newNode = createNode(op);
                newNode->left = left;
                newNode->right = right;
                pushNode(&nodeStack, newNode);
            }
            pushChar(&opStack, ch);
        }
    }

    while (!isCharEmpty(&opStack)) {
        char op = popChar(&opStack);
        struct Node* right = popNode(&nodeStack);
        struct Node* left = popNode(&nodeStack);
        struct Node* newNode = createNode(op);
        newNode->left = left;
        newNode->right = right;
        pushNode(&nodeStack, newNode);
    }

    return popNode(&nodeStack);
}

// Prefix traversal (Root-Left-Right)
void prefix(struct Node* root) {
    if (root == NULL) return;
    printf("%c", root->data);
    prefix(root->left);
    prefix(root->right);
}

// Postfix traversal (Left-Right-Root)
void postfix(struct Node* root) {
    if (root == NULL) return;
    postfix(root->left);
    postfix(root->right);
    printf("%c", root->data);
}

// Free memory
void freeTree(struct Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Main Menu
int main() {
    struct Node* root = NULL;
    char expression[MAX];
    int choice;

    while (1) {
        printf("\n--- Expression Tree Menu ---\n");
        printf("1. Enter Infix Expression\n");
        printf("2. Display Prefix Expression\n");
        printf("3. Display Postfix Expression\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
        case 1:
            freeTree(root);
            root = NULL;
            printf("Enter infix expression (e.g., A+B*C): ");
            fgets(expression, MAX, stdin);
            expression[strcspn(expression, "\n")] = '\0'; // remove newline
            root = buildExpressionTree(expression);
            printf("Expression tree created successfully.\n");
            break;
        case 2:
            if (!root)
                printf("Tree not created yet.\n");
            else {
                printf("Prefix Expression: ");
                prefix(root);
                printf("\n");
            }
            break;
        case 3:
            if (!root)
                printf("Tree not created yet.\n");
            else {
                printf("Postfix Expression: ");
                postfix(root);
                printf("\n");
            }
            break;
        case 4:
            freeTree(root);
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
}

#include <stdio.h>
#include <ctype.h>  // for isalpha(), isdigit()
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

// Function to push into stack
void push(char c) {
    stack[++top] = c;
}

// Function to pop from stack
char pop() {
    if (top == -1)
        return -1;
    else
        return stack[top--];
}

// Function to return precedence of operators
int precedence(char c) {
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}

void infixToPostfix(char infix[]) {
    char postfix[MAX];
    int i, j = 0;
    char c;
    
    for (i = 0; infix[i] != '\0'; i++) {
        c = infix[i];
        
        if (isalpha(c) || isdigit(c)) {
            postfix[j++] = c;  // Operand directly to postfix
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = pop();
            }
            pop(); // pop '('
        }
        else { // Operator
            while (top != -1 && precedence(stack[top]) >= precedence(c)) {
                postfix[j++] = pop();
            }
            push(c);
        }
    }
    
    // Pop any remaining operators
    while (top != -1) {
        postfix[j++] = pop();
    }
    
    postfix[j] = '\0';  // End postfix expression
    
    printf("Postfix Expression: %s\n", postfix);
}

int main() {
    char infix[MAX];
    
    printf("Enter an Infix Expression: ");
    scanf("%s", infix);
    
    infixToPostfix(infix);
    
    return 0;
}


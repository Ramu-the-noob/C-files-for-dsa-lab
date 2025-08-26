
#include <stdio.h>
#include <ctype.h>  // For isdigit()
#include <stdlib.h> // For atoi()

#define MAX 100

int stack[MAX];
int top = -1;

// Function to push into stack
void push(int value) {
    stack[++top] = value;
}

// Function to pop from stack
int pop() {
    return stack[top--];
}

// Function to evaluate postfix expression
int evaluatePostfix(char postfix[]) {
    int i;
    char ch;
    int val;
    
    for (i = 0; postfix[i] != '\0'; i++) {
        ch = postfix[i];
        
        if (isdigit(ch)) {
            // If operand, push onto stack
            push(ch - '0');  // Convert char to int
        }
        else if (ch == ' ') {
            // Ignore spaces
            continue;
        }
        else {
            // Operator encountered
            int val2 = pop();
            int val1 = pop();
            
            switch (ch) {
                case '+':
                    push(val1 + val2);
                    break;
                case '-':
                    push(val1 - val2);
                    break;
                case '*':
                    push(val1 * val2);
                    break;
                case '/':
                    push(val1 / val2);
                    break;
                case '^':
                    {
                        int result = 1;
                        for (int i = 0; i < val2; i++)
                            result *= val1;
                        push(result);
                        break;
                    }
            }
        }
    }
    
    return pop();
}

int main() {
    char postfix[MAX];
    
    printf("Enter a Postfix Expression (single-digit numbers and operators without spaces, like 562+*): ");
    scanf("%s", postfix);
    
    int result = evaluatePostfix(postfix);
    
    printf("Result of Postfix Evaluation: %d\n", result);
    
    return 0;
}


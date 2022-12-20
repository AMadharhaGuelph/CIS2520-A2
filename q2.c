/*
Name: Ankush Madharha
ID: 1172859
Date: 2022-10-22
Assignment Name: Assignment 2 - Linked Lists
*/

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Global Variables
float stack[256];
int stackSize = 0;

// Function declarations
void Push(float element);
float Pop();
void Show();

int main(int argc, char *argv[]) { 
    // Iterate through the expression
    for(int i = 0; i < strlen(argv[1]); i++) {
        if(isdigit(argv[1][i])) {
            // Push the digit to the stack
            Push((argv[1][i]-'0'));
            //Show();
        }
        // Execute if the current element is a operation
        else {
            // Store the two operands
            float operand2 = Pop(stack, stackSize);
            float operand1 = Pop(stack, stackSize);

            // Store the result depending on the operation
            switch(argv[1][i]) {
                case '+':
                    Push(operand1 + operand2);
                    //Show();
                    break;
                case '-':
                    Push(operand1 - operand2);
                    //Show();
                    break;
                case '*':
                    Push(operand1 * operand2);
                    //Show();
                    break;
                default:
                    Push(operand1 / operand2);
                    //Show();
                    break;
            }      
        }
    }

    // Final answer should be the only element left in the stack, output it
    printf("Answer: %.2f", Pop(stack, stackSize));

    return 0;
}

// Push an element to the stack
void Push(float element) {
    stack[stackSize] = element;
    stackSize++;
}

// Pop an element from the stack
float Pop() {
    stackSize--;
    return stack[stackSize];
}

// Output the stack
void Show() {
    for(int i = 0; i < stackSize; i++) {
        printf("[%.2f] ", stack[i]);
    }
    printf("\n");
}
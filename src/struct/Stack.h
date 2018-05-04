/*
 * Stack.h
 *
 * Implementation code based on:
 * https://www.geeksforgeeks.org/stack-data-structure-introduction-program/
 *
 * Adapted for doubles
 *
 *  Created on: May 3, 2018
 *      Author: evan.marcey
 */

#ifndef STRUCT_STACK_H_
#define STRUCT_STACK_H_

struct Stack;

// function to create a stack of given capacity. It initializes size of stack as 0
struct Stack* createStack(unsigned capacity);

// Stack is full when top is equal to the last index
int isFull(struct Stack* stack);

// Stack is empty when top is equal to -1
int isEmpty(struct Stack* stack);

// Function to add an item to stack.  It increases top by 1
void push(struct Stack* stack, double item);

// Function to remove an item from stack.  It decreases top by 1
double pop(struct Stack* stack);

// Function to view the top item in the stack
double get_top(struct Stack* stack);


#endif /* STRUCT_STACK_H_ */

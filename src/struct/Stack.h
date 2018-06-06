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

// A structure to represent a stack
struct Stack;

/*
 * 	createStack:
 * 		- creates a new Stack struct
 *
 * 	params:
 * 		- capacity: max size of Stack
 *
 * 	returns:
 * 		- Stack struct
 */
struct Stack* createStack(unsigned capacity);

/*
 * 	isFull:
 * 		- checks if a Stack is full.
 *
 * 	params:
 * 		- stack: Stack struct to check
 *
 * 	returns:
 * 		- Returns 1 if true, 0 if false
 */
int isFull(struct Stack* stack);

/*
 * 	isFull:
 * 		- checks if a Stack is empty.
 *
 * 	params:
 * 		- stack: Stack struct to check
 *
 * 	returns:
 * 		- Returns 1 if true, 0 if false
 */
int isEmpty(struct Stack* stack);

/*
 * 	push:
 * 		- adds a new item to a stack.
 * 		- increases top by 1
 *
 * 	params:
 * 		- stack: Stack struct to add item to
 * 		- item: value of new item
 */
void push(struct Stack* stack, double item);

/*
 * 	pop:
 * 		- removes an item from a stack.
 * 		- decreases top by 1
 *
 * 	params:
 * 		- stack: Stack struct to pop
 *
 * 	returns:
 * 		- value of popped item
 */
double pop(struct Stack* stack);

/*
 * 	get_top:
 * 		- displays top item of stack
 *
 * 	params:
 * 		- stack: Stack struct to display
 *
 * 	returns:
 * 		- value of top item
 */
double get_top(struct Stack* stack);


#endif /* STRUCT_STACK_H_ */

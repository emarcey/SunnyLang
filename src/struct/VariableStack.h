/*
 * VariableStack.h
 *
 *  Created on: May 7, 2018
 *      Author: evan.marcey
 */

#include "Variable.h"

#ifndef STRUCT_VARIABLESTACK_H_
#define STRUCT_VARIABLESTACK_H_

// A structure to represent a stack of variables
struct VariableStack;

/*
 * 	vs_get_top_num:
 * 		- function to return number of values in VariableStack
 *
 * 	params:
 * 		- stack: VariableStack to check
 *
 * 	returns:
 * 		- int value of stack->top
 */
int vs_get_top_num(struct VariableStack* stack);

/*
 * 	vs_create_stack:
 * 		- creates a new VariableStack struct
 *
 * 	params:
 * 		- capacity: max size of Stack
 *
 * 	returns:
 * 		- VariableStack struct
 */
struct VariableStack* vs_create_stack(unsigned capacity);

/*
 * 	vs_is_full:
 * 		- checks if a VariableStack is full.
 *
 * 	params:
 * 		- stack: VariableStack struct to check
 *
 * 	returns:
 * 		- Returns 1 if true, 0 if false
 */
int vs_is_full(struct VariableStack* VariableStack);

/*
 * 	vs_is_empty:
 * 		- checks if a VariableStack is empty.
 *
 * 	params:
 * 		- stack: VariableStack struct to check
 *
 * 	returns:
 * 		- Returns 1 if true, 0 if false
 */
int vs_is_empty(struct VariableStack* VariableStack);

/*
 * 	vs_push:
 * 		- adds a new item to a VariableStack.
 * 		- increases top by 1
 *
 * 	params:
 * 		- stack: VariableStack struct to add item to
 * 		- item: Variable to add
 */
void vs_push(struct VariableStack* VariableStack, struct Variable* item);

/*
 * 	vs_pop:
 * 		- removes an item from a stack.
 * 		- decreases top by 1
 *
 * 	params:
 * 		- stack: VariableStack struct to pop
 *
 * 	returns:
 * 		- value of popped item
 */
struct Variable* vs_pop(struct VariableStack* stack);

/*
 * 	vs_get_top:
 * 		- displays top item of stack
 *
 * 	params:
 * 		- stack: VariableStack struct to display
 *
 * 	returns:
 * 		- value of top item
 */
struct Variable* vs_get_top(struct VariableStack* stack);

#endif /* STRUCT_VARIABLESTACK_H_ */

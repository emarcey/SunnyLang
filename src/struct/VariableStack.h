/*
 * VariableStack.h
 *
 *  Created on: May 7, 2018
 *      Author: evan.marcey
 */

#include "Variable.h"

#ifndef STRUCT_VARIABLESTACK_H_
#define STRUCT_VARIABLESTACK_H_

struct VariableStack;

// function to create a stack of given capacity. It initializes size of stack as 0
struct VariableStack* vs_create_stack(unsigned capacity);

// Stack is full when top is equal to the last index
int vs_is_full(struct VariableStack* VariableStack);

// Stack is empty when top is equal to -1
int vs_is_empty(struct VariableStack* VariableStack);

// Function to add an item to stack.  It increases top by 1
void vs_push(struct VariableStack* VariableStack, struct Variable* item);

// Function to remove an item from stack.  It decreases top by 1
struct Variable* vs_pop(struct VariableStack* stack);

// Function to view the top item in the stack
struct Variable* vs_get_top(struct VariableStack* stack);

#endif /* STRUCT_VARIABLESTACK_H_ */

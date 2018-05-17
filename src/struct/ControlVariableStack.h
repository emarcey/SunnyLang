/*
 * ControlVariableStack.h
 *
 *  Created on: May 14, 2018
 *      Author: evan.marcey
 */

#include "ControlVariable.h"

#ifndef STRUCT_CONTROLVARIABLESTACK_H_
#define STRUCT_CONTROLVARIABLESTACK_H_

struct ControlVariableStack;

int cvs_get_top_num(struct ControlVariableStack* stack);
// function to create a stack of given capacity. It initializes size of stack as 0
struct ControlVariableStack* cvs_create_stack(unsigned capacity);

// Stack is full when top is equal to the last index
int cvs_is_full(struct ControlVariableStack* ControlVariableStack);

// Stack is empty when top is equal to -1
int cvs_is_empty(struct ControlVariableStack* ControlVariableStack);

// Function to add an item to stack.  It increases top by 1
void cvs_push(struct ControlVariableStack* ControlVariableStack, struct ControlVariable* item);

// Function to remove an item from stack.  It decreases top by 1
struct ControlVariable* cvs_pop(struct ControlVariableStack* stack);

// Function to view the top item in the stack
struct ControlVariable* cvs_get_top(struct ControlVariableStack* stack);

#endif /* STRUCT_CONTROLVARIABLESTACK_H_ */

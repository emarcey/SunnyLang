/*
 * ControlVariableStack.c
 *
 *  Created on: May 14, 2018
 *      Author: evan.marcey
 */


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "../Exceptions.h"
#include "ControlVariable.h"

// A structure to represent a stack
struct ControlVariableStack
{
    int top;
    unsigned capacity;
    struct ControlVariable** array;
};

// function to create a stack of given capacity. It initializes size of
// stack as 0
struct ControlVariableStack* cvs_create_stack(unsigned capacity)
{
    struct ControlVariableStack* stack = (struct ControlVariableStack*) malloc(sizeof(struct ControlVariableStack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct ControlVariable**) malloc(stack->capacity * sizeof(struct ControlVariable*));
    return stack;
}

int cvs_get_top_num(struct ControlVariableStack* stack) {
	return stack->top;
}

// Stack is full when top is equal to the last index
int cvs_is_full(struct ControlVariableStack* stack)
{   return stack->top == stack->capacity - 1; }

// Stack is empty when top is equal to -1
int cvs_is_empty(struct ControlVariableStack* stack)
{   return stack->top == -1;  }

// Function to add an item to stack.  It increases top by 1
void cvs_push(struct ControlVariableStack* stack, struct ControlVariable* item)
{
    if (cvs_is_full(stack))
    	FullStackError(get_control_variable_type(item),__LINE__,__FILE__);
    stack->array[++stack->top] = item;
}

// Function to remove an item from stack.  It decreases top by 1
struct ControlVariable* cvs_pop(struct ControlVariableStack* stack)
{
    if (cvs_is_empty(stack))
        return NULL;
    return stack->array[stack->top--];
}

// Function to view the top item in the stack
struct ControlVariable* cvs_get_top(struct ControlVariableStack* stack) {
	if (cvs_is_empty(stack))
		return NULL;
	return stack->array[stack->top];
}

/*
 * Stack.h
 *
 * Implementation code based on:
 * https://www.geeksforgeeks.org/stack-data-structure-introduction-program/
 *
 * Adapted for variables
 *
 *  Created on: May 7, 2018
 *      Author: evan.marcey
 */
// C program for array implementation of stack
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "Variable.h"
#include "../Exceptions.h"

// A structure to represent a stack
struct VariableStack
{
    int top;
    unsigned capacity;
    struct Variable** array;
};

// function to create a stack of given capacity. It initializes size of
// stack as 0
struct VariableStack* vs_create_stack(unsigned capacity)
{
    struct VariableStack* stack = (struct VariableStack*) malloc(sizeof(struct VariableStack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct Variable**) malloc(stack->capacity * sizeof(struct Variable*));
    return stack;
}

int vs_get_top_num(struct VariableStack* stack) {
	return stack->top;
}

// Stack is full when top is equal to the last index
int vs_is_full(struct VariableStack* stack)
{   return stack->top == stack->capacity - 1; }

// Stack is empty when top is equal to -1
int vs_is_empty(struct VariableStack* stack)
{   return stack->top == -1;  }

// Function to add an item to stack.  It increases top by 1
void vs_push(struct VariableStack* stack, struct Variable* item)
{
    if (vs_is_full(stack))
    	FullStackError(get_variable_name(item),__LINE__,__FILE__);
    stack->array[++stack->top] = item;
}

// Function to remove an item from stack.  It decreases top by 1
struct Variable* vs_pop(struct VariableStack* stack)
{
    if (vs_is_empty(stack))
        return NULL;
    return stack->array[stack->top--];
}

// Function to view the top item in the stack
struct Variable* vs_get_top(struct VariableStack* stack) {
	if (vs_is_empty(stack))
		return NULL;
	return stack->array[stack->top];
}


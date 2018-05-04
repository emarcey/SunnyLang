/*
 * Math_Utils.c
 *
 *  Created on: May 3, 2018
 *      Author: evan.marcey
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#include "../struct/Stack.h"
#include "../Exceptions.h"
#include "String_Utils.h"

int get_precedence(unsigned int c) {

	int num_vals = 6;
	int precedence[][2] = {
				{94,3}, // ^
				{42,2}, // *
				{47,2}, // /
				{37,2}, // %
				{43,1}, // +
				{45,1} // -
		};
	for (int i = 0; i < num_vals; i++) {
		if (c==precedence[i][0]) {
			return precedence[i][1];
		}
	}
	return -1;
}

double eval_op(double op1, double op2, double op) {
	double tmp_val;
	if (op == 43) { //+
		tmp_val = op1+op2;
	} else if (op == 45) { //-
		tmp_val = op1-op2;
	} else if (op == 42) { //*
		tmp_val = op1*op2;
	} else if (op == 47) { // /
		if (op2 != 0) {
			tmp_val = op1/op2;
		} else {
			DivideByZeroError(op1, op2);
		}
	} else if (op == 94) { // ^
		tmp_val = pow(op1,op2);

	} else if (op == 37) { // %
		int tmp_op1 = op1;
		int tmp_op2 = op2;
		if (tmp_op1==op1 && tmp_op2 == op2) {
			tmp_val = tmp_op1%tmp_op2;
		} else {
			ModularArithmeticError(op1, op2);
		}
	}
	return tmp_val;
}

double eval_infix(char *** tokens, int num_tokens) {
	double result = 0;
	int token_index = 0;

	char prev_token_type = 1;

	struct Stack* operand_stack = createStack(num_tokens);
	struct Stack* operator_stack = createStack(num_tokens);
	while (token_index < num_tokens) {
		char tmp_token_type = tokens[token_index][0][0];

		if (tmp_token_type==111 && strlen(tokens[token_index][1]) > 1) {
			char * info = malloc(sizeof(char)*1024);
			sprintf(info,"Token, %s, is not valid for the infix expression", tokens[token_index][1]);
			EvalError(info);
			free(info);
		}
		if (tmp_token_type==110 && prev_token_type==110) {
			char * info = malloc(sizeof(char)*1024);
			sprintf(info,"You have back to back numbers in your expression, with token %s", tokens[token_index][1]);
			EvalError(info);
			free(info);
		}


		char * tmp_token_val = tokens[token_index][1];
		char tmp_token_hash = hash(tmp_token_val);
		int tmp_token_precedence = get_precedence(tmp_token_hash);

		if (tmp_token_type == 110) { //if token is operand
			double tmp_operand = atof(tokens[token_index][1]);
			push(operand_stack,tmp_operand);

		} else if (tmp_token_type == 111
				&& isEmpty(operator_stack)==1
				&& tmp_token_hash != 40
				&& tmp_token_hash != 41) { //if token is operator and stack is empty
			push(operator_stack,tmp_token_hash);

		} else if (tmp_token_type == 111
				&& isEmpty(operator_stack) == 0
				&& tmp_token_hash != 40
				&& tmp_token_hash != 41) { //if token is operator, operator stack is not empty

			double top_val = get_top(operator_stack);
			int tmp_val = top_val;
			int op_precedence = get_precedence(tmp_val);

			if (tmp_token_precedence > op_precedence) { //if token's precedence > top stack value's precedence
				push(operator_stack, tmp_token_hash);
			} else { //process
				double op1 = pop(operand_stack);
				if (isEmpty(operand_stack))
					EvalError("There's something wrong with your expression!");
				double op2 = pop(operand_stack);
				double op = pop(operator_stack);
				double tmp_val = eval_op(op2,op1,op);
				push(operand_stack,tmp_val);
			}

		} else if (tmp_token_type == 111 && tmp_token_hash == 40) { //if token is '('
			push(operator_stack, tmp_token_hash);
		} else if (tmp_token_type == 111 && tmp_token_hash == 41) { //if token is ')'
			while (get_top(operator_stack) != 40) {
				double op1 = pop(operand_stack);
				if (isEmpty(operand_stack))
					EvalError("There's something wrong with your expression!");
				double op2 = pop(operand_stack);
				double op = pop(operator_stack);
				double tmp_val = eval_op(op2,op1,op);
				push(operand_stack,tmp_val);
				if (isEmpty(operator_stack))
					EvalError("There are mismatched parentheses in your expression!");
			}
			pop(operator_stack);
		} else {
			double op1 = pop(operand_stack);
			if (isEmpty(operand_stack))
				EvalError("There's something wrong with your expression!");
			double op2 = pop(operand_stack);
			double op = pop(operator_stack);
			double tmp_val = eval_op(op2,op1,op);
			push(operand_stack,tmp_val);
		}

		prev_token_type = tmp_token_type;

		token_index++;
	}

	while (isEmpty(operator_stack) == 0) {
		double op1 = pop(operand_stack);
		if (isEmpty(operand_stack))
			EvalError("There's something wrong with your expression!");
		double op2 = pop(operand_stack);
		double op = pop(operator_stack);
		if (op == 40 || op == 41)
			EvalError("There are mismatched parentheses in your expression!");
		double tmp_val = eval_op(op2,op1,op);
		push(operand_stack,tmp_val);
	}
	result = get_top(operand_stack);

	return result;
}

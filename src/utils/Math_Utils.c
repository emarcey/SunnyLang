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
#include "../struct/VariableStack.h"
#include "../struct/Token.h"
#include "../struct/Variable.h"
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

struct Variable* eval_op_numeric(struct Variable* op1, struct Variable* op2, double op) {
	struct Variable* tmp_var = malloc(sizeof(struct Variable*));
	double tmp_val=0;
	double op1_val, op2_val;
	if (strcmp(get_variable_type(op1),"float")==0)
		op1_val = get_variable_fval(op1);
	else if (strcmp(get_variable_type(op1),"int")==0 || strcmp(get_variable_type(op1),"boolean")==0)
		op1_val = get_variable_ival(op1);
	if (strcmp(get_variable_type(op2),"float")==0)
		op2_val = get_variable_fval(op2);
	else if (strcmp(get_variable_type(op2),"int")==0 || strcmp(get_variable_type(op2),"boolean")==0)
		op2_val = get_variable_ival(op2);

	if (op == 43) { //+
		tmp_val = op1_val+op2_val;
	} else if (op == 45) { //-
		tmp_val = op1_val-op2_val;
	} else if (op == 42) { //*
		tmp_val = op1_val*op2_val;
	} else if (op == 47) { // /
		if (op2 != 0) {
			tmp_val = op1_val/op2_val;
		} else {
			DivideByZeroError(op1_val, op2_val);
		}
	} else if (op == 94) { // ^
		tmp_val = pow(op1_val,op2_val);
	} else if (op == 37) { // %
		int tmp_op1 = op1_val;
		int tmp_op2 = op2_val;
		if (tmp_op1==op1_val && tmp_op2 == op2_val) {
			tmp_val = tmp_op1%tmp_op2;
		} else {
			ModularArithmeticError(op1_val, op2_val);
		}
	}

	if (strcmp(get_variable_type(op1),"int")==0 && strcmp(get_variable_type(op2),"int")==0) {
		int tmp_int = tmp_val;
		tmp_var = create_variable("int","int",tmp_int,0,"");
	} else {
		tmp_var = create_variable("float","float",0,tmp_val,"");
	}
	return tmp_var;
}

struct Variable* eval_op(struct Variable* op1, struct Variable* op2, double op) {
	struct Variable* tmp_var = malloc(sizeof(struct Variable*));

	if (variable_types_compatible(get_variable_type(op1),get_variable_type(op2))==0)
		MismatchedVariableTypesError(get_variable_name(op1), get_variable_type(op1), get_variable_name(op2), get_variable_type(op2));

	if (strcmp(get_variable_type(op1),"string")==0 && strcmp(get_variable_type(op2),"float")==0) {

	} else {
		tmp_var = eval_op_numeric(op1,op2,op);
	}

	return tmp_var;
}

struct Variable * eval_infix(struct Token ** tokens,
		int num_tokens,
		int token_index,
		struct Variable ** variables,
		int variable_count) {
	struct Variable* result = malloc(sizeof(struct Variable*));

	char prev_token_type = 1;

	struct VariableStack* operand_stack = vs_create_stack(num_tokens);
	struct Stack* operator_stack = createStack(num_tokens);

	while (token_index < num_tokens) {
		char tmp_token_type = get_token_type(tokens[token_index]);
		if ((tmp_token_type=='n' || tmp_token_type=='v' || tmp_token_type=='s') &&
				(prev_token_type=='n' || prev_token_type=='v' || prev_token_type=='s')) {
			char * info = malloc(sizeof(char)*1024);
			sprintf(info,"There is an error in your expression at token %s", get_token_value(tokens[token_index]));
			SyntaxError(info);
		}

		char * tmp_token_val = get_token_value(tokens[token_index]);
		unsigned tmp_token_hash = get_token_hash(tokens[token_index]);
		int tmp_token_precedence = get_token_precedence(tokens[token_index]);

		if (tmp_token_type == 'n') { //if token is numeric operand
			float tmp_operand = atof(tmp_token_val);
			struct Variable* tmp_var = create_variable("float","float",0,tmp_operand,"");
			vs_push(operand_stack,tmp_var);
		} else if (tmp_token_type == 's') { //if token is string operand
			struct Variable* tmp_var = create_variable("string","string",0,0,tmp_token_val);
			vs_push(operand_stack,tmp_var);
		} else if (tmp_token_type == 'v') { //if token is variable
			int var_index = variable_index(variables,variable_count,tmp_token_hash);
			if (var_index==-1) {
				VariableNotFoundError(tmp_token_val);
			}
			if (strcmp(get_variable_type(variables[var_index]),"string")==0) {
				char * info = malloc(sizeof(char)*1024);
				sprintf(info,"Strings not supported right now, %s", get_token_value(tokens[token_index]));
				SyntaxError(info);
			} else {
				vs_push(operand_stack,variables[var_index]);
			}
		} else if (tmp_token_type == 'o'
				&& isEmpty(operator_stack)==1
				&& tmp_token_hash != ')') { //if token is operator and stack is empty
			push(operator_stack,tmp_token_hash);

		} else if (tmp_token_type == 'o'
				&& isEmpty(operator_stack) == 0
				&& tmp_token_hash != '('
				&& tmp_token_hash != ')') { //if token is operator, operator stack is not empty

			double top_val = get_top(operator_stack);
			int tmp_val = top_val;
			int op_precedence = get_precedence(tmp_val);

			if (tmp_token_precedence > op_precedence) { //if token's precedence > top stack value's precedence
				push(operator_stack, tmp_token_hash);
			} else { //process
				struct Variable* op1 = vs_pop(operand_stack);
				if (vs_is_empty(operand_stack))
					EvalError("There's something wrong with your expression!");
				struct Variable* op2 = vs_pop(operand_stack);
				double op = tmp_token_hash;
				struct Variable* tmp_var = eval_op(op2,op1,op);
				vs_push(operand_stack,tmp_var);
			}

		} else if (tmp_token_type == 'o' && tmp_token_hash == '(') { //if token is '('
			push(operator_stack, tmp_token_hash);
		} else if (tmp_token_type == 'o' && tmp_token_hash == ')') { //if token is ')'
			while (get_top(operator_stack) != 40) {
				struct Variable* op1 = vs_pop(operand_stack);
				if (vs_is_empty(operand_stack))
					EvalError("There's something wrong with your expression!");
				struct Variable* op2 = vs_pop(operand_stack);
				double op = pop(operator_stack);
				struct Variable* tmp_var = eval_op(op2,op1,op);
				vs_push(operand_stack,tmp_var);
				if (isEmpty(operator_stack))
					EvalError("There are mismatched parentheses in your expression!");
			}
			pop(operator_stack);
		} else {
			struct Variable* op1 = vs_pop(operand_stack);
			if (vs_is_empty(operand_stack))
				EvalError("There's something wrong with your expression!");
			struct Variable* op2 = vs_pop(operand_stack);
			double op = pop(operator_stack);
			struct Variable* tmp_var = eval_op(op2,op1,op);
			vs_push(operand_stack,tmp_var);
		}

		prev_token_type = tmp_token_type;

		token_index++;
	}

	while (isEmpty(operator_stack) == 0) {
		struct Variable* op1 = vs_pop(operand_stack);
		if (vs_is_empty(operand_stack))
			EvalError("There's something wrong with your expression!");
		struct Variable* op2 = vs_pop(operand_stack);
		double op = pop(operator_stack);
		if (op == '(' || op == ')')
			EvalError("There are mismatched parentheses in your expression!");
		struct Variable* tmp_var = eval_op(op2,op1,op);
		vs_push(operand_stack,tmp_var);
	}
	result = vs_get_top(operand_stack);

	return result;
}

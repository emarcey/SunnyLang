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
#include "Misc_Utils.h"

int get_precedence(unsigned int c) {
	// regular operators have positive precedence
	// looping operators have negative precedence
	int precedence[][2] = {
				{94,3}, // ^
				{42,2}, // *
				{47,2}, // /
				{37,2}, // %
				{43,1}, // +
				{45,1}, // -
				{1952,-1},// ==
				{1921,-1}, // <=
				{1983,-1}, // >=
				{60,-1}, // <
				{62,-1}, // >
				{96727,-2}, // and
				{3555,-2}, //or
				{40,-3}, // (
				{41,-3}, // )
				{-1,-1} //end
		};
	int i = 0;

	while (precedence[i][0] != -1) {
		if (c==precedence[i][0]) {
			return precedence[i][1];
		}
		i++;
	}

	return -100;
}

struct Variable* eval_op_numeric(struct Variable* op1,
		struct Variable* op2,
		double op) {
	struct Variable* tmp_var = malloc(sizeof(struct Variable*));
	double tmp_val=0;
	double op1_val, op2_val;
	unsigned tmp_op = op;
	if (strcmp(get_variable_type(op1),"float")==0)
		op1_val = get_variable_fval(op1);
	else
		op1_val = get_variable_ival(op1);
	if (strcmp(get_variable_type(op2),"float")==0)
		op2_val = get_variable_fval(op2);
	else
		op2_val = get_variable_ival(op2);

	char * info = malloc(sizeof(char)*1024);
	int tmp_op1 = op1_val;
	int tmp_op2 = op2_val;
	switch(tmp_op) {

		case 37: // %
			if (tmp_op1==op1_val && tmp_op2 == op2_val) tmp_val = tmp_op1%tmp_op2;
			else ModularArithmeticError(op1_val, op2_val,__LINE__,__FILE__);
			break;
		case 42: // *
			tmp_val = op1_val*op2_val;
			break;
		case 43: // +
			tmp_val = op1_val+op2_val;
			break;
		case 45: // -
			tmp_val = op1_val-op2_val;
			break;
		case 47: // /
			if (op2 != 0) tmp_val = op1_val/op2_val;
			else DivideByZeroError(op1_val, op2_val,__LINE__,__FILE__);
			break;
		case 60: // <
			tmp_val = op1_val < op2_val;
			break;
		case 62: // >
			tmp_val = op1_val > op2_val;
			break;
		case 94: // ^
			tmp_val = pow(op1_val,op2_val);
			break;
		case 1921: // <=
			tmp_val = op1_val <= op2_val;
			break;
		case 1952: // ==
			tmp_val = op1_val == op2_val;
			break;
		case 1983: // >=
			tmp_val = op1_val >= op2_val;
			break;
		case 3555: // or
			if (op1_val+op2_val == 1 || op1_val+op2_val == 2) tmp_val = 1;
			else if (op1_val + op2_val == 0) tmp_val = 0;
			else {
				char * info = malloc(sizeof(char)*1024);
				sprintf(info,"Invalid values, %f and %f, passed to or statement.",op1_val,op2_val);
				InvalidValueError(info,__LINE__,__FILE__);
			}
			break;
		case 96727: //and
			if (op1_val+op2_val == 2) tmp_val = 1;
			else if (op1_val+op2_val == 1 || op1_val+op2_val == 0) tmp_val = 0;
			else {
				char * info = malloc(sizeof(char)*1024);
				sprintf(info,"Invalid values, %f and %f, passed to and statement.",op1_val,op2_val);
				InvalidValueError(info,__LINE__,__FILE__);
			}
			break;

		default:
			sprintf(info,"Unknown mathematical operator: %f",op);
			InvalidValueError(info,__LINE__,__FILE__);
	}

	if (strcmp(get_variable_type(op1),"int")==0 && strcmp(get_variable_type(op2),"int")==0) {
		int tmp_int = tmp_val;
		tmp_var = create_variable("int","int",tmp_int,0,"",-1,-1);
	} else
		tmp_var = create_variable("float","float",0,tmp_val,"",-1,-1);
	return tmp_var;
}

struct Variable* eval_op_string(struct Variable* op1, struct Variable* op2, double op) {
	struct Variable* tmp_var = malloc(sizeof(struct Variable*));

	return tmp_var;
}

struct Variable* eval_op(struct Variable* op1, struct Variable* op2, double op) {
	struct Variable* tmp_var = malloc(sizeof(struct Variable*));

	if (variable_types_compatible(get_variable_type(op1),get_variable_type(op2))==0)
		MismatchedVariableTypesError(get_variable_name(op1),
				get_variable_type(op1),
				get_variable_name(op2),
				get_variable_type(op2),
				__LINE__,
				__FILE__);

	if (strcmp(get_variable_type(op1),"string")==0 && strcmp(get_variable_type(op2),"float")==0) {
		//need to add code for handling strings
	} else
		tmp_var = eval_op_numeric(op1,op2,op);

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
			SyntaxError(info,__LINE__,__FILE__);
		}

		char * tmp_token_val = get_token_value(tokens[token_index]);
		unsigned tmp_token_hash = get_token_hash(tokens[token_index]);
		int tmp_token_precedence = get_token_precedence(tokens[token_index]);

		if (tmp_token_type == 'n') { //if token is numeric operand
			float tmp_operand = atof(tmp_token_val);
			struct Variable* tmp_var = create_variable("float","float",0,tmp_operand,"",-1,-1);
			vs_push(operand_stack,tmp_var);
		} else if (tmp_token_type == 's') { //if token is string operand
			struct Variable* tmp_var = create_variable("string","string",0,0,tmp_token_val,-1,-1);
			vs_push(operand_stack,tmp_var);
		} else if (tmp_token_type == 'v') { //if token is variable
			int var_index = variable_index(variables,variable_count,tmp_token_hash);
			if (var_index==-1) {
				VariableNotFoundError(tmp_token_val,__LINE__,__FILE__);
			}
			vs_push(operand_stack,variables[var_index]);
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
					EvalError("Operand stack is empty - there's something wrong with your expression!",__LINE__,__FILE__);
				struct Variable* op2 = vs_pop(operand_stack);
				double op = tmp_token_hash;
				struct Variable* tmp_var = eval_op(op2,op1,op);
				vs_push(operand_stack,tmp_var);
			}

		} else if (tmp_token_type == 'o' && tmp_token_hash == '(') { //if token is '('
			push(operator_stack, tmp_token_hash);
		} else if (tmp_token_type == 'o' && tmp_token_precedence < 0) { //if token is ')'
			while (tmp_token_precedence > get_precedence(get_top(operator_stack))) {
				struct Variable* op1 = vs_pop(operand_stack);

				if (tmp_token_hash == ')' && vs_is_empty(operand_stack))
					EvalError("Operand stack is empty - there's something wrong with your expression!",__LINE__,__FILE__);
				struct Variable* op2 = vs_pop(operand_stack);
				double op = pop(operator_stack);
				struct Variable* tmp_var = eval_op(op2,op1,op);
				vs_push(operand_stack,tmp_var);
				if (tmp_token_hash == ')' && isEmpty(operator_stack))
					EvalError("There are mismatched parentheses in your expression!",__LINE__,__FILE__);
			}
			pop(operator_stack);
			if (tmp_token_hash != ')')
				push(operator_stack,tmp_token_hash);
		} else {
			struct Variable* op1 = vs_pop(operand_stack);
			if (vs_is_empty(operand_stack))
				EvalError("Operand stack is empty - there's something wrong with your expression!",__LINE__,__FILE__);
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
			EvalError("Operand stack is empty - there's something wrong with your expression!",__LINE__,__FILE__);
		struct Variable* op2 = vs_pop(operand_stack);
		double op = pop(operator_stack);
		if (op == '(' || op == ')')
			EvalError("There are mismatched parentheses in your expression!",__LINE__,__FILE__);
		struct Variable* tmp_var = eval_op(op2,op1,op);
		vs_push(operand_stack,tmp_var);
	}
	result = vs_get_top(operand_stack);

	return result;
}

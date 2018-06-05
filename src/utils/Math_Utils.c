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
#include "../Tokenizer.h"
#include "String_Utils.h"
#include "Misc_Utils.h"

int get_precedence(unsigned int c) {
	// regular operators have positive precedence
	// looping operators have negative precedence
	int precedence[][2] = {
				{94,4}, // ^
				{42,3}, // *
				{47,3}, // /
				{37,3}, // %
				{43,2}, // +
				{45,2}, // -
				{1952,1},// ==
				{1921,1}, // <=
				{1983,1}, // >=
				{60,1}, // <
				{62,1}, // >
				{96727,0}, // and
				{3555,0}, //or
				{40,10}, // (
				{41,10}, // )
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


struct Variable * eval_function(struct Variable * eval_func,
		struct Token ** tokens,
		int num_tokens,
		int token_index,
		struct Variable ** variables,
		int variable_count,
		struct Token *** token_array,
		int num_token_rows,
		int token_array_lengths[],
		int depth,
		struct VariableStack * control_flow_stack) {
	int v_start_line = get_variable_func_start_line(eval_func);
	int v_end_line = get_variable_func_end_line(eval_func);
	int v_num_tokens = token_array_lengths[v_start_line];
	struct Token ** v_tokens = token_array[v_start_line];

	// create return variable
	struct Variable * result_func = malloc(sizeof(struct Variable *));
	result_func = create_variable(get_token_value(v_tokens[1]),"func_result",-1,-1,"",-1,depth);

	//make sure we have the right number of tokens
	if (num_tokens-token_index-1 != (v_num_tokens-3)/2) {
		char * info = malloc(sizeof(char)*1024);
		sprintf(info,"Mismatched arguments in for statement call.");
		SyntaxError(info,__LINE__,__FILE__);
	}

	//start by creating an array of the parameters passed to the function
	for (int i = 3; i < v_num_tokens-1; i+=2) {
		int tmp_assign_variable_ind = variable_index(variables,variable_count,get_token_hash(tokens[token_index+(i-1)/2]));

		if (tmp_assign_variable_ind==-1) {
			VariableNotFoundError(get_token_value(tokens[token_index+(i-1)/2]),__LINE__,__FILE__);
		}
		struct Variable * tmp_assign_variable = create_variable(get_token_value(v_tokens[i+1]),
				get_token_value(v_tokens[i]),
				0,0,"",-1,depth);

		// make sure all the data types are compatible
		if (variable_types_compatible(get_variable_type(tmp_assign_variable),get_variable_type(variables[tmp_assign_variable_ind]))==0)
			MismatchedVariableTypesError(get_variable_name(tmp_assign_variable),
					get_variable_type(tmp_assign_variable),
					get_variable_name(variables[tmp_assign_variable_ind]),
					get_variable_type(variables[tmp_assign_variable_ind]),
					__LINE__,
					__FILE__);

		assign_variable_value(tmp_assign_variable,
				get_variable_ival(variables[tmp_assign_variable_ind]),
				get_variable_fval(variables[tmp_assign_variable_ind]),
				get_variable_cval(variables[tmp_assign_variable_ind]));

		variables[variable_count] = tmp_assign_variable;
		variable_count++;
	}

	int i = v_start_line+1;
	while (i < v_end_line) {
		int line_number = i;
		result_func = eval_line(token_array[i],
				token_array_lengths[i],
				variables,
				&variable_count,
				control_flow_stack,
				&line_number,
				&depth,
				token_array,
				num_token_rows,
				token_array_lengths);
		if (line_number != i) {
			i = line_number;
		}
		else i++;

	}
	if (result_func==NULL)
		return create_variable("void","void",-1,-1,"",-1,depth);
	return result_func;
}

struct Variable * eval_infix(struct Token ** tokens,
		int num_tokens,
		int token_index,
		struct Variable ** variables,
		int variable_count,
		struct Token *** token_array,
		int num_token_rows,
		int * token_array_lengths,
		int * depth,
		struct VariableStack * control_flow_stack) {
	int tmp_depth = *depth;
	struct Variable* result = malloc(sizeof(struct Variable*));

	//char prev_token_type = 1;

	struct VariableStack* operand_stack = vs_create_stack(num_tokens);
	struct Stack* operator_stack = createStack(num_tokens);

	while (token_index < num_tokens) {

		char tmp_token_type = get_token_type(tokens[token_index]);
		/*
		if ((tmp_token_type=='n' || tmp_token_type=='v' || tmp_token_type=='s') &&
				(prev_token_type=='n' || prev_token_type=='v' || prev_token_type=='s')) {
			char * info = malloc(sizeof(char)*1024);
			sprintf(info,"There is an error in your expression at token %s", get_token_value(tokens[token_index]));
			SyntaxError(info,__LINE__,__FILE__);
		}
		*/

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
			// if variable is not found
			if (var_index==-1) {
				VariableNotFoundError(tmp_token_val,__LINE__,__FILE__);
			}
			// if variable points to a function
			if (strcmp(get_variable_type(variables[var_index]),"function")==0) {
				struct Variable * tmp_eval_func_result = eval_function(variables[var_index],
						tokens,
						num_tokens,
						token_index,
						variables,
						variable_count,
						token_array,
						num_token_rows,
						token_array_lengths,
						tmp_depth+1,
						control_flow_stack);
				vs_push(operand_stack,tmp_eval_func_result);

				token_index += get_variable_func_num_arguments(variables[var_index]);
			} else {
				vs_push(operand_stack,variables[var_index]);
			}
		} else if (tmp_token_type == 'o' && tmp_token_hash == '(') { //if token is '('
			push(operator_stack, tmp_token_hash);
		} else if (tmp_token_type == 'o' && tmp_token_hash != ')') {
			if (isEmpty(operator_stack)==1)
				push(operator_stack,tmp_token_hash);
			else {
				while (isEmpty(operator_stack) == 0 &&
						tmp_token_precedence > get_precedence(get_top(operator_stack))) {
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
				push(operator_stack,tmp_token_hash);
			}
		} else {
			while (isEmpty(operator_stack) == 0 &&
					get_top(operator_stack)!='(') {
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
		}
		//prev_token_type = tmp_token_type;

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
		if (strcmp(get_variable_name(op1),"void")==0 || strcmp(get_variable_name(op2),"void")==0 ) {
			EvalError("Cannot evaluate null objects.",__LINE__,__FILE__);
		}
		struct Variable* tmp_var = eval_op(op2,op1,op);
		vs_push(operand_stack,tmp_var);
	}
	result = vs_get_top(operand_stack);
	*depth = tmp_depth;

	return result;
}

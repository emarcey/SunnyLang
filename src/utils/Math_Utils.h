/*
 * Math_Utils.h
 *
 *  Created on: May 3, 2018
 *      Author: evan.marcey
 */
#include "../struct/Token.h"
#include "../struct/Variable.h"
#include "../struct/VariableStack.h"

#ifndef MATH_UTILS_H_
#define MATH_UTILS_H_

/*
 * get_precedence:
 * 	- for a given character, c, representing an operator, returns the precedence
 *  - currently supports +,-,/,*,^,%
 *
 * params:
 *  - c: ASCII value of operator
 *
 * returns:
 *  - precedence for character
 */
int get_precedence(unsigned int c);

/*
 *  eval_op_numeric:
 *  	- function that handles eval_op when both operands are numeric types
 *
 *  params:
 *  	- op1: first numeric variable to evaluate
 *  	- op2: second numeric variable to evaluate
 *  	- op: hash value of operator
 *
 *  returns:
 *  	- Variable with value as result of evaluation
 */
struct Variable* eval_op_numeric(struct Variable* op1, struct Variable* op2, double op);

/*
 *  eval_op_string:
 *  	- function that handles eval_op when both operands are string types
 *
 *  params:
 *  	- op1: first string variable to evaluate
 *  	- op2: second string variable to evaluate
 *  	- op: hash value of operator
 *
 *  returns:
 *  	- Variable with value as result of evaluation
 */
struct Variable* eval_op_string(struct Variable* op1, struct Variable* op2, double op);

/*
 *  eval_op_num_string:
 *  	- function that handles eval_op when both operands are string types
 *
 *  params:
 *  	- op1: string variable to evaluate
 *  	- op2: numeric variable to evaluate
 *  	- op: hash value of operator
 *
 *  returns:
 *  	- Variable with value as result of evaluation
 */
struct Variable* eval_op_num_string(struct Variable* op1, struct Variable* op2, double op) ;

/*
 *	eval_function:
 *		- function that evaluates a custom SunnyLang function
 *
 *	params:
 *		- eval_func: Variable for function to evaluate
 *		- tokens: pointer to array of Tokens for current line in input script
 *		- num_tokens: number of Tokens in tokens
 *		- token_index: index in tokens where function is called
 *		- variables: pointer to array of Variables in environment
 *		- variable_count: number of variables in variables
 *		- token_array: pointer to array of arrays of Tokens for entire input script
 *		- num_token_rows: number of tokens in token_array
 *		- token_array_lengths: number of tokens in each line of token_array
 *		- depth: environment function nest depth
 *		- control_flow_stack: VariableStack containing nested control flow elements
 *
 *	returns:
 *		- variable containing output of eval_func
 *
 */
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
		struct VariableStack * control_flow_stack);

/*
 * eval_op:
 *  - evaluates a simple expression, two operands and one operator in the format: op1 op op2
 *
 * params:
 * 	- op1: variable with first operand
 * 	- op2: variable with second operand
 *  - op: operator
 *
 * returns:
 *  - variable with value of operation
 */
struct Variable* eval_op(struct Variable* op1, struct Variable* op2, double op);

/*
 * eval_infix:
 * 	- evaluates a mathematical expression in infix notation
 *
 * params:
 *  - tokens: array of tokens where each row has [token_type, token]
 *  - num_tokens: number of tokens in tokens
 *
 * returns:
 *  - result of evaluation
 */
struct Variable* eval_infix(struct Token ** tokens,
		int num_tokens,
		int token_index,
		struct Variable ** variables,
		int variable_count,
		struct Token *** token_array,
		int num_token_rows,
		int * token_array_lengths,
		int * depth,
		struct VariableStack * control_flow_stack);


#endif /* MATH_UTILS_H_ */

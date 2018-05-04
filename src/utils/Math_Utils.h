/*
 * Math_Utils.h
 *
 *  Created on: May 3, 2018
 *      Author: evan.marcey
 */

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
int get_precedence(char c);

/*
 * eval_op:
 *  - evaluates a simple expression, two operands and one operator in the format: op1 op op2
 *  - i.e. (1 + 2)
 *  - currently supports +,-,/,*,^,%
 *
 * params:
 * 	- op1: first operand
 * 	- op2: second operand
 *  - op: operator
 *
 * returns:
 *  - value of operation
 */
double eval_op(double op1, double op2, char op);

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
double eval_infix(char *** tokens, int num_tokens);


#endif /* MATH_UTILS_H_ */

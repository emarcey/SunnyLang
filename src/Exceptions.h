/*
 * Exceptions.h
 *
 *  Created on: May 3, 2018
 *      Author: evan.marcey
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

void RaiseError(char * error_type, char * message);

void DivideByZeroError(double op1, double op2);

void ModularArithmeticError(double op1, double op2);

void CommandArgumentError(char * info);

void EvalError(char * info);



#endif /* EXCEPTIONS_H_ */

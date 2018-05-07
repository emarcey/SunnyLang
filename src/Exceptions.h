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

void InvalidValueError(char * info);

void TypeNotRecognizedError(char * v_type, char * name, char * struct_name);

void InvalidVariableName(char * name);

void TokenizationError(char * token, char * info);

void VariableAlreadyExistsError(char * variable_name);

void SyntaxError(char * info);

void VariableNotfoundError(char * variable_name);

#endif /* EXCEPTIONS_H_ */

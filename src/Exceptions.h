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

void VariableNotFoundError(char * variable_name);

void EmptyStackError();

void FullStackError(char * item_name);

void MismatchedTypesError(char * variable_name, char * variable_type, char * target_type);

void MismatchedVariableTypesError(char * variable_name1, char * variable_type1, char * variable_name2, char * variable_type2);

#endif /* EXCEPTIONS_H_ */

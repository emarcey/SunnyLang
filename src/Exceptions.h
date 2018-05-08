/*
 * Exceptions.h
 *
 *  Created on: May 3, 2018
 *      Author: evan.marcey
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

void RaiseError(char * error_type, char * message, int line_number, char * file_name);

void DivideByZeroError(double op1, double op2, int line_number, char * file_name);

void ModularArithmeticError(double op1, double op2, int line_number, char * file_name);

void CommandArgumentError(char * info, int line_number, char * file_name);

void EvalError(char * info, int line_number, char * file_name);

void InvalidValueError(char * info, int line_number, char * file_name);

void TypeNotRecognizedError(char * v_type, char * name, char * struct_name, int line_number, char * file_name);

void InvalidVariableName(char * name, int line_number, char * file_name);

void TokenizationError(char * token, char * info, int line_number, char * file_name);

void VariableAlreadyExistsError(char * variable_name, int line_number, char * file_name);

void SyntaxError(char * info, int line_number, char * file_name);

void VariableNotFoundError(char * variable_name, int line_number, char * file_name);

void EmptyStackError(int line_number, char * file_name);

void FullStackError(char * item_name, int line_number, char * file_name);

void MismatchedTypesError(char * variable_name, char * variable_type, char * target_type, int line_number, char * file_name);

void MismatchedVariableTypesError(char * variable_name1,
		char * variable_type1,
		char * variable_name2,
		char * variable_type2,
		int line_number,
		char * file_name);

void InvalidIfError(char * value, int line_number, char * file_name);

#endif /* EXCEPTIONS_H_ */

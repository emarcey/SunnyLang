/*
 * Exceptions.c
 *
 *  Created on: May 3, 2018
 *      Author: evan.marcey
 */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "GlobalVariables.h"

void RaiseError(char * error_type, char * message, int line_number, char * file_name) {
	fprintf(stderr,"%s\n\tError occurred at line %d of file %s in source code during run.\n\t%s\n",error_type,line_number,file_name,message);
	exit(EXIT_FAILURE);
}

void RaiseSunnyError(char * error_type, char * message, int line_number, char * file_name) {
	char * v_message = malloc(sizeof(char)*1024);
	sprintf(v_message,"Error occurred at line %d of SunnyLang input file.\n\t%s\n",SunnyLineNumber+1,message);
	RaiseError(error_type,v_message,line_number,file_name);
}

void DivideByZeroError(double op1, double op2, int line_number, char * file_name) {
	char * type = "DivideByZeroError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Division by zero with operands: %f, %f",op1,op2);
	RaiseSunnyError(type, message, line_number, file_name);
}

void ModularArithmeticError(double op1, double op2, int line_number, char * file_name) {

	char * type = "ModularArithmeticError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Cannot perform modular arithmetic with the following operands: %f, %f",op1,op2);
	RaiseSunnyError(type, message, line_number, file_name);

}

void CommandArgumentError(char * info, int line_number, char * file_name) {
	char * type = "CommandArgumentError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Error occurred with command arguments:\n%s\n",info);
	RaiseError(type, message, line_number, file_name);
}

void FileNotFoundError(char * in_file_name, int line_number, char * file_name) {
	char * type = "FileNotFoundError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"File %s not found or could not be opened.\n",in_file_name);
	RaiseError(type, message, line_number, file_name);
}


void EvalError(char * info, int line_number, char * file_name) {
	char * type = "EvalError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Error occurred during evaluation of an expression:\n%s\n",info);
	RaiseSunnyError(type, message, line_number, file_name);
}

void InvalidValueError(char * info, int line_number, char * file_name) {
	char * type = "InvalidValueError";

	RaiseSunnyError(type, info, line_number, file_name);
}

void TypeNotRecognizedError(char * v_type, char * name, char * struct_name, int line_number, char * file_name) {
	char * type = "TypeNotRecognizedError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Attempted to instantiate %s %s with unrecognized type %s.",struct_name,name,v_type);

	RaiseSunnyError(type, message, line_number, file_name);
}

void ListTypeNotRecognizedError(char * v_type, char * struct_name, int line_number, char * file_name) {
	char * type = "ListTypeNotRecognizedError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Attempted to instantiate %s with unrecognized type %s.",struct_name,v_type);

	RaiseSunnyError(type, message, line_number, file_name);
}

void InvalidTypeReturnError(char * v_type, char * struct_name, char * value_type, int line_number, char * file_name) {
	char * type = "InvalidTypeReturnError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Attempted to call value for %s with %s of type %s.",value_type,struct_name,v_type);

	RaiseSunnyError(type, message, line_number, file_name);
}

void IndexOutOfBoundsError(unsigned int v_index, unsigned int length, int line_number, char * file_name) {
	char * type = "IndexOutOfBoundsError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Index %u is out of bounds of array with length %u",v_index,length);

	RaiseSunnyError(type, message, line_number, file_name);
}

void InvalidVariableName(char * name, int line_number, char * file_name){
	char * type = "InvalidVariableName";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Unable to create variable %s. Variable name must be alpha-numeric and cannot start with a number.",name);

	RaiseSunnyError(type,message, line_number, file_name);
}

void TokenizationError(char * token, char * info, int line_number, char * file_name) {
	char * type = "TokenizationError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Error occurred during tokenization at token %s:\n%s\n",token,info);
	RaiseSunnyError(type, message, line_number, file_name);
}

void VariableAlreadyExistsError(char * variable_name, int line_number, char * file_name) {
	char * type = "VariableAlreadyExistsError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Variable %s already exists. Cannot declare again.",variable_name);
	RaiseSunnyError(type, message, line_number, file_name);
}

void SyntaxError(char * info, int line_number, char * file_name) {
	char * type = "SyntaxError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Error occurred during evaluation of an expression:\n%s\n",info);
	RaiseSunnyError(type, message, line_number, file_name);
}

void VariableNotFoundError(char * variable_name, int line_number, char * file_name) {
	char * type = "VariableNotfoundError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Variable %s has not been declared yet.",variable_name);
	RaiseSunnyError(type, message, line_number, file_name);
}

void EmptyStackError(int line_number, char * file_name) {
	char * type = "EmptyStackError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"You can't pop an empty stack.");
	RaiseError(type, message, line_number, file_name);
}

void EmptyListError(int line_number, char * file_name) {
	char * type = "EmptyStackError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"You can't remove an item from an empty list.");
	RaiseSunnyError(type, message, line_number, file_name);
}

void FullStackError(char * item_name, int line_number, char * file_name) {
	char * type = "FullStackError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Stack is full; unable to add element, %s.",item_name);
	RaiseError(type, message, line_number, file_name);
}

void MismatchedTypesError(char * variable_name, char * variable_type, char * target_type, int line_number, char * file_name) {
	char * type = "MismatchedTypesError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Attempted to populate %s variable %s with %s data.",variable_type,variable_name,target_type);
	RaiseSunnyError(type, message, line_number, file_name);
}

void MismatchedVariableTypesError(char * variable_name1,
		char * variable_type1,
		char * variable_name2,
		char * variable_type2,
		int line_number,
		char * file_name) {
	char * type = "MismatchedVariableTypesError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Cannot compare %s variable %s with %s variable %s.",variable_type1,variable_name1,variable_type2,variable_name2);
	RaiseSunnyError(type, message, line_number, file_name);
}

void InvalidConditionValueError(char * value, int line_number, char * file_name) {
	char * type = "InvalidIfError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"%s is not a valid value for Condition statement.",value);
	RaiseSunnyError(type, message, line_number, file_name);
}

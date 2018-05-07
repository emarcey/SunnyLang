/*
 * Exceptions.c
 *
 *  Created on: May 3, 2018
 *      Author: evan.marcey
 */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void RaiseError(char * error_type, char * message) {
	fprintf(stderr,"%s occurred during run.\n%s\n",error_type,message);
	exit(EXIT_FAILURE);
}

void DivideByZeroError(double op1, double op2) {

	char * type = "DivideByZeroError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Division by zero with operands: %f, %f",op1,op2);
	RaiseError(type, message);
}

void ModularArithmeticError(double op1, double op2) {

	char * type = "ModularArithmeticError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Cannot perform modular arithmetic with the following operands: %f, %f",op1,op2);
	RaiseError(type, message);

}

void CommandArgumentError(char * info) {
	char * type = "CommandArgumentError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Error occurred with command arguments:\n%s\n",info);
	RaiseError(type, message);
}

void EvalError(char * info) {
	char * type = "EvalError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Error occurred during evaluation of an expression:\n%s\n",info);
	RaiseError(type, message);
}

void InvalidValueError(char * info) {
	char * type = "InvalidValueError";

	RaiseError(type, info);
}

void TypeNotRecognizedError(char * v_type, char * name, char * struct_name) {
	char * type = "TypeNotRecognizedError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Attempted to instantiate %s %s with unrecognized type %s.",struct_name,name,v_type);

	RaiseError(type, message);
}

void InvalidVariableName(char * name){
	char * type = "InvalidVariableName";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Unable to create variable %s. Variable name must be alpha-numeric and cannot start with a number.",name);

	RaiseError(type,message);
}

void TokenizationError(char * token, char * info) {
	char * type = "TokenizationError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Error occurred during tokenization at token %s:\n%s\n",token,info);
	RaiseError(type, message);
}

void VariableAlreadyExistsError(char * variable_name) {
	char * type = "VariableAlreadyExistsError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Variable %s already exists. Cannot declare again.",variable_name);
	RaiseError(type, message);
}

void SyntaxError(char * info) {
	char * type = "SyntaxError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Error occurred during evaluation of an expression:\n%s\n",info);
	RaiseError(type, message);
}

void VariableNotFoundError(char * variable_name) {
	char * type = "VariableNotfoundError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Variable %s has not been declared yet.",variable_name);
	RaiseError(type, message);
}

void EmptyStackError() {
	char * type = "EmptyStackError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"You can't pop an empty stack.");
	RaiseError(type, message);
}

void FullStackError(char * item_name) {
	char * type = "FullStackError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Stack is full; unable to add element, %s.",item_name);
	RaiseError(type, message);
}

void MismatchedTypesError(char * variable_name, char * variable_type, char * target_type) {
	char * type = "MismatchedTypesError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Attempted to populate %s variable %s with %s data.",variable_type,variable_name,target_type);
	RaiseError(type, message);
}

void MismatchedVariableTypesError(char * variable_name1, char * variable_type1, char * variable_name2, char * variable_type2) {
	char * type = "MismatchedVariableTypesError";
	char * message = malloc(sizeof(char)*1024);

	sprintf(message,"Cannot compare %s variable %s with %s variable %s.",variable_type1,variable_name1,variable_type2,variable_name2);
	RaiseError(type, message);
}

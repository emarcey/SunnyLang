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



/*
 * Function.c
 *
 *  Created on: Jun 4, 2018
 *      Author: evan.marcey
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "../Exceptions.h"

struct Function_Data {
	int num_arguments;
	int num_returns;
	int start_line;
	int end_line;
};

struct Function_Data * create_function_data(int num_arguments,
	int num_returns,
	int start_line,
	int end_line) {

	char * info = malloc(sizeof(char)*1024);
	struct Function_Data * func = (struct Function_Data *) malloc(sizeof(struct Function_Data));

	if (num_arguments < 0) {
		sprintf(info,"Function cannot have fewer than 0 arguments.");
		InvalidValueError(info,__LINE__,__FILE__);
	}

	if (num_returns < 0) {
		sprintf(info,"Function cannot have fewer than 0 return values.");
		InvalidValueError(info,__LINE__,__FILE__);
	}

	if (start_line < 0) {
		sprintf(info,"Function start line %d invalid.",start_line);
		InvalidValueError(info,__LINE__,__FILE__);
	}

	if (end_line < 0) {
		sprintf(info,"Function end line %d invalid.",end_line);
		InvalidValueError(info,__LINE__,__FILE__);
	}

	free(info);

	func->num_arguments=num_arguments;
	func->num_returns=num_returns;
	func->start_line=start_line;
	func->end_line=end_line;
	return func;
}

int func_get_num_arguments(struct Function_Data * func) {
	return func->num_arguments;
}

int func_get_num_returns(struct Function_Data * func) {
	return func->num_returns;
}

int func_get_start_line(struct Function_Data * func) {
	return func->start_line;
}

int func_get_end_line(struct Function_Data * func) {
	return func->end_line;
}

void func_assign_num_arguments(struct Function_Data * func,
		int num_arguments) {
	char * info = malloc(sizeof(char)*1024);

	if (num_arguments < 0) {
		sprintf(info,"Function cannot have fewer than 0 arguments.");
		InvalidValueError(info,__LINE__,__FILE__);
	}

	free(info);

	func->num_arguments=num_arguments;
}

void func_assign_num_returns(struct Function_Data * func,
		int num_returns) {
	char * info = malloc(sizeof(char)*1024);

	if (num_returns < 0) {
		sprintf(info,"Function cannot have fewer than 0 returns.");
		InvalidValueError(info,__LINE__,__FILE__);
	}

	free(info);
	func->num_returns=num_returns;
}

void func_assign_start_line(struct Function_Data * func,
		int start_line) {

	char * info = malloc(sizeof(char)*1024);

	if (start_line < 0) {
		sprintf(info,"Function start line %d invalid.",start_line);
		InvalidValueError(info,__LINE__,__FILE__);
	}

	free(info);
	func->start_line=start_line;
}

void func_assign_end_line(struct Function_Data * func,
		int end_line) {

	char * info = malloc(sizeof(char)*1024);

	if (end_line < 0) {
		sprintf(info,"Function end line %d invalid.",end_line);
		InvalidValueError(info,__LINE__,__FILE__);
	}

	free(info);
	func->end_line=end_line;
}

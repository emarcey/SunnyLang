/*
 * ControlVariable.c
 *
 *  Created on: May 14, 2018
 *      Author: evan.marcey
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "../Exceptions.h"

struct ControlVariable {
	char * type;
	int status;
	int start_line_number;
	int end_line_number;
};

struct ControlVariable * create_control_variable(char * type, int status, int start_line_number, int end_line_number) {
	struct ControlVariable * cv = malloc(sizeof(struct ControlVariable *));

	if (strcmp(type,"if")==0 || strcmp(type,"for")==0 || strcmp(type,"while")==0)
		cv->type = type;
	else {
		char * info = malloc(sizeof(char)*2014);
		sprintf(info,"control variable does not accept type %s.",type);
		InvalidValueError(info,__LINE__,__FILE__);
	}

	if (status < 0 || status > 2) {
		char * info = malloc(sizeof(char)*2014);
		sprintf(info,"control variable does not accept status value of %d.",status);
		InvalidValueError(info,__LINE__,__FILE__);
	}
	cv->status = status;

	if (strcmp(type,"if")==0 && (start_line_number >= 0 || end_line_number >=0)) {
		char * info = malloc(sizeof(char)*2014);
		sprintf(info,"If control variable does not accept line numbers.");
		InvalidValueError(info,__LINE__,__FILE__);
	} else {
		cv->start_line_number = start_line_number;
		cv->end_line_number = end_line_number;
	}
	return cv;
}

char * get_control_variable_type(struct ControlVariable * cv) {
	return cv->type;
}

int get_control_variable_status(struct ControlVariable * cv) {
	return cv->status;
}

int get_control_variable_start_line_number(struct ControlVariable * cv) {
	return cv->start_line_number;
}

int get_control_variable_end_line_number(struct ControlVariable * cv) {
	return cv->end_line_number;
}

void assign_control_variable_type(struct ControlVariable * cv,char * type) {
	if (strcmp(type,"if")==0 || strcmp(type,"for")==0 || strcmp(type,"while")==0)
			cv->type = type;
	else {
		char * info = malloc(sizeof(char)*2014);
		sprintf(info,"control variable does not accept type %s.",type);
	}

}

void assign_control_variable_status(struct ControlVariable * cv, int status) {
	if (status < 0 || status > 2) {
		char * info = malloc(sizeof(char)*2014);
		sprintf(info,"control variable does not accept status value of %d.",status);
		InvalidValueError(info,__LINE__,__FILE__);
	}
	cv->status = status;
}

void assign_control_variable_start_line_number(struct ControlVariable * cv, int start_line_number) {
	if (strcmp(cv->type,"if")==0) {
		char * info = malloc(sizeof(char)*2014);
		sprintf(info,"If control variable does not accept line numbers.");
		InvalidValueError(info,__LINE__,__FILE__);
	} else if (start_line_number < 0) {
		char * info = malloc(sizeof(char)*2014);
		sprintf(info,"Start line number cannot be less than 0.");
		InvalidValueError(info,__LINE__,__FILE__);
	} else {
		cv->start_line_number = start_line_number;
	}
}

void assign_control_variable_end_line_number(struct ControlVariable * cv, int end_line_number) {
	if (strcmp(cv->type,"if")==0) {
		char * info = malloc(sizeof(char)*2014);
		sprintf(info,"If control variable does not accept line numbers.");
		InvalidValueError(info,__LINE__,__FILE__);
	} else if (end_line_number < 0) {
		char * info = malloc(sizeof(char)*2014);
		sprintf(info,"End line number cannot be less than 0.");
		InvalidValueError(info,__LINE__,__FILE__);
	} else if (end_line_number < cv->start_line_number) {
		char * info = malloc(sizeof(char)*2014);
		sprintf(info,"End line number cannot be less than start line number.");
		InvalidValueError(info,__LINE__,__FILE__);
	} else {
		cv->end_line_number = end_line_number;
	}
}

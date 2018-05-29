/*
 * Variable.c
 *
 *  Created on: May 4, 2018
 *      Author: evan.marcey
 */



#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "../Exceptions.h"

#include "../utils/String_Utils.h"

struct Variable {
	char * type;
	char * name;
	unsigned int name_hash;
	int line_number;

	union {
		int ival;
		float fval;
		char* cval;
	} uval;

};

void assign_line_number(struct Variable * variable, int line_number) {
	if (strcmp(variable->type,"control") == 0 || strcmp(variable->name,"if")!= 0) {
		variable->line_number = line_number;
	} else {
			char * info = malloc(sizeof(char)*1024);
			sprintf("Line number not applicable for %s type variable %s.",variable->type,variable->name);
			InvalidValueError(info,__LINE__,__FILE__);
		}
}

struct Variable* create_variable(char * type,
		char * name,
		int ival,
		float fval,
		char * cval,
		int line_number) {
	struct Variable* variable = (struct Variable*) malloc(sizeof(struct Variable));

	variable->type = type;
	variable->name = name;
	variable->name_hash = hash(name);

	if (strcmp(type,"int")==0) { //if int
		variable->uval.ival = ival;
	} else if (strcmp(type,"boolean")==0) { //if boolean
		if (ival == 0 || ival == 1) {
			variable->uval.ival = ival;
		} else {
			char * info = malloc(sizeof(char)*2014);
			sprintf(info,"Value of %d not applicable for data type boolean",ival);
		}
	} else if (strcmp(type,"float")==0) {
		variable->uval.fval = fval;
	} else if (strcmp(type,"string")==0) {
		variable->uval.cval = cval;
	} else if (strcmp(type,"control")==0) {
		variable->uval.ival = ival;
	} else if (strcmp(type,"function")==0) {
		variable->uval.ival = ival;
	} else {
		TypeNotRecognizedError(type,name,"variable",__LINE__,__FILE__);
	}

	if (line_number > 0) assign_line_number(variable, line_number);

	return variable;
}

char * get_variable_type(struct Variable * variable) {
	return variable->type;
}

char * get_variable_name(struct Variable * variable) {
	return variable->name;
}

unsigned int get_variable_hash(struct Variable * variable) {
	return variable->name_hash;
}

int get_variable_ival(struct Variable * variable) {
	return variable->uval.ival;
}

float get_variable_fval(struct Variable * variable) {
	return variable->uval.fval;
}

char * get_variable_cval(struct Variable * variable) {
	return variable->uval.cval;
}

int get_variable_line_number(struct Variable * variable) {
	return variable->line_number;
}

int get_variable_val_as_int_condition(struct Variable * variable) {
	double tmp_result_double = 0;
	int tmp_result_int = 0;
	if (strcmp(get_variable_type(variable),"float")==0) {
		tmp_result_double = get_variable_fval(variable);
		tmp_result_int = tmp_result_double;
		if (tmp_result_double != 0 && tmp_result_double != 1) {
			char * info = malloc(sizeof(char)*1024);
			sprintf(info,"%f,",tmp_result_double);
			InvalidConditionValueError(info,__LINE__,__FILE__);
		}
	} else if (strcmp(get_variable_type(variable),"int")==0 ||
			strcmp(get_variable_type(variable),"boolean")==0 ||
			strcmp(get_variable_type(variable),"control")==0 ||
			strcmp(get_variable_type(variable),"function")==0) {
				tmp_result_int = get_variable_ival(variable);
	} else {
		char * info = malloc(sizeof(char)*1024);
		sprintf(info,"Variable type of %s not valid for a condition evaluation.",get_variable_type(variable));
		InvalidValueError(info,__LINE__,__FILE__);
	}

	if (tmp_result_int != 0 && tmp_result_int != 1) {
		char * info = malloc(sizeof(char)*1024);
		sprintf(info,"%d",tmp_result_int);
		InvalidConditionValueError(info,__LINE__,__FILE__);
	}
	return tmp_result_int;
}
char * return_variable_value_as_char(struct Variable * variable) {
	char * return_val = malloc(sizeof(char)*1024);
	if (strcmp(variable->type,"string")==0)
		return_val = variable->uval.cval;
	else if (strcmp(variable->type,"string")==0)
		sprintf(return_val,"%f",variable->uval.fval);
	else if (strcmp(variable->type,"int")==0 ||
			strcmp(variable->type,"boolean")==0 ||
			strcmp(variable->type,"control")==0 ||
			strcmp(get_variable_type(variable),"function")==0)
		sprintf(return_val,"%d",variable->uval.ival);

	return return_val;
}

void assign_variable_value(struct Variable * variable, int ival, float fval, char * cval) {
	if ((strcmp(variable->type,"int") ==0 ||
			strcmp(variable->type,"boolean")==0) ||
			strcmp(variable->type,"control")==0 ||
			strcmp(get_variable_type(variable),"function")==0) {
		variable->uval.ival = ival;
	} else if (strcmp(variable->type,"float")==0) {
		variable->uval.fval = fval;
	} else if (strcmp(variable->type,"string")==0) {
		variable->uval.cval = cval;
	}
}

int variable_index(struct Variable** variables, int variable_count, unsigned int s_variable_hash) {
	for (int i = 0; i < variable_count; i++) {
		if (get_variable_hash(variables[i])==s_variable_hash)
			return i;
	}

	return -1;
}

int variable_types_compatible(char * type1, char * type2) {

	if (strcmp(type1,"string")==0 && strcmp(type2,"string")==0) {
		return 1;
	} else if (strcmp(type1,"control")==0 ||
			strcmp(type1,"function")==0 ||
			strcmp(type2,"control")==0 ||
			strcmp(type2,"function")==0) {
		return 0;
	} else if (strcmp(type1,"string")!=0 && (strcmp(type2,"string")!=0)) {
		return 1;
	}
	return 0;
}

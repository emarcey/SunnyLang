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

	union {
		int ival;
		float fval;
		char* cval;
	} uval;

};

struct Variable* create_variable(char * type,
		char * name,
		int ival,
		float fval,
		char * cval) {
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
	} else {
		TypeNotRecognizedError(type,name,"variable");
	}

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

void assign_variable_value(struct Variable * variable, int ival, float fval, char * cval) {
	if ((strcmp(variable->type,"int")==0 || strcmp(variable->type,"boolean")==0)) {
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
	} else if (strcmp(type1,"string")!=0 && (strcmp(type2,"string")!=0)) {
		return 1;
	}
	return 0;
}

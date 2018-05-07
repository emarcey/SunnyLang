/*
 * Variable.h
 *
 *  Created on: May 4, 2018
 *      Author: evan.marcey
 */

#ifndef STRUCT_VARIABLE_H_
#define STRUCT_VARIABLE_H_

struct Variable;

struct Variable* create_variable(char * type,char * name,int ival,float fval,char * cval);

char * get_variable_type(struct Variable * variable);

char * get_variable_name(struct Variable * variable);

unsigned int get_variable_hash(struct Variable * variable);

int get_variable_ival(struct Variable * variable);

double get_variable_fval(struct Variable * variable);

char * get_variable_cval(struct Variable * variable);

int variable_index(struct Variable** variables, int variable_count, unsigned int s_variable_hash);

#endif /* STRUCT_VARIABLE_H_ */

/*
 * Variable.h
 *
 *  Created on: May 4, 2018
 *      Author: evan.marcey
 */

//Definition for Variable structure & associated functions
#ifndef STRUCT_VARIABLE_H_
#define STRUCT_VARIABLE_H_

//Variable structure
struct Variable;

//Function assigns line number to variable if correct type
void assign_line_number(struct Variable * variable, int line_number);

/*
 * create_variable:
 *  - Create a Variable with given input
 *
 * params:
 * 	- type: currently accepted types: int, string, boolean, float
 * 	- name: name of Variable, must be alphanumeric (or '_') and cannot start with a number
 * 	- ival: if type is boolean or int, this receives the value
 * 	- fval: if type is float, this receives the value
 * 	- cval: if type is string, this receives the value
 *
 * returns:
 *  - pointer directed at Variable that was created
 */
struct Variable* create_variable(char * type,char * name,int ival,float fval,char * cval,int line_number);

//Function returns variable type
char * get_variable_type(struct Variable * variable);

//Function returns variable name
char * get_variable_name(struct Variable * variable);

//Function returns variable hash value
unsigned int get_variable_hash(struct Variable * variable);

//Function returns variable ival
int get_variable_ival(struct Variable * variable);

//Function returns variable fval
float get_variable_fval(struct Variable * variable);

//Function returns variable cval
char * get_variable_cval(struct Variable * variable);

int get_variable_val_as_int_condition(struct Variable * variable);

//Function return variable line_number
int get_variable_line_number(struct Variable * variable);

//Function returns variable value as char *, converting based on type
char * return_variable_value_as_char(struct Variable * variable);

//Function assigns a value to a variable based on type
void assign_variable_value(struct Variable * variable, int ival, float fval, char * cval);

/*
 * variable_index:
 *  - loops through a list of variables, returns index of variable with matching name
 *  - if not present, returns -1
 *
 * params:
 * 	- variables: list of Variable objects to loop through
 * 	- variable_count: number of objects in variables
 * 	- s_variable_hash: hash value of the name of the search variable to compare
 *
 * returns:
 *  - index of variable in variables, or -1
 */
int variable_index(struct Variable** variables, int variable_count, unsigned int s_variable_hash);

/*
 * variable_types_compatible:
 * 	- Determines if two variables have types that can be compared (i.e. float and int vs float and string)
 *
 * params:
 * 	- type1: type of first variable
 * 	- type2: type of second variable
 *
 * returns:
 *  - 1 if compatible, 0 if not
 */
int variable_types_compatible(char * type1, char * type2);

#endif /* STRUCT_VARIABLE_H_ */

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

/*
 * 	assign_line_number:
 * 		- helper function to update a Variable's line_number
 *
 * 	params:
 * 		- variable: Variable to update
 * 		- line_number: new value for line_number
 */
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
struct Variable* create_variable(char * type,char * name,int ival,float fval,char * cval,int line_number, int depth);

struct Variable * create_variable_func(char * type,
		char * name,
		int line_number,
		int depth,
		int num_arguments,
		int num_returns,
		int start_line,
		int end_line);

/*
 * 	get_variable_type:
 * 		- helper function to return a Variable's type
 *
 * 	params:
 * 		- variable: Variable to get
 *
 * 	return:
 * 		- char* value of variable type
 */
char * get_variable_type(struct Variable * variable);

/*
 * 	get_variable_name:
 * 		- helper function to return a Variable's name
 *
 * 	params:
 * 		- variable: Variable to get
 *
 * 	return:
 * 		- char* value of variable name
 */
char * get_variable_name(struct Variable * variable);

/*
 * 	get_variable_hash:
 * 		- helper function to return hash of Variable's name
 *
 * 	params:
 * 		- variable: Variable to get
 *
 * 	return:
 * 		- unsigned int value of variable hash
 */
unsigned int get_variable_hash(struct Variable * variable);

/*
 * 	get_variable_ival:
 * 		- helper function to return Variable's ival
 * 		- DOES NOT CHECK FOR CORRECT VARIABLE TYPE
 *
 * 	params:
 * 		- variable: Variable to get
 *
 * 	return:
 * 		- int value of variable ival
 */
int get_variable_ival(struct Variable * variable);

/*
 * 	get_variable_fval:
 * 		- helper function to return Variable's fval
 * 		- DOES NOT CHECK FOR CORRECT VARIABLE TYPE
 *
 * 	params:
 * 		- variable: Variable to get
 *
 * 	return:
 * 		- double value of variable fval
 */
float get_variable_fval(struct Variable * variable);

/*
 * 	get_variable_cval:
 * 		- helper function to return Variable's cval
 * 		- DOES NOT CHECK FOR CORRECT VARIABLE TYPE
 *
 * 	params:
 * 		- variable: Variable to get
 *
 * 	return:
 * 		- char* value of variable cval
 */
char * get_variable_cval(struct Variable * variable);

/*
 * 	get_variable_val_as_int_condition:
 * 		- helper function to return Variable's ival or fval as int, depending on type
 *
 * 	params:
 * 		- variable: Variable to get
 *
 * 	return:
 * 		- int value of ival or fval
 */
int get_variable_val_as_int_condition(struct Variable * variable);

/*
 * 	get_variable_line_number:
 * 		- helper function to return Variable's line_number
 *
 * 	params:
 * 		- variable: Variable to get
 *
 * 	return:
 * 		- int value of variable line_number
 */
int get_variable_line_number(struct Variable * variable);

/*
 * 	get_variable_depth:
 * 		- helper function to return Variable's depth
 *
 * 	params:
 * 		- variable: Variable to get
 *
 * 	return:
 * 		- int value of variable depth
 */
int get_variable_depth(struct Variable * variable);

/*
 * 	return_variable_value_as_char:
 * 		- helper function to return Variable's value as a char
 *
 * 	params:
 * 		- variable: Variable to get
 *
 * 	return:
 * 		- char* value of variable ival, fval or cval
 */
char * return_variable_value_as_char(struct Variable * variable);

/*
 * 	get_variable_func_num_arguments:
 * 		- helper function to return Variable's num_arguments if function
 *
 * 	params:
 * 		- variable: Variable to get
 *
 * 	return:
 * 		- int value of variable num_arguments
 */
int get_variable_func_num_arguments(struct Variable * variable);

/*
 * 	get_variable_func_num_returns:
 * 		- helper function to return Variable's num_returns if function
 *
 * 	params:
 * 		- variable: Variable to get
 *
 * 	return:
 * 		- int value of variable num_returns
 */
int get_variable_func_num_returns(struct Variable * variable);

/*
 * 	get_variable_func_start_line:
 * 		- helper function to return Variable's start_line if function
 *
 * 	params:
 * 		- variable: Variable to get
 *
 * 	return:
 * 		- int value of variable start_line
 */
int get_variable_func_start_line(struct Variable * variable);

/*
 * 	get_variable_func_end_line:
 * 		- helper function to return Variable's end_line if function
 *
 * 	params:
 * 		- variable: Variable to get
 *
 * 	return:
 * 		- int value of variable end_line
 */
int get_variable_func_end_line(struct Variable * variable);

/*
 * 	assign_variable_value:
 * 		- helper function to update a Variable's value
 *
 * 	params:
 * 		- variable: Variable to update
 * 		- ival: new value if int or boolean
 * 		- fval: new value if float
 * 		- cval: new value if string
 */
void assign_variable_value(struct Variable * variable, int ival, float fval, char * cval);

/*
 * 	assign_variable_depth:
 * 		- helper function to update a Variable's depth
 *
 * 	params:
 * 		- variable: Variable to update
 * 		- depth: new value for depth
 */
void assign_variable_depth(struct Variable * variable, int depth);

/*
 * 	assign_variable_func_num_arguments:
 * 		- helper function to update a Variable's num_arguments if function type
 *
 * 	params:
 * 		- variable: Variable to update
 * 		- num_arguments: new value for num_arguments
 */
void assign_variable_func_num_arguments(struct Variable * variable, int num_arguments);

/*
 * 	assign_variable_func_num_returns:
 * 		- helper function to update a Variable's num_returns if function type
 *
 * 	params:
 * 		- variable: Variable to update
 * 		- num_returns: new value for num_returns
 */
void assign_variable_func_num_returns(struct Variable * variable, int num_returns);

/*
 * 	assign_variable_func_start_line:
 * 		- helper function to update a Variable's start_line if function type
 *
 * 	params:
 * 		- variable: Variable to update
 * 		- start_line: new value for start_line
 */
void assign_variable_func_start_line(struct Variable * variable, int start_line);

/*
 * 	assign_variable_func_end_line:
 * 		- helper function to update a Variable's end_line if function type
 *
 * 	params:
 * 		- variable: Variable to update
 * 		- end_line: new value for end_line
 */
void assign_variable_func_end_line(struct Variable * variable, int end_line);

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

/*
 * 	variable_is_numeric:
 * 		- checks if variable is of a numeric type (int, float, boolean)
 *
 * 	params:
 * 		- variable: Variable to check
 *
 * 	returns:
 * 		- 1 if true, otherwise 0
 */
int variable_is_numeric(struct Variable * variable);

#endif /* STRUCT_VARIABLE_H_ */

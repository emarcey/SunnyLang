/*
 * Function_Data.h
 *
 *  Created on: Jun 4, 2018
 *      Author: evan.marcey
 */

#ifndef STRUCT_FUNCTION_DATA_H_
#define STRUCT_FUNCTION_DATA_H_

// Declare a structure to store data necessary for a function variable
struct Function_Data;

/*
 *  create_function_data:
 *  	- allocates a Function_Data variable, assigns values and returns
 *
 *  Params:
 *  	- num_arguments: value for number of arguments function takes
 *  	- num_returns: value for number of return values function takes
 *  	- start_line: line where declare statement can be found in source script
 *  	- end_line: line where end declare statement can be found in source script
 *
 * 	Returns:
 *
 */
struct Function_Data * create_function_data(int num_arguments,
	int num_returns,
	int start_line,
	int end_line);

/*
 * 	func_get_num_arguments:
 * 		- helper method to return num_arguments for Function_Data struct
 *
 * 	params:
 * 		- func: Function_Data to call
 *
 * 	returns:
 * 		- num_arguments value for func
 */
int func_get_num_arguments(struct Function_Data * func);

/*
 * 	func_get_num_returns:
 * 		- helper method to return num_returns for Function_Data struct
 *
 * 	params:
 * 		- func: Function_Data to call
 *
 * 	returns:
 * 		- returns value for func
 */
int func_get_num_returns(struct Function_Data * func);

/*
 * 	func_get_start_line:
 * 		- helper method to return start_line for Function_Data struct
 *
 * 	params:
 * 		- func: Function_Data to call
 *
 * 	returns:
 * 		- returns value for func
 */
int func_get_start_line(struct Function_Data * func);

/*
 * 	func_get_end_line:
 * 		- helper method to return end_line for Function_Data struct
 *
 * 	params:
 * 		- func: Function_Data to call
 *
 * 	returns:
 * 		- returns value for func
 */
int func_get_end_line(struct Function_Data * func);

/*
 * 	func_assign_num_arguments:
 * 		- helper function to assign new value to num_arguments for a Function_Data object
 *
 * 	params:
 * 		- func: Function_Data you want to update
 * 		- num_arguments: new value for num_arguments
 */
void func_assign_num_arguments(struct Function_Data * func,
		int num_arguments);

/*
 * 	func_assign_num_returns:
 * 		- helper function to assign new value to num_returns for a Function_Data object
 *
 * 	params:
 * 		- func: Function_Data you want to update
 * 		- num_returns: new value for num_returns
 */
void func_assign_num_returns(struct Function_Data * func,
		int num_returns);

/*
 * 	func_assign_start_line:
 * 		- helper function to assign new value to start_line for a Function_Data object
 *
 * 	params:
 * 		- func: Function_Data you want to update
 * 		- start_line: new value for start_line
 */
void func_assign_start_line(struct Function_Data * func,
		int start_line);

/*
 * 	func_assign_end_line:
 * 		- helper function to assign new value to end_line for a Function_Data object
 *
 * 	params:
 * 		- func: Function_Data you want to update
 * 		- end_line: new value for end_line
 */
void func_assign_end_line(struct Function_Data * func,
		int end_line);

#endif /* STRUCT_FUNCTION_DATA_H_ */

/*
 * Function_Data.h
 *
 *  Created on: Jun 4, 2018
 *      Author: evan.marcey
 */

#ifndef STRUCT_FUNCTION_DATA_H_
#define STRUCT_FUNCTION_DATA_H_

struct Function_Data;

struct Function_Data * create_function_data(int num_arguments,
	int num_returns,
	int start_line,
	int end_line);

int func_get_num_arguments(struct Function_Data * func);

int func_get_num_returns(struct Function_Data * func);

int func_get_start_line(struct Function_Data * func);

int func_get_end_line(struct Function_Data * func);

void func_assign_num_arguments(struct Function_Data * func,
		int num_arguments);

void func_assign_num_returns(struct Function_Data * func,
		int num_returns);

void func_assign_start_line(struct Function_Data * func,
		int start_line);

void func_assign_end_line(struct Function_Data * func,
		int end_line);

#endif /* STRUCT_FUNCTION_DATA_H_ */

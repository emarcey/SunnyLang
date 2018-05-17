/*
 * ControlVariable.h
 *
 *  Created on: May 14, 2018
 *      Author: evan.marcey
 */

#ifndef STRUCT_CONTROLVARIABLE_H_
#define STRUCT_CONTROLVARIABLE_H_

struct ControlVariable;

struct ControlVariable * create_control_variable(char * type, int status, int start_line_number, int end_line_number);

char * get_control_variable_type(struct ControlVariable * cv);

int get_control_variable_status(struct ControlVariable * cv);

int get_control_variable_start_line_number(struct ControlVariable * cv);

int get_control_variable_end_line_number(struct ControlVariable * cv);

void assign_control_variable_type(struct ControlVariable * cv,char * type);

void assign_control_variable_status(struct ControlVariable * cv, int status);

void assign_control_variable_start_line_number(struct ControlVariable * cv, int start_line_number);

void assign_control_variable_end_line_number(struct ControlVariable * cv, int end_line_number);


#endif /* STRUCT_CONTROLVARIABLE_H_ */

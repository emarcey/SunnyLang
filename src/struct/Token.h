/*
 * Token.h
 *
 *  Created on: May 4, 2018
 *      Author: evan.marcey
 */

#ifndef STRUCT_TOKEN_H_
#define STRUCT_TOKEN_H_

struct Token;

struct Token * create_token(char token_type,char * token_value);

void assign_token_value(struct Token * token, char * new_value);

void append_token_value(struct Token * token, char * new_value);

void assign_token_type(struct Token * token, char new_type);

char get_token_type(struct Token * token);

char * get_token_value(struct Token * token);

unsigned int get_token_hash(struct Token * token);

int get_token_precedence(struct Token * token);

#endif /* STRUCT_TOKEN_H_ */

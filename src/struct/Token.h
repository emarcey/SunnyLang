/*
 * Token.h
 *
 *  Created on: May 4, 2018
 *      Author: evan.marcey
 */

#ifndef STRUCT_TOKEN_H_
#define STRUCT_TOKEN_H_

//implements structure to store data for a Token
struct Token;

//Function to create a token
struct Token * create_token(char token_type,char * token_value);

//Function to set a token's value; updates hash and precedence
void assign_token_value(struct Token * token, char * new_value);

//Function to append a string to the end of a token's value; updates hash and precedence
void append_token_value(struct Token * token, char * new_value);

//Function to assign a type to a token
void assign_token_type(struct Token * token, char new_type);

//Function returns a token's type
char get_token_type(struct Token * token);

//Function returns a token's value
char * get_token_value(struct Token * token);

//Function returns a token's hash value
unsigned int get_token_hash(struct Token * token);

//Function returns a token's precedence
int get_token_precedence(struct Token * token);

#endif /* STRUCT_TOKEN_H_ */

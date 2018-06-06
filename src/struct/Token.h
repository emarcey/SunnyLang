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

/*
 * 	create_token:
 * 		- creates a new Token struct
 *
 * 	params:
 * 		- token_type: type of new token
 * 		- token_value: value of new token
 *
 * 	returns:
 * 		- newly created Token
 *
 */
struct Token * create_token(char token_type,char * token_value);

/*
 * 	assign_token_value:
 * 		- helper function to replace token value
 *
 * 	params:
 * 		- token: Token to update
 * 		- new_value: new value for token_value
 *
 */
void assign_token_value(struct Token * token, char * new_value);

/*
 * 	append_token_value:
 * 		- helper function to append new string to token value
 *
 * 	params:
 * 		- token: Token to update
 * 		- new_value: value to append to token_value
 *
 */
void append_token_value(struct Token * token, char * new_value);

/*
 * 	assign_token_type:
 * 		- helper function to replace token type
 *
 * 	params:
 * 		- token: Token to update
 * 		- new_type: new value for token_type
 *
 */
void assign_token_type(struct Token * token, char new_type);

/*
 * 	get_token_type:
 * 		- helper function to get a Token's type
 *
 * 	params:
 * 		- token: Token to get type from
 *
 * 	returns:
 * 		- char value of token_type
 */
char get_token_type(struct Token * token);

/*
 * 	get_token_value:
 * 		- helper function to get a Token's value
 *
 * 	params:
 * 		- token: Token to get value from
 *
 * 	returns:
 * 		- char* value of token_value
 */
char * get_token_value(struct Token * token);

/*
 * 	get_token_hash:
 * 		- helper function to get hash of Token's value
 *
 * 	params:
 * 		- token: Token to get hash from
 *
 * 	returns:
 * 		- unsigned int value of token_hash
 */
unsigned int get_token_hash(struct Token * token);

/*
 * 	get_token_precedence:
 * 		- helper function to get hash of Token's precedence
 *
 * 	params:
 * 		- token: Token to get precedence from
 *
 * 	returns:
 * 		- int value of token_precedence
 */
int get_token_precedence(struct Token * token);

#endif /* STRUCT_TOKEN_H_ */

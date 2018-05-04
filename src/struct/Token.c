/*
 * Token.c
 *
 *  Created on: May 4, 2018
 *      Author: evan.marcey
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "../utils/String_Utils.h"
#include "../utils/Math_Utils.h"

struct Token {
	char token_type;
	char * token_value;
	unsigned int token_hash;
	int token_precedence;
};

struct Token * create_token(char token_type,
		char * token_value) {
	struct Token* token = (struct Token*) malloc(sizeof(struct Token));
	token->token_type=token_type;
	token->token_value=token_value;
	token->token_hash=hash(token_value);
	token->token_precedence=get_precedence(token->token_hash);

	return token;
}

void assign_token_value(struct Token * token, char * new_value) {
	token->token_value = new_value;
	token->token_hash=hash(token->token_value);
	token->token_precedence=get_precedence(token->token_hash);
}

void append_token_value(struct Token * token, char * new_value) {
	char * tmp = malloc(sizeof(token->token_value)+sizeof(char)*(strlen(new_value)+2));
	sprintf(tmp,"%s %s",token->token_value,new_value);
	strcpy(token->token_value,tmp);
	token->token_hash=hash(token->token_value);
	token->token_precedence=get_precedence(token->token_hash);
}

void assign_token_type(struct Token * token, char new_type) {
	token->token_type=new_type;
}

char get_token_type(struct Token * token) {
	return token->token_type;
}

char * get_token_value(struct Token * token) {
	return token->token_value;
}

unsigned int get_token_hash(struct Token * token) {
	return token->token_hash;
}

int get_token_precedence(struct Token * token) {
	return token->token_precedence;
}

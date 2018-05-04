/*
 * Token.c
 *
 *  Created on: May 4, 2018
 *      Author: evan.marcey
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


struct Token {
	char token_type;
	char * token_name;
	unsigned int token_hash;
	int token_precedence;
	char * token_value;
};

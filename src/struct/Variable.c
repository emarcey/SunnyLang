/*
 * Variable.c
 *
 *  Created on: May 4, 2018
 *      Author: evan.marcey
 */



#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Variable {
	char type;
	char * name;
	int name_hash;

};

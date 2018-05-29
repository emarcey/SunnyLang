/*
 * Misc_Utils.c
 *
 *  Created on: May 8, 2018
 *      Author: evan.marcey
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../struct/Variable.h"

int element_in_list_int(int * list, int list_len, double e) {
	for (int i = 0; i < list_len; i++) {
		if (list[i]==e) return 1;
	}
	return 0;
}

int element_in_list_variable(struct Variable ** list, int list_len, char * e) {
	for (int i = 0; i < list_len; i++) {
		if (strcmp(get_variable_name(list[i]),e)==0) {
			return i;
		}
	}
	return 0;
}

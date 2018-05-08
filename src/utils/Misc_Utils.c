/*
 * Misc_Utils.c
 *
 *  Created on: May 8, 2018
 *      Author: evan.marcey
 */

#include <stdio.h>
#include <stdlib.h>

int element_in_list_int(int * list, int list_len, double e) {
	for (int i = 0; i < list_len; i++) {
		if (list[i]==e) return 1;
	}
	return 0;
}

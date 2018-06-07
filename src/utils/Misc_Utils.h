/*
 * Misc_Utils.h
 *
 *  Created on: May 8, 2018
 *      Author: evan.marcey
 */
#include "../struct/Variable.h"

#ifndef UTILS_MISC_UTILS_H_
#define UTILS_MISC_UTILS_H_

/*
 * 	element_in_list_int:
 * 		- iterates through a list of ints to determine if value is in list
 *
 * 	params:
 * 		- list: list of ints to check
 * 		- list_len: length of list
 * 		- e: value to search for
 *
 * 	returns:
 * 		- 1 if element is in list, otherwise 0
 *
 */
int element_in_list_int(int * list, int list_len, double e);

#endif /* UTILS_MISC_UTILS_H_ */

/*
 * String_Methods.h
 *
 *  Created on: Apr 19, 2018
 *      Author: evan.marcey
 */

#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

/*
 * count_chars:
 *  - count frequency of a character within a phrase
 *
 * params:
 * 	- phrase: phrase to search
 * 	- c_find: character for which to search
 *
 * returns:
 *  - number of instances of c_find in phrase
 */
int count_chars(char * phrase, char c_find);

/*
 * next_char_ind:
 *  - locates first occurrence of a character within a phrase
 *
 * params:
 * 	- phrase: phrase to search
 * 	- c_find: character for which to search
 *
 * returns:
 * 	- index of first instance of c_find in phrase, or -1 if not found
 */
int next_char_ind(char * phrase, char c_find);

/*
 * is_number:
 *  - determines if a string contains a number (includes decimals and negatives)
 *
 * params:
 *  - s: string input to check
 *
 * returns:
 *  - 1 if s is a number, otherwise 0
 */
int is_number(char * s);

unsigned int hash (const char* word);

#endif /* STRING_UTILS_H_ */

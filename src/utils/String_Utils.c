/*
 * String_Methods.c
 *
 *  Created on: Apr 19, 2018
 *      Author: evan.marcey
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//counts the number of a given character in a phrase
int count_chars(char * phrase, char c_find) {
	int char_count = 0;

	for (int i = 0; i < strlen(phrase); i++) {
		if (phrase[i]==c_find) char_count++;
	}

	return char_count;
}

//finds the next index of a given character in a phrase
//returns -1 if not found
int next_char_ind(char * phrase, char c_find) {
	for (int i = 0; i < strlen(phrase); i++) {
		if (phrase[i]==c_find) return i;
	}
	return -1;
}

int is_number(char * s) {
	int start = 0;
	int dec_ct = 0;

	while(*s != '\0') {
		if (start == 0) {
			if (*s == 46) dec_ct++;
			else if (*s != 45 && (*s < 48 || *s > 57)) {
				return 0;
			}
			start = 1;
		}
		else {
			if (*s == 46) {
				dec_ct++;
			}
			else if (*s < 48 || *s > 57) {
				return 0;
			}
		}

		if (dec_ct > 1) return 0;
		s++;
	}

	return 1;
}

unsigned int hash (const char* word)
{
    unsigned int hash = 0;
    for (int i = 0 ; word[i] != '\0' ; i++)
    {
        hash = 31*hash + word[i];
    }
    return hash;
}

int is_alphanum(char * s) {
	while (*s != '\0') {
		if (*s < 48 ||
				(*s > 57 && *s < 65) ||
				(*s > 90 && *s < 95) ||
				(*s > 95 && *s < 97) ||
				*s > 122) {
			return 0;
		}
		s++;
	}
	return 1;
}

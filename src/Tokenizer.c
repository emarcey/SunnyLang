#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/File_Utils.h"
#include "utils/String_Utils.h"
#include "struct/Token.h"

int check_dictionary(char *** cmds,
		int cmd_rows,
		int cmd_fields,
		int chk_string_len,
		char * chk_string,
		int * dict_val) {

	int match_count = 0;
	int cmd_match = -1;

	//create temporary string from current token to use for comparisons
	char tmp_chk_string[chk_string_len+1];
	tmp_chk_string[chk_string_len] = '\0';
	strcpy(tmp_chk_string,chk_string);

	//for each value in the dictionary, determine if it matches the input string
	for (int i = 0; i < cmd_rows; i++) {
		char tmp_cmd[chk_string_len+1];
		strncpy(tmp_cmd,cmds[i][1],chk_string_len);
		tmp_cmd[chk_string_len] = '\0';

		if (strcmp(tmp_chk_string,tmp_cmd)==0) {
			match_count++;
			cmd_match = i;
		}

	}
	if (match_count == 1) *dict_val = cmd_match;
	return match_count;
}

char *** tokenize_line(char * line,
		int * num_tokens,
		char *** cmds,
		int cmd_rows,
		int cmd_fields) {

	int num_words = count_chars(line,' ')+1;
	char * words;
	char *** tokens = malloc(sizeof(char**)*num_words);
	for (int i = 0; i < num_words; i++) {
		tokens[i] = malloc(sizeof(char*)*2);
		tokens[i][0] = malloc(sizeof(char)*2);
		strcpy(tokens[i][0],"e");
	}

	int token_count = 0;
	words = strtok(line," ");

	while (words != NULL) {

		int is_num = is_number(words);
		//handling quoted string
		//start of quotation
		if (words[0]==34) {
			tokens[token_count][1] = malloc(sizeof(char)*(strlen(words)+1));
			//check to make sure token is empty
			if (tokens[token_count][0][0]==101) {
				tokens[token_count][0][0] = 115;

				strcpy(tokens[token_count][1],words);

				//check for the end of the string
				if (words[strlen(words)-1]==34) {
					token_count++;
				}

			} else {
				printf("%s\n",words);
				printf("Token already occupied. Something went wrong!\n");
				exit(EXIT_FAILURE);
			}
		}
		//printf("%d\n",tokens[token_count][0][0]);
		else if (tokens[token_count][0][0]==115) {

			char * tmp = malloc(sizeof(tokens[token_count][1])+sizeof(char)*(strlen(words)+2));
			sprintf(tmp,"%s %s",tokens[token_count][1],words);
			strcpy(tokens[token_count][1],tmp);

			//check for the end of the string
			if (words[strlen(words)-1]==34) {
				token_count++;
			}
		}

		//figure out if number
		//a number should start with a digit, a decimal, or a minus sign
		//and should contain at most 1 decimal
		else if (is_num==1) {
			if (tokens[token_count][0][0]==101) {
				tokens[token_count][1] = malloc(sizeof(char)*(strlen(words)+1));
				tokens[token_count][0][0] = 110;
				strcpy(tokens[token_count][1],words);
				token_count++;

			} else {
				printf("%s\n",words);
				printf("Token already occupied. Something went wrong!\n");
				exit(EXIT_FAILURE);
			}
		}
		else {
			//figure out if it belongs to a command
			int cmd_val = -1;
			int cmd_matches = check_dictionary(cmds,
					cmd_rows,
					cmd_fields,
					strlen(words),
					words,
					&cmd_val);

			if (cmd_matches == 1) {
				tokens[token_count][0][0] = cmds[cmd_val][2][0];
				tokens[token_count][1] = malloc(sizeof(char)*(strlen(cmds[cmd_val][0])+1));
				strcpy(tokens[token_count][1],cmds[cmd_val][0]);
			}
			//if not, it's a variable
			else {
				//but two variables back to back doesn't make sense
				if (token_count > 0 && tokens[token_count-1][0][0]==118) {
					printf("Two variables back to back? Who do you think you are?");
					exit(EXIT_FAILURE);
				}
				tokens[token_count][0][0] = 118;
				tokens[token_count][1] = malloc(sizeof(char)*(strlen(words)+1));
				strcpy(tokens[token_count][1],words);

			}

			token_count++;
		}

		words = strtok(NULL, " ");

	}
	*num_tokens = token_count;
	return tokens;
}

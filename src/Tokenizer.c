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

struct Token ** tokenize_line(char * line,
		int * num_tokens,
		char *** cmds,
		int cmd_rows,
		int cmd_fields) {

	int num_words = count_chars(line,' ')+1;
	char * words;
	struct Token ** tokens = malloc(sizeof(struct Token*)*num_words);
	for (int i = 0; i < num_words; i++) {
		tokens[i] = create_token('e',"");
	}

	int token_count = 0;
	words = strtok(line," ");

	while (words != NULL) {

		int is_num = is_number(words);
		//handling quoted string
		//start of quotation
		if (words[0]==34) {
			//check to make sure token is empty
			if (get_token_type(tokens[token_count])==101) {
				assign_token_type(tokens[token_count],115);

				assign_token_value(tokens[token_count],words);

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
		else if (get_token_type(tokens[token_count])==115) {

			append_token_value(tokens[token_count],words);

			//check for the end of the string
			if (words[strlen(words)-1]==34) {
				token_count++;
			}
		}

		//figure out if number
		//a number should start with a digit, a decimal, or a minus sign
		//and should contain at most 1 decimal
		else if (is_num==1) {
			if (get_token_type(tokens[token_count])==101) {

				assign_token_type(tokens[token_count],110);
				assign_token_value(tokens[token_count],words);
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
				assign_token_type(tokens[token_count],cmds[cmd_val][2][0]);
				assign_token_value(tokens[token_count],cmds[cmd_val][0]);
			}
			//if not, it's a variable
			else {
				//but two variables back to back doesn't make sense
				if (token_count > 0 && get_token_type(tokens[token_count-1])==118) {
					printf("Two variables back to back? Who do you think you are?");
					exit(EXIT_FAILURE);
				}
				assign_token_type(tokens[token_count],118);
				assign_token_value(tokens[token_count],words);

			}

			token_count++;
		}

		words = strtok(NULL, " ");

	}
	*num_tokens = token_count;
	return tokens;
}

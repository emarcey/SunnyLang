#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/File_Utils.h"
#include "utils/String_Utils.h"
#include "utils/Math_Utils.h"
#include "struct/Token.h"
#include "struct/Stack.h"
#include "struct/Variable.h"

#include "Exceptions.h"

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
				char * info = malloc(sizeof(char)*2014);
				sprintf(info,"Token already occupied. Something went wrong!\n");
				TokenizationError(words,info);
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
				char * info = malloc(sizeof(char)*2014);
				sprintf(info,"Token already occupied. Something went wrong!\n");
				TokenizationError(words,info);
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
					char * info = malloc(sizeof(char)*2014);
					sprintf(info,"Back-to-back variables found in expression.\n");
					TokenizationError(words,info);
				} else {
					assign_token_type(tokens[token_count],118);
					assign_token_value(tokens[token_count],words);
				}
			}

			token_count++;
		}

		words = strtok(NULL, " ");

	}
	*num_tokens = token_count;
	return tokens;
}

struct Variable ** eval_line(struct Token ** tokens, int num_tokens, struct Variable ** variables, int * num_variables) {
	int tmp_num_variables = *num_variables;
	if (get_token_hash(tokens[0])==1542341994) { //declare a new variable
		/*
		 * First, we're going to do a bunch of error handling
		 */
		if (num_tokens < 3) //if syntax is just not long enough to contain all necessary types
			SyntaxError("Not enough tokens for variable declaration");

		else if (tmp_num_variables > 0 &&
				variable_index(variables,tmp_num_variables,get_token_hash(tokens[1]))!=-1) //check if variable exists
			VariableAlreadyExistsError(get_token_value(tokens[1]));

		else if (is_alphanum(get_token_value(tokens[1]))==0) //invalid variable name
			InvalidVariableName(get_token_value(tokens[1]));

		else if (get_token_hash(tokens[2])!=104431 &&
				get_token_hash(tokens[2])!=97526364 &&
				get_token_hash(tokens[2])!=-891985903 &&
				get_token_hash(tokens[2])!=64711720) //if next command
			TypeNotRecognizedError(get_token_value(tokens[2]),get_token_value(tokens[1]),"variable");

		else if (num_tokens==3) { //instantiate a blank variable
			struct Variable * tmp_var = create_variable(get_token_value(tokens[2]),get_token_value(tokens[1]),0,0,"");
			variables[tmp_num_variables] = tmp_var;
			tmp_num_variables++;

		} else if (num_tokens == 4) //
			SyntaxError("Not enough tokens for variable declaration");

		else if (get_token_hash(tokens[3])!=-1408204561) //if we're missing an 'assign' command
			SyntaxError("Assign block missing.");

		else {
			double tmp_val = eval_infix(tokens,num_tokens,4,variables,tmp_num_variables);
			int tmp_int = 0;
			float tmp_f = 0;
			if (get_token_hash(tokens[2]) == 104431 || get_token_value(tokens[2]) == -891985903) {
				tmp_int = tmp_val;
			} else {
				tmp_f = tmp_val;
			}
			struct Variable * tmp_var = create_variable(get_token_value(tokens[2]),get_token_value(tokens[1]),tmp_int,tmp_f,"");
			variables[tmp_num_variables] = tmp_var;
			printf("tmp_val: %f\n",get_variable_fval(variables[tmp_num_variables]));
			tmp_num_variables++;
		}

	} else {
		double tmp = eval_infix(tokens,num_tokens,0,variables,tmp_num_variables);
		printf("%f\n",tmp);
	}
	*num_variables = tmp_num_variables;
	return variables;
}

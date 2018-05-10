/*
 * Tokenizer.h
 *
 *  Created on: May 2, 2018
 *      Author: evan.marcey
 */

#include "struct/Stack.h"
#include "struct/VariableStack.h"

#ifndef TOKENIZER_H_
#define TOKENIZER_H_

/*
 * check_commands:
 * 	- Checks the current string against the commands list
 *
 * params:
 * 	- cmds: array containing list of all commands, where each row is of the form [common definition, term to check]
 * 		- i.e. [print, BANG THE WAITRESS]
 * 	- cmd_rows: number of records in cmds
 * 	- cmd_fields: number of fields in cmds (should be 2)
 * 	- chk_string_len: length of chk_string
 * 	- chk_string: string to search for in the command list
 * 	- cmd_val: pointer that is set to row number in command list if 1 match is found
 *
 * returns:
 * 	- number of potential matches found
 */
int check_commands(char *** cmds,
		int cmd_rows,
		int cmd_fields,
		int chk_string_len,
		char * chk_string,
		int * cmd_val);

/*
 * tokenize_line:
 * 	- receives a line of commands and tokenizes them according to ref_Token
 *
 * params:
 * 	- line: string to tokenize
 * 	- num_tokens: pointer that is set to the number of tokens found
 *
 * returns:
 *  - array of tokens, where each row contains [type of token, token]
 */
struct Token ** tokenize_line(char * line,
		int * num_tokens,
		char *** cmds,
		int cmd_rows,
		int cmd_fields);

struct Variable ** eval_line(struct Token ** tokens,
		int num_tokens,
		struct Variable ** variables,
		int * num_variables,
		struct VariableStack * control_flow_stack,
		int * line_number);

#endif /* TOKENIZER_H_ */

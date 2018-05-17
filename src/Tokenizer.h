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

/*
 * validate_for_statement:
 * 	- checks a line of code (in token form) and determines if the code is valid or not, with the following results:
 * 		- throws an error if invalid
 * 		- returns 1 if valid and variable already exists
 * 		- returns 2 if valid, variable does not exist and default type to integer
 * 		- returns 3 if valid, variable does not exist and type is explicitly stated in the statement
 *
 * params:
 * 	- tokens: array of Token objects representing the for statement
 * 	- num_tokens: number of Token objects in tokens
 * 	- variables: array of Variable objects for current variables in the environment
 * 	- tmp_num_variables: number of Variable objects in variables
 * 	- control_flow_stack: VariableStack containing current control flow objects
 *
 *  - returns:
 *  	- one of three validation codes
 *
 */

int validate_for_statement(struct Token ** tokens,
		int num_tokens,
		struct Variable ** variables,
		int tmp_num_variables,
		struct VariableStack * control_flow_stack);

/*
 * eval_line:
 *  - evaluates and executes a tokenized line of SunnyLang code
 *
 * params:
 * - tokens: array of Token objects representing the for statement
 * - num_tokens: number of Token objects in tokens
 * - variables: array of Variable objects for current variables in the environment
 * - num_variables: number of Variable objects in variables
 * - control_flow_stack: VariableStack containing current control flow objects
 * - line_number: current line in SunnyLang code
 *
 * returns:
 *  - array of Variable objects representing the environment's current variables
 */
struct Variable ** eval_line(struct Token ** tokens,
		int num_tokens,
		struct Variable ** variables,
		int * num_variables,
		struct VariableStack * control_flow_stack,
		int * line_number);

#endif /* TOKENIZER_H_ */

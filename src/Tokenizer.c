#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/File_Utils.h"
#include "utils/String_Utils.h"
#include "utils/Math_Utils.h"
#include "utils/Misc_Utils.h"
#include "struct/Token.h"
#include "struct/Stack.h"
#include "struct/Variable.h"
#include "struct/VariableStack.h"

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

		if (strcmp(tmp_chk_string,cmds[i][1])==0) {
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
				TokenizationError(words,info,__LINE__,__FILE__);
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
				TokenizationError(words,info,__LINE__,__FILE__);
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
				/*
				if (token_count > 0 && get_token_type(tokens[token_count-1])==118) {
					char * info = malloc(sizeof(char)*2014);
					sprintf(info,"Back-to-back variables found in expression at token %s.\n",words);
					SyntaxError(info,__LINE__,__FILE__);
				} else {
				*/
				assign_token_type(tokens[token_count],118);
				assign_token_value(tokens[token_count],words);
				//}
			}

			token_count++;
		}

		words = strtok(NULL, " ");

	}
	*num_tokens = token_count;
	return tokens;
}

int validate_declare_variable_statement(struct Token ** tokens,
		int num_tokens,
		struct Variable ** variables,
		int tmp_num_variables) {
	int result_type = 0;

	if (num_tokens < 3) //if syntax is just not long enough to contain all necessary types
		SyntaxError("Not enough tokens for variable declaration",__LINE__,__FILE__);

	else if (tmp_num_variables > 0 &&
			variable_index(variables,tmp_num_variables,get_token_hash(tokens[1]))!=-1) //check if variable exists
		VariableAlreadyExistsError(get_token_value(tokens[1]),__LINE__,__FILE__);

	else if (is_alphanum(get_token_value(tokens[1]))==0) //invalid variable name
		InvalidVariableName(get_token_value(tokens[1]),__LINE__,__FILE__);

	else if (get_token_hash(tokens[2])!=104431 &&
			get_token_hash(tokens[2])!=97526364 &&
			get_token_hash(tokens[2])!=-891985903 &&
			get_token_hash(tokens[2])!=64711720) //if next command
		TypeNotRecognizedError(get_token_value(tokens[2]),get_token_value(tokens[1]),"variable",__LINE__,__FILE__);

	else if (num_tokens==3) { //if variable has no operator
		result_type = 1;

	} else if (num_tokens == 4) //
		SyntaxError("Not enough tokens for variable declaration",__LINE__,__FILE__);

	return result_type;
}

int validate_for_statement(struct Token ** tokens,
		int num_tokens,
		struct Variable ** variables,
		int tmp_num_variables,
		struct VariableStack * control_flow_stack) {
	int return_val = 0;
	int equalities[] = {1921,1983,60,62};
	int equalities_len = 4;

	if (num_tokens == 6 || num_tokens == 7) {

		// validate variable
		if (get_token_type(tokens[1])!='v') {
			char * info = malloc(sizeof(char)*1024);
			sprintf(info,"Unable to parse for statement. Expected variable as second token, but received token %s of type %d",
					get_token_value(tokens[1]),
					get_token_type(tokens[1]));
			SyntaxError(info,__LINE__,__FILE__);
		}
		else if (variable_index(variables,tmp_num_variables,get_token_hash(tokens[1])) == -1) { //variable does not exist
			if (num_tokens == 7) {
				if (get_token_type(tokens[2])!='d') {
					char * info = malloc(sizeof(char)*1024);
					sprintf(info,
							"Unable to parse for statement. Expected data type for new variable, but received token %s of type %d",
							get_token_value(tokens[2]),
							get_token_type(tokens[2]));
					SyntaxError(info,__LINE__,__FILE__);
				} else if (strcmp(get_token_value(tokens[2]),"int")==0 || strcmp(get_token_value(tokens[2]),"float") == 0) {
					return_val = 3;
				} else {
					char * info = malloc(sizeof(char)*1024);
					sprintf(info,
							"%s %s of type %d",
							"Unable to parse for statement. Expected int or float for new variable data type, but received token",
							get_token_value(tokens[1]),
							get_token_type(tokens[1]));
					SyntaxError(info,__LINE__,__FILE__);
				}
			} else return_val = 2;
		} else { //variable does exist
			if (num_tokens == 7 &&
					vs_is_empty(control_flow_stack)!= 1 &&
					strcmp(get_variable_name(vs_get_top(control_flow_stack)),"for")==0 &&
					get_variable_ival(vs_get_top(control_flow_stack))==2)
				SyntaxError("Unable to parse for statement. Incorrect statement length.",__LINE__,__FILE__);
			return_val = 1;
		}

	} else SyntaxError("Unable to parse for statement. Incorrect statement length.",__LINE__,__FILE__);

	//validate the rest of it
	int cur_token = 2;
	if (num_tokens == 7) cur_token = 3;
	//validate begin value
	if (get_token_type(tokens[cur_token])=='v') {
		int tmp_ind = variable_index(variables,tmp_num_variables,get_token_hash(tokens[cur_token]));
		if (tmp_ind == -1 && get_token_hash(tokens[cur_token]) != get_token_hash(tokens[1])) {
			char * info = malloc(sizeof(char)*1024);
			sprintf(info,"Unknown variable %s passed as begin value",get_token_value(tokens[cur_token]));
			SyntaxError(info,__LINE__,__FILE__);
		}
	} else if (get_token_type(tokens[cur_token])!='n') {
		char * info = malloc(sizeof(char)*1024);
		sprintf(info,"Unexpected token %s of type %d passed as begin value",
				get_token_value(tokens[cur_token]),
				get_token_type(tokens[cur_token]));
		SyntaxError(info,__LINE__,__FILE__);
	}
	//validate operator
	if (element_in_list_int(equalities,equalities_len,get_token_hash(tokens[cur_token+1]))==0) {
		char * info = malloc(sizeof(char)*1024);
		sprintf(info,"Unexpected token %s of type %d passed as equality operator",
				get_token_value(tokens[cur_token+1]),
				get_token_type(tokens[cur_token+1]));
		SyntaxError(info,__LINE__,__FILE__);
	}

	//validate end value
	if (get_token_type(tokens[cur_token+2])=='v') {
		int tmp_ind = variable_index(variables,tmp_num_variables,get_token_hash(tokens[cur_token+2]));
		if (tmp_ind == -1) {
			char * info = malloc(sizeof(char)*1024);
			sprintf(info,"Unexpected variable %s passed as end value",get_token_value(tokens[cur_token+2]));
			SyntaxError(info,__LINE__,__FILE__);
		}
	} else if (get_token_type(tokens[cur_token+2])!='n') {
		char * info = malloc(sizeof(char)*1024);
		sprintf(info,"Unexpected token %s of type %d passed as end value",
				get_token_value(tokens[cur_token+2]),
				get_token_type(tokens[cur_token+2]));
		SyntaxError(info,__LINE__,__FILE__);
	}

	//validate interval
	if (get_token_type(tokens[cur_token+3])=='v') {
		int tmp_ind = variable_index(variables,tmp_num_variables,get_token_hash(tokens[cur_token+3]));
		if (tmp_ind == -1) {
			char * info = malloc(sizeof(char)*1024);
			sprintf(info,"Unexpected variable %s passed as end value",get_token_value(tokens[cur_token+3]));
			SyntaxError(info,__LINE__,__FILE__);
		}
	} else if (get_token_type(tokens[cur_token+3])!='n') {
		char * info = malloc(sizeof(char)*1024);
		sprintf(info,"Unexpected token %s of type %d passed as end value",
				get_token_value(tokens[cur_token+3]),
				get_token_type(tokens[cur_token+3]));
		SyntaxError(info,__LINE__,__FILE__);
	}

	return return_val;
}

struct Variable ** eval_line(struct Token ** tokens,
		int num_tokens,
		struct Variable ** variables,
		int * num_variables,
		struct VariableStack * control_flow_stack,
		int * line_number) {

	int tmp_num_variables = *num_variables;
	int tmp_line_number = *line_number;

	if (num_tokens==0) return variables;

	if (vs_is_empty(control_flow_stack) || get_variable_ival(vs_get_top(control_flow_stack))==1) {
		if (get_token_hash(tokens[0])==1542341994) { //declare a new variable
			int result_type = validate_declare_variable_statement(tokens,num_tokens,variables,tmp_num_variables);

			if (result_type==1) { //instantiate a blank variable
				struct Variable * tmp_var = create_variable(get_token_value(tokens[2]),get_token_value(tokens[1]),0,0,"",-1);
				variables[tmp_num_variables] = tmp_var;
				tmp_num_variables++;
			}
			else {
				struct Variable* tmp = eval_infix(tokens,num_tokens,4,variables,tmp_num_variables);
				if (variable_types_compatible(get_variable_type(tmp),get_token_value(tokens[2]))==0)
					MismatchedTypesError(get_token_value(tokens[1]),get_token_value(tokens[2]),get_variable_type(tmp),__LINE__,__FILE__);
				if (strcmp(get_variable_type(tmp),"string")!=0) {
					int tmp_int = 0;
					float tmp_f = 0;
					unsigned token_hash = get_token_hash(tokens[2]);

					if (token_hash == 104431 || token_hash == -891985903) {
						if (strcmp(get_variable_type(tmp),"float")==0) {
							tmp_int = get_variable_fval(tmp);
						} else {
							tmp_int = get_variable_ival(tmp);
						}

					} else {
						tmp_f = get_variable_fval(tmp);
					}
					struct Variable * tmp_var = create_variable(get_token_value(tokens[2]),get_token_value(tokens[1]),tmp_int,tmp_f,"",-1);
					variables[tmp_num_variables] = tmp_var;
					tmp_num_variables++;
				}
			}
		} else if (get_token_hash(tokens[0])==499119488) { //ForBegin
			int validate_for = validate_for_statement(tokens,num_tokens,variables,tmp_num_variables,control_flow_stack);
			struct Variable * tmp_var = malloc(sizeof(struct Variable*));
			if (validate_for == 1) {
				int variable_ind = variable_index(variables,tmp_num_variables,get_token_hash(tokens[1]));
				tmp_var = variables[variable_ind];
				char * tmp_val = malloc(sizeof(char)*20);
				double tmp_double;
				int tmp_int;
				sprintf(tmp_val,"%s",get_token_value(tokens[2]));
				tmp_double = atof(tmp_val);
				tmp_int = tmp_double;
				assign_variable_value(tmp_var,tmp_int,tmp_double,"");
			}
			if (validate_for == 2 || validate_for == 3) {
				char * tmp_val = malloc(sizeof(char)*20);
				double tmp_double = 0;
				int tmp_int = 0;
				char * tmp_type = malloc(sizeof(char)*10);
				if (get_token_hash(tokens[2])!=get_token_hash(tokens[1])) {
					if (get_token_type(tokens[2])=='v') {
						int variable_ind = variable_index(variables,tmp_num_variables,get_token_hash(tokens[2]));
						sprintf(tmp_val,"%s",return_variable_value_as_char(variables[variable_ind]));
						tmp_double = atof(tmp_val);
						tmp_int = tmp_double;
					} else if (get_token_type(tokens[2])=='n') {
						tmp_double = atof(get_token_value(tokens[2]));
						tmp_int = tmp_double;
					}
				}
				if (validate_for == 2) sprintf(tmp_type,"int");
				else sprintf(tmp_type,"%s",get_token_value(tokens[2]));

				tmp_var = create_variable(tmp_type,get_token_value(tokens[1]),tmp_int,tmp_double,"",-1);
				variables[tmp_num_variables] = tmp_var;
				tmp_num_variables++;
			}
			double tmp_double;
			struct Variable * tmp_var2 = malloc(sizeof(struct Variable *));
			if (get_token_type(tokens[num_tokens-2])=='n') {
				tmp_double = atof(get_token_value(tokens[num_tokens-2]));
				tmp_var2 = create_variable("float","float",0,tmp_double,"",-1);
			} else if (get_token_type(tokens[num_tokens-2])=='v') {
				int variable_ind = variable_index(variables,tmp_num_variables,get_token_hash(tokens[num_tokens-2]));
				tmp_var2 = variables[variable_ind];
			}
			struct Variable * tmp_result = eval_op_numeric(tmp_var,tmp_var2,get_token_hash(tokens[num_tokens-3]));

			int tmp_result_int = get_variable_val_as_int_condition(tmp_result);
			struct Variable * push_to_stack = create_variable("control","for",tmp_result_int,0,"",tmp_line_number);
			vs_push(control_flow_stack,push_to_stack);
		} else if (get_token_hash(tokens[0])==2110017394) { // ForEnd
			if (vs_is_empty(control_flow_stack) || strcmp(get_variable_name(vs_get_top(control_flow_stack)),"for") != 0)
				SyntaxError("ForEnd loop found without corresponding Begin statement.",__LINE__,__FILE__);

			if (num_tokens > 1)
				SyntaxError("Too many tokens found on ForEnd line.",__LINE__,__FILE__);

			tmp_line_number = get_variable_line_number(vs_get_top(control_flow_stack));
			*line_number = tmp_line_number;
			assign_variable_value(vs_get_top(control_flow_stack),2,2,"");

		} else if (get_token_hash(tokens[0])==3714707480) { // WhileBegin
			if (num_tokens < 2)
				SyntaxError("WhileBegin statement requires an expression to evaluate.",__LINE__,__FILE__);

			struct Variable * while_tmp = eval_infix(tokens,num_tokens,1,variables,tmp_num_variables);
			int tmp_result_int = get_variable_val_as_int_condition(while_tmp);
			free(while_tmp);
			struct Variable * push_to_stack = create_variable("control","while",tmp_result_int,0,"",tmp_line_number);
			vs_push(control_flow_stack,push_to_stack);

		} else if (get_token_hash(tokens[0])==2220625930) { // WhileEnd
			if (vs_is_empty(control_flow_stack) || strcmp(get_variable_name(vs_get_top(control_flow_stack)),"while") != 0)
				SyntaxError("WhileEnd loop found without corresponding Begin statement.",__LINE__,__FILE__);

			if (num_tokens > 1)
				SyntaxError("Too many tokens found on WhileEnd line.",__LINE__,__FILE__);

			tmp_line_number = get_variable_line_number(vs_get_top(control_flow_stack));
			*line_number = tmp_line_number;
			assign_variable_value(vs_get_top(control_flow_stack),2,2,"");

		} else if (get_token_hash(tokens[0])==2365) { // If
			if (num_tokens==1) SyntaxError("No statement found after If call",__LINE__,__FILE__);

			struct Variable * tmp = eval_infix(tokens,num_tokens,1,variables,tmp_num_variables);
			double tmp_val = 0;
			if (strcmp(get_variable_type(tmp),"string")==0)
				InvalidValueError("If statement cannot interpret string value.",__LINE__,__FILE__);
			else if (strcmp(get_variable_type(tmp),"float")==0)
				tmp_val = get_variable_fval(tmp);
			else if (strcmp(get_variable_type(tmp),"int")==0 || strcmp(get_variable_type(tmp),"boolean")==0)
				tmp_val = get_variable_ival(tmp);

			if (tmp_val != 1 && tmp_val != 0) {
				char * info = malloc(sizeof(char)*1024);
				sprintf(info,"If statement cannot interpret value: %f",tmp_val);
				InvalidValueError(info,__LINE__,__FILE__);
			}

			struct Variable * tmp_control = create_variable("control","if",tmp_val,0,"",-1);

			vs_push(control_flow_stack,tmp_control);
		} else if (get_token_hash(tokens[0])==2162724 || //Elif
						get_token_hash(tokens[0])==2163033 || //Else
						get_token_hash(tokens[0])==67098424 )  { //EndIf
			if (strcmp(get_variable_name(vs_get_top(control_flow_stack)),"if")!=0)
				SyntaxError("Mismatched control flow arguments in your expression",__LINE__,__FILE__);
			if (get_token_hash(tokens[0])==67098424)
				vs_pop(control_flow_stack);
			else {
				struct Variable * tmp_control = vs_pop(control_flow_stack);
				assign_variable_value(tmp_control,2,0,"");
				vs_push(control_flow_stack,tmp_control);
			}
		} else if (get_token_type(tokens[0])=='v') {
			if (num_tokens < 2) {
				struct Variable* tmp = eval_infix(tokens,num_tokens,0,variables,tmp_num_variables);
							fprintf(stdout,"Result: %s\n",return_variable_value_as_char(tmp));
			}
			else {
				if (get_token_hash(tokens[1])==1376 || // ++
						get_token_hash(tokens[1])==1440) { // --
					int tmp_variable_index = variable_index(variables,tmp_num_variables,get_token_hash(tokens[0]));
					if (tmp_num_variables == 0 || tmp_variable_index==-1) //check if variable exists
						VariableNotFoundError(get_token_value(tokens[0]),__LINE__,__FILE__);

					if (num_tokens > 2) {
						char * info = malloc(sizeof(char)*1024);
						sprintf(info,"%s operator has too many tokens.",get_token_value(tokens[1]));
						SyntaxError(info,__LINE__,__FILE__);
					}

					if (strcmp(get_variable_type(variables[tmp_variable_index]),"int")!=0 &&
							strcmp(get_variable_type(variables[tmp_variable_index]),"float")!=0) {
						char * info = malloc(sizeof(char)*1024);
						sprintf(info,"Operator %s not valid for variable %s of type %s",
								get_token_value(tokens[1]),
								get_variable_name(variables[tmp_variable_index]),
								get_variable_type(variables[tmp_variable_index]));
						InvalidValueError(info,__LINE__,__FILE__);
					}

					double tmp_val_f = get_variable_fval(variables[tmp_variable_index]);
					int tmp_val_i = get_variable_ival(variables[tmp_variable_index]);
					int change = 0;

					if (get_token_hash(tokens[1])==1376) {
						change = 1;
					} else if (get_token_hash(tokens[1])==1440) {
						change = -1;
					}

					assign_variable_value(variables[tmp_variable_index],tmp_val_i+change,tmp_val_f+change,"");



				}
				else if (get_token_type(tokens[1])=='a') { // assign tasks

					int tmp_variable_index = variable_index(variables,tmp_num_variables,get_token_hash(tokens[0]));
					if (tmp_num_variables == 0 || tmp_variable_index==-1) //check if variable exists
						VariableNotFoundError(get_token_value(tokens[0]),__LINE__,__FILE__);

					if (num_tokens == 2) { //check that statement is long enough
						char * info = malloc(sizeof(char)*1024);
						sprintf("Variable %s assignment statement does not have a value.",get_token_value(tokens[0]));
						SyntaxError(info,__LINE__,__FILE__);
					}

					struct Variable* tmp = eval_infix(tokens,num_tokens,2,variables,tmp_num_variables);
					if (variable_types_compatible(get_variable_type(tmp),get_token_value(tokens[0]))==0)
						MismatchedTypesError(get_token_value(tokens[0]),
								get_variable_type(variables[tmp_variable_index]),
								get_variable_type(tmp),
								__LINE__,
								__FILE__);

					struct Variable * tmp_assign = malloc(sizeof(struct Variable *));
					if (strcmp(get_token_value(tokens[1]),"assign")!=0) {
						char * tmp_val_c = malloc(sizeof(char)*2);
						sprintf(tmp_val_c,"%c",get_token_value(tokens[1])[0]);
						double tmp_val_d = hash(tmp_val_c);
						tmp_assign = eval_op(variables[tmp_variable_index],tmp,tmp_val_d);
					} else {
						tmp_assign = tmp;
					}

					float tmp_float = get_variable_fval(tmp_assign);
					int tmp_int = tmp_float;

					assign_variable_value(variables[tmp_variable_index],
							tmp_int,
							tmp_float,
							get_variable_cval(tmp_assign));
				}
			}
		} else {
			struct Variable* tmp = eval_infix(tokens,num_tokens,0,variables,tmp_num_variables);
			fprintf(stdout,"Result: %s\n",return_variable_value_as_char(tmp));
		}

	} else if (get_variable_ival(vs_get_top(control_flow_stack))==2) { // if the control flow stack says the task is already complete

		// handle all if logic
		if (get_token_hash(tokens[0])==2162724 || // Elif
				get_token_hash(tokens[0])==2163033 || // Else
				get_token_hash(tokens[0])==67098424 || // EndIf
				(get_token_hash(tokens[0])==2365)) {
			if (strcmp(get_variable_name(vs_get_top(control_flow_stack)),"if")!=0)
				SyntaxError("Mismatched control flow arguments in your expression",__LINE__,__FILE__);

			if (get_token_hash(tokens[0])==67098424) vs_pop(control_flow_stack);
			else if (get_token_hash(tokens[0])==2365)  {  // If
				struct Variable * tmp_control = create_variable("control","if",2,0,"",-1);
				vs_push(control_flow_stack,tmp_control);
			}
		} else if (get_token_hash(tokens[0])==499119488) { // ForBegin

			int tmp_var_index = variable_index(variables,tmp_num_variables,get_token_hash(tokens[1]));
			double interval = atof(get_token_value(tokens[num_tokens-1]));
			double tmp_double;
			struct Variable * tmp_var = malloc(sizeof(struct Variable *));
			if (strcmp(get_variable_type(variables[tmp_var_index]),"float")==0) {
				assign_variable_value(variables[tmp_var_index],0,get_variable_fval(variables[tmp_var_index])+interval,"");
			} else {
				int tmp_val = get_variable_ival(variables[tmp_var_index])+interval;
				assign_variable_value(variables[tmp_var_index],tmp_val,0,"");
			}

			if (get_token_type(tokens[num_tokens-2])=='n') {
				tmp_double = atof(get_token_value(tokens[num_tokens-2]));
				tmp_var = create_variable("float","float",0,tmp_double,"",-1);
			} else if (get_token_type(tokens[num_tokens-2])=='v') {
				int variable_ind = variable_index(variables,tmp_num_variables,get_token_hash(tokens[num_tokens-2]));
				tmp_var = variables[variable_ind];
			}
			struct Variable * tmp_result = eval_op_numeric(variables[tmp_var_index],tmp_var,get_token_hash(tokens[num_tokens-3]));

			int tmp_result_int = get_variable_val_as_int_condition(tmp_result);
			assign_variable_value(vs_get_top(control_flow_stack),tmp_result_int,0,"");

		} else if (get_token_hash(tokens[0])==3714707480) { // WhileBegin
			struct Variable * tmp_while = eval_infix(tokens,num_tokens,1,variables,tmp_num_variables);
			int tmp_result_int = get_variable_val_as_int_condition(tmp_while);
			assign_variable_value(vs_get_top(control_flow_stack),tmp_result_int,0,"");
			free(tmp_while);
		}

	} else if (get_variable_ival(vs_get_top(control_flow_stack))==0) { // if the control flow stack says the task is not complete

		// handle all if logic
		if ((get_token_hash(tokens[0])==2162724 || // Elif
			get_token_hash(tokens[0])==2163033 || // Else
			get_token_hash(tokens[0])==67098424) && // EndIf
				strcmp(get_variable_name(vs_get_top(control_flow_stack)),"if")==0) {

			vs_pop(control_flow_stack);

			if(get_token_hash(tokens[0])==2162724) { // Else if
				if (num_tokens==1) SyntaxError("No statement found after If call",__LINE__,__FILE__);

				struct Variable * tmp = eval_infix(tokens,num_tokens,1,variables,tmp_num_variables);
				double tmp_val = 0;
				if (strcmp(get_variable_type(tmp),"string")==0)
					InvalidValueError("If statement cannot interpret string value.",__LINE__,__FILE__);
				else if (strcmp(get_variable_type(tmp),"float")==0)
					tmp_val = get_variable_fval(tmp);
				else if (strcmp(get_variable_type(tmp),"int")==0 || strcmp(get_variable_type(tmp),"boolean")==0)
					tmp_val = get_variable_ival(tmp);

				if (tmp_val != 1 && tmp_val != 0) {
					char * info = malloc(sizeof(char)*1024);
					sprintf(info,"If statement cannot interpret value: %f",tmp_val);
					InvalidValueError(info,__LINE__,__FILE__);
				}
				struct Variable * tmp_control = create_variable("control","if",tmp_val,0,"",-1);
				vs_push(control_flow_stack,tmp_control);

			} else if (get_token_hash(tokens[0])==2163033) { // Else
				struct Variable * tmp_control = create_variable("control","if",1,0,"",-1);
				vs_push(control_flow_stack,tmp_control);
			}
		}

		else if (get_token_hash(tokens[0])==499119488) { //ForBegin
			if (strcmp(get_variable_name(vs_get_top(control_flow_stack)),"for")==0) {
				struct Variable * tmp_control = create_variable("control","for",0,0,"",tmp_line_number);
				vs_push(control_flow_stack,tmp_control);
			}
		}

		else if (get_token_hash(tokens[0])==2110017394) { //ForEnd
			if (vs_is_empty(control_flow_stack) || strcmp(get_variable_name(vs_get_top(control_flow_stack)),"for")!=0)
				SyntaxError("ForEnd found without matching For loop",__LINE__,__FILE__);
			vs_pop(control_flow_stack);
		}

		} else if (get_token_hash(tokens[0])==3714707480) { // WhileBegin
			if (strcmp(get_variable_name(vs_get_top(control_flow_stack)),"while")==0) {
				struct Variable * tmp_control = create_variable("control","while",0,0,"",tmp_line_number);
				vs_push(control_flow_stack,tmp_control);
			}
		} else if (get_token_hash(tokens[0])==2220625930) { // WhileEnd
			if (vs_is_empty(control_flow_stack) || strcmp(get_variable_name(vs_get_top(control_flow_stack)),"while")!=0)
				SyntaxError("WhileEnd found without matching While loop",__LINE__,__FILE__);
			vs_pop(control_flow_stack);

	} else SyntaxError("Something is wrong with your expression!",__LINE__,__FILE__);

	*num_variables = tmp_num_variables;
	return variables;
}

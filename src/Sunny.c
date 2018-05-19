/*
 ============================================================================
 Name        : Sunny.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utils/File_Utils.h"
#include "utils/String_Utils.h"
#include "utils/Math_Utils.h"
#include "utils/Misc_Utils.h"

#include "struct/Token.h"
#include "struct/Variable.h"
#include "struct/VariableStack.h"

#include "Exceptions.h"
#include "Tokenizer.h"

static char * df = "./cmds.csv";

int main(int argc, char* argv[]) {


	printf("++: %u\n",hash("++"));
	printf("--: %u\n",hash("--"));
	clock_t start = clock(), diff;

	int cmd_num_rows, cmd_num_fields;
	char *** cmds = load_csv(df,',',&cmd_num_fields,&cmd_num_rows);

	char * s_file_name;

	//handle incorrect command line issues;
	if (argc==1)
		CommandArgumentError("No file received from command line.",__LINE__,__FILE__);
	else if (argc > 2)
		CommandArgumentError("Too many commands received.",__LINE__,__FILE__);
	else {
		size_t file_name_length = strlen(argv[1]);
		if (strcmp(argv[1]+(file_name_length-3),".s\0")==0)
			CommandArgumentError("File type not recognized. Use .st files.",__LINE__,__FILE__);
		s_file_name = malloc(sizeof(char)*file_name_length+1);
		s_file_name = argv[1];
	}

	int sdata_num_rows;
	char ** s_data = load_file(s_file_name,&sdata_num_rows);
	struct Variable ** variables = malloc(sizeof(struct Variable *)*sdata_num_rows);
	struct VariableStack * control_flow_stack = vs_create_stack(sdata_num_rows);

	int num_variables = 0;
	int i = 0;

	struct Token *** token_array = malloc(sizeof(struct Token **)*sdata_num_rows);
	int token_array_lengths[sdata_num_rows];
	while (i < sdata_num_rows) {
		int num_tokens = 0;
		fprintf(stdout,"Initial phrase: %s\n",s_data[i]);
		token_array[i] = tokenize_line(s_data[i],
				&num_tokens,
				cmds,
				cmd_num_rows,
				cmd_num_fields);

		token_array_lengths[i] = num_tokens;
		fprintf(stdout,"Translated: ");
		for (int j = 0; j < num_tokens; j++) {
			struct Token * t = token_array[i][j];
			fprintf(stdout,"%s ",get_token_value(t));
		}
		fprintf(stdout,"\n");
		i++;
	}
	fprintf(stdout,"\n");
	i = 0;
	while (i < sdata_num_rows) {
		int line_number = i;
		variables = eval_line(token_array[i],token_array_lengths[i],variables,&num_variables,control_flow_stack,&line_number);
		if (line_number != i) {
			i = line_number;
		}
		else i++;
	}

	free(s_data);
	free(variables);

	diff = clock() - start;

	int msec = diff * 1000/CLOCKS_PER_SEC;
	fprintf(stdout,"\nTime taken %d seconds %d milliseconds", msec/1000, msec%1000);

	return 0;
}

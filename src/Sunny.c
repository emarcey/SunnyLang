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

#include "struct/Token.h"
#include "struct/Variable.h"

#include "Exceptions.h"
#include "Tokenizer.h"

static char * df = "./cmds.csv";
//struct Variable ** user_variables = malloc(sizeof(struct Variable *)*25);
//static int user_variable_ct = 0;

int main(int argc, char* argv[]) {
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
	struct Stack * if_stack = createStack(sdata_num_rows);

	int num_variables = 0;
	for (int i = 0; i < sdata_num_rows; i++) {
		int num_tokens;
		printf("Initial phrase: %s\n",s_data[i]);
		struct Token ** tokens = tokenize_line(s_data[i],
				&num_tokens,
				cmds,
				cmd_num_rows,
				cmd_num_fields);
		printf("Translated: ");
		for (int j = 0; j < num_tokens; j++) {
			struct Token * t = tokens[j];
			printf("%s ",get_token_value(t));
		}
		printf("\n");
		variables = eval_line(tokens,num_tokens,variables,&num_variables,if_stack);
	}
	if (isEmpty(if_stack)) SyntaxError("No EndIf statement found at the end of your program.",__LINE__,__FILE__);

	free(s_data);
	free(variables);

	diff = clock() - start;

	int msec = diff * 1000/CLOCKS_PER_SEC;
	printf("Time taken %d seconds %d milliseconds", msec/1000, msec%1000);

	return 0;
}

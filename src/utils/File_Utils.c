#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "String_Utils.h"
#include "../Exceptions.h"

int count_lines(char * filename) {
	FILE * stream = fopen(filename,"r");
	char line[1024];
	int line_ct = 0;

	while (fgets(line, 1024, stream)) {
		line_ct++;
	}
	return line_ct;
}

char ** load_file(char * filename, int * num_rows) {
	int lines = count_lines(filename);
	*num_rows = lines;
	char ** file_data = malloc(sizeof(char*)*(lines+1));

	//if (lines == 0) FileNotFoundError(filename,__LINE__,__FILE__);

	FILE * stream = fopen(filename,"r");
	char line[1024];
	int line_ct = 0;

	while (fgets(line, 1024, stream)) {
		file_data[line_ct] = malloc(sizeof(char)*(strlen(line)+1));
		sprintf(file_data[line_ct],"%s",line);
		if (file_data[line_ct][strlen(line)-1] == '\n') {
			file_data[line_ct][strlen(line)-1] = '\0';
		}
		line_ct++;
	}

	return file_data;
}

char *** load_csv(char * filename, char delimiter, int * row_width, int * num_rows) {
	int lines = count_lines(filename);
	*num_rows = lines;
	char *** file_data = malloc(sizeof(char**)*(lines+1));
	char * v_delimiter = malloc(sizeof(char)*2);
	v_delimiter[0] = delimiter;
	v_delimiter[1] = '\0';

	FILE * stream = fopen(filename,"r");
	char line[1024];
	int line_ct = 0;

	while (fgets(line, 1024, stream)) {
		int num_fields = count_chars(line,delimiter);
		file_data[line_ct] = malloc(sizeof(char*)*(num_fields+1));

		char * words = strtok(line,v_delimiter);
		int word_ct = 0;

		while (words != NULL) {
			file_data[line_ct][word_ct] = malloc(sizeof(char)*(strlen(words)+1));
			sprintf(file_data[line_ct][word_ct],"%s",words);
			if (file_data[line_ct][word_ct][strlen(words)-1]=='\n') {
				file_data[line_ct][word_ct][strlen(words)-1] = '\0';
			}
			words = strtok(NULL,v_delimiter);
			word_ct++;
		}
		*row_width = num_fields+1;
		line_ct ++;
		free(words);


	}


	return file_data;
}

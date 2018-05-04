/*
 * File_Methods.h
 *
 *  Created on: May 2, 2018
 *      Author: evan.marcey
 */

#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_

/*
 * count_lines:
 *  - counts the number of lines in a file
 *
 * params:
 *  - file_name: name of file to check
 *
 * returns:
 *  - number of lines in file_name
 */
int count_lines(char * file_name);

/*
 * load_file:
 *  - loads file line by line into character array
 *
 * params:
 *  - filename: name of file to load
 *  - num_rows: pointer set to number of lines found in file
 *
 * returns:
 *  - array where each row is a line in the file
 */
char ** load_file(char * filename, int * num_rows);

/*
 * load_csv:
 *  - loads a file line by line into character array, split by delimiter
 *
 * params:
 *  - filename: name of file to load
 *  - delimiter: delimiter to use to split each row (i.e. ',' for a csv)
 *  - row_width: pointer set to number of columns in a row
 *  - num_rows: pointer set to number of lines found in file
 *
 * returns:
 *  - array where each row is an array of the split fields from a line in the file
 */
char *** load_csv(char * filename, char delimiter, int * row_width, int * num_rows);

#endif /* FILE_UTILS_H_ */

/*
 * TestingCustomLists.c
 *
 *  Created on: Jun 11, 2018
 *      Author: evan.marcey
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../utils/File_Utils.h"
#include "../utils/String_Utils.h"
#include "../utils/Math_Utils.h"
#include "../utils/Misc_Utils.h"

#include "../struct/Token.h"
#include "../struct/Variable.h"
#include "../struct/VariableStack.h"
#include "../struct/CustomList.h"
#include "../struct/ListItem.h"

#include "../Exceptions.h"
#include "../Tokenizer.h"
#include "../GlobalVariables.h"

int test_ListItem() {
	//test create method
	struct ListItem * tmp1 = create_ListItem("string","test_string",0,0,NULL); //create string
	struct ListItem * tmp2 = create_ListItem("int","test_string",1,0,NULL); //create int
	struct ListItem * tmp3 = create_ListItem("boolean","test_string",1,0,NULL); //create boolean
	struct ListItem * tmp4 = create_ListItem("float","test_string",0,1.1,NULL); //create float
	//struct ListItem * tmp5 = create_ListItem("rawr","test_string",0,1.1,NULL); //create invalid type
	// wait for customList until later

	// testing print method
	printf("Printing New List Items...\n");
	printf("\ttmp1: ");
	print_list_item(tmp1);
	printf("\n");
	printf("\ttmp2: ");
	print_list_item(tmp2);
	printf("\n");
	printf("\ttmp3: ");
	print_list_item(tmp3);
	printf("\n");
	printf("\ttmp4: ");
	print_list_item(tmp4);
	printf("\n");

	//test get_c_item
	char * tmp;
	//this should not return an error
	tmp = get_ListItem_c_item(tmp1);
	printf("Get tmp1 c_item: %s\n",tmp);
	/*
	//this should return an error
	tmp = get_ListItem_c_item(tmp2);
	printf("Get tmp2 c_item: %s\n",tmp);
	//this should return an error
	tmp = get_ListItem_c_item(tmp3);
	printf("Get tmp3 c_item: %s\n",tmp);
	//this should return an error
	tmp = get_ListItem_c_item(tmp4);
	printf("Get tmp3 c_item: %s\n",tmp);
	*/

	//test get_i_item
	int tmp_i;
	/*
	int tmp_i = get_ListItem_i_item(tmp1);
	printf("Get tmp1 i_item: %d\n",tmp_i);
	*/
	//this should not return an error
	tmp_i = get_ListItem_i_item(tmp2);
	printf("Get tmp2 i_item: %d\n",tmp_i);
	//this should not return an error
	tmp_i = get_ListItem_i_item(tmp3);
	printf("Get tmp3 i_item: %d\n",tmp_i);
	//this should return an error
	/*
	tmp_i = get_ListItem_i_item(tmp4);
	printf("Get tmp3 i_item: %d\n",tmp_i);
	*/

	//test get_f_item
	float tmp_f;
	/*
	//this should return an error
	tmp_f = get_ListItem_f_item(tmp1);
	printf("Get tmp1 f_item: %f\n",tmp_f);
	//this should return an error
	tmp_f = get_ListItem_f_item(tmp2);
	printf("Get tmp2 f_item: %f\n",tmp_f);
	//this should return an error
	tmp_f = get_ListItem_f_item(tmp3);
	printf("Get tmp3 f_item: %f\n",tmp_f);
	*/
	//this should not return an error
	tmp_f = get_ListItem_f_item(tmp4);
	printf("Get tmp3 f_item: %f\n",tmp_f);

	//test updates
	update_ListItem(tmp1,"new_string",0,0,NULL);
	update_ListItem(tmp2,"",0,0,NULL);
	update_ListItem(tmp3,"",0,0,NULL);
	update_ListItem(tmp4,"",0,0.1234,NULL);

	// testing print method
	printf("Printing New List Items...\n");
	printf("\ttmp1: ");
	print_list_item(tmp1);
	printf("\n");
	printf("\ttmp2: ");
	print_list_item(tmp2);
	printf("\n");
	printf("\ttmp3: ");
	print_list_item(tmp3);
	printf("\n");
	printf("\ttmp4: ");
	print_list_item(tmp4);
	printf("\n");

	return 1;
}

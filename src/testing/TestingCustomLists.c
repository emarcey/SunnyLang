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


int test_CustomList() {
	// create a few list items
	struct ListItem * tmp1 = create_ListItem("string","test_string",0,0,NULL); //create string
	struct ListItem * tmp2 = create_ListItem("int","test_string",1,0,NULL); //create int
	struct ListItem * tmp3 = create_ListItem("boolean","test_string",1,0,NULL); //create boolean
	struct ListItem * tmp4 = create_ListItem("float","test_string",0,1.1,NULL); //create float

	//create a new CustomList
	struct CustomList * tmp_customlist = create_CustomList();

	//should be not full and is empty
	printf("Is tmp_customlist full? %d\n",cl_is_full(tmp_customlist));
	printf("Is tmp_customlist empty? %d\n",cl_is_empty(tmp_customlist));

	printf("Current index should be -1: %u\n",cl_get_index(tmp_customlist));
	printf("Current capacity should be 1000: %u\n",cl_get_capacity(tmp_customlist));

	//insert all ListItems to back
	cl_insert_back(tmp_customlist,tmp1);
	cl_insert_back(tmp_customlist,tmp2);
	printf("Current index should be 1: %u\n",cl_get_index(tmp_customlist));

	//print all elements in list
	cl_print_list(tmp_customlist);

	//insert element at front
	cl_insert(tmp_customlist,tmp3,0);
	cl_print_list(tmp_customlist);

	//insert element at index 1
	cl_insert(tmp_customlist,tmp4,1);
	cl_print_list(tmp_customlist);

	//remove an element from the back
	printf("Current index should be 3: %u\n",cl_get_index(tmp_customlist));
	struct ListItem * tmp_remove_back = cl_remove_back(tmp_customlist);
	printf("Current index should be 2: %u\n",cl_get_index(tmp_customlist));
	printf("Item removed from list:\n");
	print_list_item(tmp_remove_back);
	printf("\n");
	cl_print_list(tmp_customlist);
	free(tmp_remove_back);

	//remove an element from index 1
	printf("Current length should be 3: %u\n",cl_get_length(tmp_customlist));
	struct ListItem * tmp_remove_back1 = cl_remove(tmp_customlist,1);
	printf("Current index should be 2: %u\n",cl_get_length(tmp_customlist));
	printf("Item removed from list:\n");
	print_list_item(tmp_remove_back1);
	printf("\n");
	cl_print_list(tmp_customlist);

	/*
	//test removing an item from an empty list
	cl_remove_back(tmp_customlist);
	cl_remove_back(tmp_customlist);
	//should error here
	cl_remove_back(tmp_customlist);
	*/

	//test getting a list item
	struct ListItem * tmp_get = cl_get_item(tmp_customlist,0);

	printf("Get Item:\n\t");
	print_list_item(tmp_get);
	printf("\n");
	free(tmp_get);

	cl_print_list(tmp_customlist);
	//should throw error - out of bounds test 1
	//struct ListItem * tmp_get1 = cl_get_item(tmp_customlist,-1);
	//should throw error - out of bounds test 2
	//struct ListItem * tmp_get2 = cl_get_item(tmp_customlist,cl_get_length(tmp_customlist));

	struct ListItem * tmp_update = create_ListItem("string","update_string",0,0,NULL); //create string
	//should throw error - out of bounds test 1
	//cl_update(tmp_customlist,tmp_update,-1);
	//should throw error - out of bounds test 2
	//cl_update(tmp_customlist,tmp_update,cl_get_length(tmp_customlist));
	cl_update(tmp_customlist,tmp_update,0);
	cl_print_list(tmp_customlist);
	cl_update(tmp_customlist,tmp_update,1);
	cl_print_list(tmp_customlist);

	//clean out list so we can test capacity
	cl_remove_back(tmp_customlist);
	cl_remove_back(tmp_customlist);

	//test capacity
	for (int i = 0; i < 1001; i++) {
		struct ListItem * tmp_iter = create_ListItem("int","",i,0,NULL);
		cl_insert_back(tmp_customlist,tmp_iter);
	}
	cl_print_list(tmp_customlist);

	return 1;
}

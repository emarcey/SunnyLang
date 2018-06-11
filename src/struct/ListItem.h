/*
 * ListItem.h
 *
 *  Created on: Jun 11, 2018
 *      Author: evan.marcey
 */

#include "./CustomList.h"

#ifndef STRUCT_LISTITEM_H_
#define STRUCT_LISTITEM_H_

// definition for item in a list
struct ListItem;

/*
 * 	create_ListItem:
 * 		- creates and returns a new ListItem
 *
 * 	params:
 * 		- type: type of ListItem to create
 * 			- currently accepted types: string, int, boolean, float, list
 * 		- c_item: value of item if string
 * 		- i_item: value of item if int or boolean
 * 		- f_item: value of item if float
 * 		- cl_item: value of item if list
 *
 * 	returns:
 * 		- new ListItem
 */
struct ListItem * create_ListItem(char * type,
		char * c_item,
		int i_item,
		float f_item,
		struct CustomList * cl_item);

/*
 *  get_ListItem_c_item:
 *  	- returns string value if ListItem is of string type
 *
 *  params:
 *  	- listitem: ListItem for which we want the string value
 *
 *  returns:
 *  	- c_item, if string type
 */
char * get_ListItem_c_item(struct ListItem * listitem);

/*
 *  get_ListItem_i_item:
 *  	- returns int value if ListItem is of int or boolean type
 *
 *  params:
 *  	- listitem: ListItem for which we want the int value
 *
 *  returns:
 *  	- i_item, if int or boolean type
 */
int get_ListItem_i_item(struct ListItem * listitem);

/*
 *  get_ListItem_f_item:
 *  	- returns float value if ListItem is of float type
 *
 *  params:
 *  	- listitem: ListItem for which we want the float value
 *
 *  returns:
 *  	- f_item, if float type
 */
float get_ListItem_f_item(struct ListItem * listitem);

/*
 *  get_ListItem_cl_item:
 *  	- returns CustomList value if ListItem is of list type
 *
 *  params:
 *  	- listitem: ListItem for which we want the list value
 *
 *  returns:
 *  	- cl_item, if list type
 */
struct CustomList * get_ListItem_cl_item(struct ListItem * listitem);

/*
 * 	update_ListItem:
 * 		- creates and returns a new ListItem
 *
 * 	params:
 * 		- listitem: ListItem object we want to update
 * 		- c_item: value of item if string
 * 		- i_item: value of item if int or boolean
 * 		- f_item: value of item if float
 * 		- cl_item: value of item if list
 *
 */
void update_ListItem(struct ListItem * listitem,
	char * c_item,
	int i_item,
	float f_item,
	struct CustomList * cl_item);

/*
 * 	print_list_item:
 * 		- prints out the data in a listitem, based on its type
 *
 * 	params:
 * 		- listitem: ListItem object we want to print
 */
void print_list_item(struct ListItem * listitem);

#endif /* STRUCT_LISTITEM_H_ */

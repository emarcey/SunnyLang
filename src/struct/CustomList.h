/*
 * customList.h
 *
 *  Created on: Jun 11, 2018
 *      Author: evan.marcey
 */

#ifndef STRUCT_CUSTOMLIST_H_
#define STRUCT_CUSTOMLIST_H_

// struct definition for a custom list object
struct CustomList;

/*
 * 	create_CustomList:
 * 		- creates a new empty customlist struct
 * 		- defaults capacity to 1000
 *
 * 	returns:
 * 		- new CustomList struct
 */
struct CustomList * create_CustomList();

/*
 * 	cl_is_full:
 * 		- checks if a customlist is full
 *
 * 	params:
 * 		- customlist: CustomList to check
 *
 * 	returns:
 * 		- 1 if full, otherwise 0
 */
int cl_is_full(struct CustomList * customlist);

/*
 * 	cl_is_empty:
 * 		- checks if a customlist is empty
 *
 * 	params:
 * 		- customlist: CustomList to check
 *
 * 	returns:
 * 		- 1 if empty, otherwise 0
 */
int cl_is_empty(struct CustomList * customlist);

/*
 *  cl_realloc_list:
 * 		- reallocates the memory of a CustomList
 * 		- increases to capacity*1.5
 *
 * 	params:
 * 		- customlist: CustomList to reallocate
 */
void cl_realloc_list(struct CustomList * customlist);

/*
 * 	cl_get_item:
 * 		- retrieves a ListItem from a CustomList at given index
 *
 * 	params:
 * 		- customlist: CustomList object from which ListItem is retrieved
 * 		- v_index: index at which desired ListItem is located
 *
 * 	returns:
 * 		- ListItem at v_index
 */
struct ListItem * cl_get_item(struct CustomList * customlist, int v_index);

/*
 * 	cl_get_index:
 * 		- retrieves the current index of a CustomList object
 *
 * 	params:
 * 		- customlist: CustomList object whose current index we want
 *
 * 	returns:
 * 		- index of CustomList object
 */
unsigned int cl_get_index(struct CustomList * customlist);

/*
 * 	cl_get_length:
 * 		- retrieves the current length of a CustomList object
 *
 * 	params:
 * 		- customlist: CustomList object whose current length we want
 *
 * 	returns:
 * 		- index of CustomList object + 1
 */
unsigned int cl_get_length(struct CustomList * customlist);

/*
 * 	cl_get_capacity:
 * 		- retrieves the capacity of a CustomList object
 *
 * 	params:
 * 		- customlist: CustomList object whose capacity we want
 *
 * 	returns:
 * 		- capacity of CustomList object
 */
unsigned int cl_get_capacity(struct CustomList * customlist);

/*
 * 	cl_insert_back:
 * 		- inserts an item at the end of a CustomList
 *
 * 	params:
 * 		- customlist: CustomList object to which we are appending data
 * 		- listitem: ListItem data to append
 */
void cl_insert_back(struct CustomList * customlist, struct ListItem * listitem);

/*
 * 	cl_remove_back:
 * 		- removes an item from the end of a CustomList
 *
 * 	params:
 * 		- customlist: CustomList object from which we are removing data
 *
 * 	returns:
 * 		- ListItem data that was removed
 */
struct ListItem * cl_remove_back(struct CustomList * customlist);

/*
 * 	cl_update:
 * 		- updates a CustomList with a new ListItem at a given index
 *
 * 	params
 * 		- customlist: CustomList object which we are updating
 * 		- listitem: new value of ListItem to be updated
 * 		- v_index: index of ListItem to be updated
 *
 */
void cl_update(struct CustomList * customlist, struct ListItem * listitem, unsigned int v_index);

/*
 * 	cl_insert:
 * 		- inserts a new ListItem into a CustomList at a given index
 *
 * 	params:
 * 		- customlist: CustomList object which we are updating
 * 		- listitem: new value of ListItem to be inserted
 * 		- v_index: index where ListItem is to be inserted
 */
void cl_insert(struct CustomList * customlist, struct ListItem * listitem, unsigned int v_index);

/*
 * 	cl_remove:
 * 		- removes a ListItem from a CustomList at a given index
 *
 * 	params:
 * 		- customlist: CustomList object from which we are removing an object
 * 		- v_index: index where ListItem to be removed is located
 *
 * 	returns:
 * 		- listitem: new value of ListItem that was removed
 */
struct ListItem * cl_remove(struct CustomList * customlist, unsigned int v_index);

/*
 * 	cl_print_list:
 * 		- iterates through a list, printing all of the objects contained within
 *
 *	params:
 *		- customlist: CustomList object whose contents are to be printed
 */
void cl_print_list(struct CustomList * customlist);

#endif /* STRUCT_CUSTOMLIST_H_ */

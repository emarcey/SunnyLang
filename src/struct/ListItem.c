/*
 * ListItem.c
 *
 *  Created on: Jun 11, 2018
 *      Author: evan.marcey
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "./CustomList.h"
#include "../Exceptions.h"

struct ListItem {
	char * type;
	union {
		char * c_item;
		int i_item;
		float f_item;
		struct CustomList * cl_item;
	} u_item;
};

struct ListItem * create_ListItem(char * type,
		char * c_item,
		int i_item,
		float f_item,
		struct CustomList * cl_item) {
	struct ListItem * listitem = (struct ListItem*) malloc(sizeof(struct ListItem));
	listitem->type = type;

	if (strcmp(type,"string")==0) listitem->u_item.c_item = c_item;
	else if (strcmp(type,"int")==0 || strcmp(type,"boolean")==0) listitem->u_item.i_item = i_item;
	else if (strcmp(type,"float")==0) listitem->u_item.f_item = f_item;
	else if (strcmp(type,"list")==0) listitem->u_item.cl_item = cl_item;
	else {
		ListTypeNotRecognizedError(type, "ListItem", __LINE__,__FILE__);
	}

	return listitem;
}

char * get_ListItem_c_item(struct ListItem * listitem) {
	if (strcmp(listitem->type,"string")!=0)
		InvalidTypeReturnError(listitem->type, "list", "string",__LINE__,__FILE__);
	return listitem->u_item.c_item;
}

int get_ListItem_i_item(struct ListItem * listitem) {
	if (strcmp(listitem->type,"int")!=0 && strcmp(listitem->type,"boolean")!=0)
		InvalidTypeReturnError(listitem->type, "list", "int",__LINE__,__FILE__);
	return listitem->u_item.i_item;
}

float get_ListItem_f_item(struct ListItem * listitem) {
	if (strcmp(listitem->type,"float")!=0)
		InvalidTypeReturnError(listitem->type, "list", "float",__LINE__,__FILE__);
	return listitem->u_item.f_item;
}

struct CustomList * get_ListItem_cl_item(struct ListItem * listitem) {
	if (strcmp(listitem->type,"list")!=0)
		InvalidTypeReturnError(listitem->type, "list", "list",__LINE__,__FILE__);
	return listitem->u_item.cl_item;
}

void update_ListItem(struct ListItem * listitem,
	char * c_item,
	int i_item,
	float f_item,
	struct CustomList * cl_item) {

	if (strcmp(listitem->type,"string")==0) listitem->u_item.c_item = c_item;
		else if (strcmp(listitem->type,"int")==0 || strcmp(listitem->type,"boolean")==0) listitem->u_item.i_item = i_item;
		else if (strcmp(listitem->type,"float")==0) listitem->u_item.f_item = f_item;
		else if (strcmp(listitem->type,"list")==0) listitem->u_item.cl_item = cl_item;
		else ListTypeNotRecognizedError(listitem->type, "ListItem", __LINE__,__FILE__);
}

void print_list_item(struct ListItem * listitem) {
	if (strcmp(listitem->type,"string")==0) printf("%s\n",listitem->u_item.c_item);
		else if (strcmp(listitem->type,"int")==0 || strcmp(listitem->type,"boolean")==0) printf("%d\n",listitem->u_item.i_item);
		else if (strcmp(listitem->type,"float")==0) printf("%f\n",listitem->u_item.f_item);
		else if (strcmp(listitem->type,"list")==0) cl_print_list(listitem->u_item.cl_item);
		else ListTypeNotRecognizedError(listitem->type, "ListItem", __LINE__,__FILE__);
}

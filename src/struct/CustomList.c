/*
 * CustomList.c
 *
 *  Created on: Jun 11, 2018
 *      Author: evan.marcey
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "./ListItem.h"
#include "../Exceptions.h"

struct CustomList {
	unsigned int index;
	unsigned int capacity;
	struct ListItem ** list;
};

struct CustomList * create_CustomList() {
	struct CustomList * customlist = (struct CustomList*) malloc(sizeof(struct CustomList));
	customlist->index=-1;
	customlist->capacity=1000;
	customlist->list=malloc(sizeof(struct ListItem*)*customlist->capacity);
	return customlist;
}

int cl_is_full(struct CustomList * customlist) {
	return customlist->index==(customlist->capacity-1);
}

int cl_is_empty(struct CustomList * customlist) {
	return customlist->index==-1;
}

void cl_realloc_list(struct CustomList * customlist) {
	struct ListItem ** tmp_list = malloc(sizeof(struct ListItem*)*customlist->capacity);
	for (int i = 0; i < customlist->index+1; i++)
		tmp_list[i] = customlist->list[i];
	customlist->capacity = customlist->capacity*1.5;
	realloc(customlist->list, sizeof(struct ListItem*)*customlist->capacity);
	customlist->list=tmp_list;
}

struct ListItem * cl_get_item(struct CustomList * customlist, int v_index) {
	if (v_index > customlist->index || v_index < 0)
		IndexOutOfBoundsError(v_index,customlist->index+1,__LINE__,__FILE__);
	return customlist->list[v_index];
}

unsigned int cl_get_index(struct CustomList * customlist) {
	return customlist->index;
}

unsigned int cl_get_length(struct CustomList * customlist) {
	return customlist->index+1;
}

unsigned int cl_get_capacity(struct CustomList * customlist) {
	return customlist->capacity;
}

void cl_insert_back(struct CustomList * customlist, struct ListItem * listitem) {
	if (cl_is_full(customlist))
		cl_realloc_list(customlist);
	customlist->index++;
	customlist->list[customlist->index]=listitem;
}

struct ListItem * cl_remove_back(struct CustomList * customlist) {
	if (cl_is_empty(customlist))
		EmptyListError(__LINE__,__FILE__);
	return customlist->list[customlist->index--];
}

void cl_update(struct CustomList * customlist, struct ListItem * listitem, unsigned int v_index) {
	if (v_index > customlist->index || v_index < 0)
		IndexOutOfBoundsError(v_index,customlist->index+1,__LINE__,__FILE__);
	customlist->list[v_index]=listitem;
}

void cl_insert(struct CustomList * customlist, struct ListItem * listitem, unsigned int v_index) {
	if (v_index > customlist->index || v_index < 0)
		IndexOutOfBoundsError(v_index,customlist->index+1,__LINE__,__FILE__);
	if (cl_is_full(customlist))
		cl_realloc_list(customlist);

	unsigned int tmp_index = customlist->index;
	customlist->index++;
	while (tmp_index >= v_index && tmp_index != 4294967295) {
		customlist->list[tmp_index+1] = customlist->list[tmp_index];
		tmp_index--;
	}
	customlist->list[v_index]=listitem;
}

struct ListItem * cl_remove(struct CustomList * customlist, unsigned int v_index) {
	if (v_index > customlist->index || v_index < 0)
		IndexOutOfBoundsError(v_index,customlist->index+1,__LINE__,__FILE__);
	if (cl_is_empty(customlist))
		EmptyListError(__LINE__,__FILE__);

	struct ListItem * tmp_list_item = customlist->list[v_index];

	while (v_index < customlist->index) {
		customlist->list[v_index] = customlist->list[v_index+1];
		v_index++;
	}
	customlist->index--;
	return tmp_list_item;
}

void cl_print_list(struct CustomList * customlist) {
	printf("list_open_brackets ");
	for (int i = 0; i <= customlist->index; i++) {
		print_list_item(cl_get_item(customlist,i));
		if (i > 0 && i%100==0) printf("\n");
		else printf(" ");

	}
	printf("list_close_brackets\n");
}


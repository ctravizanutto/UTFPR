/* ------------------------------------------------
Cainan Travizanutto && Gabriel Maestre - 2022;
#ifndef graduated
#define project_1_data_structures_lab;
#endif

------------------- QUICK INFOS -------------------
All static functions are meant to be used internally, thus the _prefix format
If user calls function with wrong parameters the function will only return and don't display any errors
This is not meant to be used in production, only for study purpose
--------------------- SUMMARY ---------------------
3x structs
5x simple linked list
6x header simple linked list
7x implementation
eof license
*/


#ifndef _PROJECT1_H
#define _PROJECT1_H

#ifndef _BOOL
    typedef enum { false, true, } bool;
#endif

#ifndef _STDIO_H
    #include <stdio.h>
#endif

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

#include <stdarg.h>

// Holds a data data of int type and a struct pointer to the next element in the list
typedef struct simple_node {
    int data;
    struct simple_node *next;
} node;

// Holds list size and a struct pointer to first element of the list
typedef struct head_node {
    int size;
    struct simple_node *next;
} h_node;

// Holds a data data of int type and two struct pointers, one to the next element in the list and one to the prior
typedef struct doubly_node {
    int data;
    struct doubly_node *next;
    struct doubly_node *prev;
} d_node;

//////////////////// SIMPLE LINKED LIST ////////////////////
node *node_create_list(int data); // Only takes a data and returns a pointer to the node
node *node_split_list(node **list, int node_pos_data); // Returns a pointer to a new list, and removes the old list pointer to node
void node_insert(node *list, int data, bool in_order, ...); // Insert node with data, if in_order true its put at the end or before a greater number,
// else it takes a pos by node data and inserts afert
void node_remove(node **list, bool delete_all, ...);
void node_print_list(node *list);


//////////////////// HEADER SIMPLE LINKED LIST ////////////////////
h_node *h_node_create_list();
void h_node_insert(node *header, int data, bool in_order, int node_pos_data);
void h_node_remove(node **header, bool delete_all, int node_pos_data);
void h_node_print_list(node *header);
h_node *h_node_split_list(node **header, int node_pos_data);

//////////////////// CIRCULAR LINKED LIST ////////////////////

//////////////////// DOUBLY LINKED LIST ////////////////////

/*
---------------------------------------
        IMPLEMENTATION
*/
node *node_create_list(int data)
{
    node *tmp = (node*) malloc(sizeof(node));
    if (tmp == NULL) exit(1);
    tmp->data = data;
    tmp->next = NULL;
    return tmp;
}

static void _node_insert_order(node *list, int data)
{
    if (list == NULL) return;
    node *tmp = (node*) malloc(sizeof(node));
    if (tmp == NULL) exit(1);
    tmp->data = data;

    while (list->data <= data && list->next != NULL)
        list = list->next;
    
    if (list->data >= data) {
        tmp->data = list->data;
        tmp->next = list->next;
        list->data = data;
        list->next = tmp;
        return;
    }
    tmp->next = list->next;
    list->next = tmp;

}

static void _node_insert_pos(node *list, int data, int node_pos_data)
{
    if (list == NULL) return;
    while (list->data != node_pos_data) {
        if (list->next == NULL) return;
        list = list->next;
    }
    node *tmp = (node*) malloc(sizeof(node));
    if (tmp == NULL) exit(1);
    tmp->data = data;
    tmp->next = list->next;
    list->next = tmp;
}

void node_insert(node *list, int data, bool in_order, ...)
{
    if (in_order) {
        _node_insert_order(list, data);
        return;
    }
    va_list arg;
    va_start(arg, in_order);
    int node_pos_data = va_arg(arg, int);
    _node_insert_pos(list, data, node_pos_data);
    va_end(arg);
}

void print_list(node *list)
{
    if (list == NULL) return;
    while (list != NULL)
    {
        printf("%d\n", list->data);
        list = list->next;
    }
    printf("\n");
}

static void _node_remove_all(node *list)
{
   if (list == NULL) return;

    _node_remove_all(list->next);
    list->next = NULL;
    free(list);
   
}

static void _node_remove_pos(node **list, int node_pos_data) 
{
    if (*list == NULL) return;
    node *tmp = *list;
    if (tmp->data == node_pos_data) { // case the node to remove its the first on list
            *list = tmp->next;
            free(tmp);
            return;
    }
    
    while (tmp != NULL) {
        if (tmp->next->data == node_pos_data) {
            node *tmp_remove = tmp->next;
            tmp->next = tmp->next->next;
            free(tmp_remove);
            return;
        }
        tmp = tmp->next;
    }
}

void node_remove(node **list, bool delete_all, ...)
{
    if (delete_all) {
        _node_remove_all(*list);
        return;
    }
    va_list arg;
    va_start(arg, delete_all);
    int node_pos_data = va_arg(arg, int);
    _node_remove_pos(list, node_pos_data);
    va_end(arg);
}

node *node_split_list(node **list, int node_pos_data)
{
    if (*list == NULL) return NULL;
    node *tmp = *list;
    if (tmp->data == node_pos_data) { // case pos is the first element
        *list = NULL;
        return tmp;
    }
    while (tmp != NULL) {
        if (tmp->next->data == node_pos_data) {
            node *tmp_return = tmp->next;
            tmp->next = NULL;
            return tmp_return;
        }
        tmp = tmp->next;
    }
    return NULL;
}



#endif // _PROJECT1_H

/*
---------------------------- PUBLIC DOMAIN ----------------------------
This is free and unencumbered software released into the public domain.
-----------------------------------------------------------------------
Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/
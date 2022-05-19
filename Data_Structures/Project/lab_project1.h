/* ----------------------------------------------
Cainan Travizanutto && Gabriel Maestre - 2022;
#ifndef graduated
#define project_1_data_structures_lab;
#endif

------------------ QUICK INFO -------------------
This is not meant to be used in production, only for study purpose
All static functions are meant to be used internally, thus the _prefix format
If user calls function with wrong parameters the function will only return and don't display any errors
Functions {
create list: returns a struct with a value data
insert: takes a list pointer, a int value data, a bool, which if true inserts before a number greater, 
        else if false after the data provide to localize a node else at the very end;
remove: takes a pointer to a list pointer and a bool, which if true removes all nodes, else a specific one
print: it prints ¯\_(ツ)_/¯
split: takes a list and a value data, remove the prior node connection and returns a new list pointer with the 
        remaining nodes
}

-------------------- SUMMARY --------------------
48 structs
66 simpl linked list
6x head simple linked list
7x implementation
EOF license
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
struct simple_node *first;
} h_node;

// Holds a data data of int type and two struct pointers, one to the next element in the list and one to the prior
typedef struct doubly_node {
int data;
struct doubly_node *next;
struct doubly_node *prev;
} d_node;

//------------------------------ SIMPLE LINKED LIST ------------------------------//
node *node_create_list(int data);
node *node_split_list(node **list, int node_pos_data);
void node_insert(node *list, int data, bool in_order, ...);
void node_remove(node **list, bool delete_all, ...);
void node_print_list(node *list);

//------------------------- SIMPLE LINKED LIST WITH HEAD -------------------------//
h_node *h_node_create_list(int data);
h_node *h_node_split_list(h_node **head, int node_pos_data);
void h_node_insert(h_node *head, int data, bool in_order, ...);
void h_node_remove(h_node **head, bool delete_all, ...);
void h_print_list(h_node *head);

//----------------------------- CIRCULAR LINKED LIST -----------------------------//
node *c_node_create_list(int data);
node *c_node_split_list(node **list, int node_pos_data);
void c_node_insert(node *list, int data, bool in_order, ...);
void c_node_remove(node **list, bool delete_all, ...);
void d_node_print_list(node *list);

//----------------------------- DOUBLY LINKED LIST --------------------------------//
node *d_node_create_list(int data);
node *d_node_split_list(node **list, int node_pos_data);
void d_node_insert(node *list, int data, bool in_order, ...);
void d_node_remove(node **list, bool delete_all, ...);
void d_node_print_list(node *list);





//------------------------------ IMPLEMENTATION ------------------------------//

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
        tmp = list;
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


static int _h_node_list_size(h_node *head)
{
    int i = 0;
    node *list = head->first;
    while (list != NULL) {
        i++;
        list = list->next;
    }
    return i;
}

h_node *h_node_create_list(int data) 
{
    h_node *tmp = (h_node*) malloc(sizeof(h_node));
    if (tmp == NULL) exit(1);
    tmp->size = 1;
    tmp->first = node_create_list(data);
    return tmp;
}

void h_node_insert(h_node *head, int data, bool in_order, ...)
{
    if (in_order) {
        _node_insert_order(head->first, data);
        head->size = _h_node_list_size(head);
        return;
    }
    va_list arg;
    va_start(arg, in_order);
    int node_pos_data = va_arg(arg, int);
    _node_insert_pos(head->first, data, node_pos_data);
    va_end(arg);
    head->size = _h_node_list_size(head);
}

void h_node_remove(h_node **head, bool delete_all, ...)
{
    if (delete_all) {
        _node_remove_all((*head)->first);
        (*head)-> size = _h_node_list_size(*head);
        return;
    }
    va_list arg;
    va_start(arg, delete_all);
    int node_pos_data = va_arg(arg, int);
    _node_remove_pos(&(*head)->first, node_pos_data);
    va_end(arg);
    (*head)->size = _h_node_list_size(*head);
}

void h_print_list(h_node *head)
{
    if (head == NULL) return;
    print_list(head->first);
    printf("List total size: %i\n", head->size);
}

h_node *h_node_split_list(h_node **head, int node_pos_data)
{
    if (*head == NULL) return NULL;
    h_node *head2 = (h_node*) malloc(sizeof(h_node));
    node *tmp = (*head)->first;
    if (tmp->data == node_pos_data) { // case pos is the first element
        *head = NULL;
        head2->first = tmp;
        head2->size = _h_node_list_size(head2);
        (*head)->size = _h_node_list_size(*head);
        return head2;
    }
    while (tmp != NULL) {
        if (tmp->next->data == node_pos_data) {
            node *tmp_return = tmp->next;
            tmp->next = NULL;
            head2->first = tmp_return;
            head2->size = _h_node_list_size(head2);
            (*head)->size = _h_node_list_size(*head);
            return head2;
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
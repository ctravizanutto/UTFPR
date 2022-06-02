/* ----------------------------------------------
Cainan Travizanutto && Gabriel Maestre - 2022;
#ifndef data_structs_assignment_done
#define project_1_data_structures_lab
#endif

------------------ QUICK INFO -------------------
This is not meant to be used in production, only for study purpose
All static functions are meant to be used internally, thus the _prefix format
If user calls function with wrong parameters the function will either return and don't display any errors
        or behave improperly
Functions { TODO
create list: 
insert: 
remove: takes a pointer to a list pointer and a bool, which if true removes all nodes, else a specific one
print: it prints ¯\_(ツ)_/¯
split: 
}

-------------------- SUMMARY --------------------
TODO
*/
#ifndef _PROJECT1_H
#define _PROJECT1_H

#ifndef _BOOL
typedef enum{ false, true } bool;
#endif

#include <stdio.h>
#include <stdlib.h>
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

void node_create_list(int data, node** list);
void node_split_list(node** list_split_from, node** list_split_to, int node_pos_data);
void node_insert(node *list, int data, bool in_order, ...);
void node_remove(node **list, bool delete_all, ...);
void node_print_list(node *list);


//------------------------- SIMPLE LINKED LIST WITH HEAD -------------------------//

void h_node_create_list(int data, h_node **list);
void h_node_split_list(h_node** head_split_from, h_node** head_split_to, int node_pos_data);
void h_node_insert(h_node *head, int data, bool in_order, ...);
void h_node_remove(h_node **head, bool delete_all, ...);
void h_node_print_list(h_node *head);


//----------------------------- CIRCULAR LINKED LIST -----------------------------//

void c_node_create_list(node **list, int data);
void c_node_split_list(node **list, int node_post_data);
void c_node_insert(node *list, int data, bool in_order, ...);
void c_node_remove(node **list, bool delete_all, ...);
void c_node_print_list(node* list);


//----------------------------- DOUBLY LINKED LIST --------------------------------//

void d_node_create_list(int data, d_node** list);
void d_node_split_list(d_node** list_split_from, d_node** list_split_to, int node_pos_data);
void d_node_insert(d_node *list, int data, bool in_order, ...);
void d_node_remove(d_node **list, bool delete_all, ...);
void d_node_print_list(d_node *list);


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
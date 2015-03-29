/*
 *  Autor: Andrei Macavei
 *  Grupa: 334 CB
*/

#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

/*
 *  Structure that represents a node in a singly linked list
 */
typedef struct ListNode_ {
    char *word;
    struct ListNode_ *next;
} ListNode;

/*
 * Structure that represents a singly linked list
 */
typedef struct List_ {
    ListNode *head, *tail;
} List;

/*
 *  Function that initializes the list with a sentinel node
 */
void list_init(List *list);

/*
 *  Function that adds a new element to the list
 */
void list_add(List *list, char *word);

/*
 *  Function that removes an element from the list
 */
void list_remove(List *list, char *word);

/*
 *  Function that removes all elements from a list
 */
void list_clear(List *list);

/*
 *  Function that finds an element in a list
 */
int list_find(List *list, char *word);

/*
 *  Function that prints all the elements of the list
 */
void list_print(List *list, FILE *output);

#endif

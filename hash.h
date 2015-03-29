/*
 *  Autor: Andrei Macavei
 *  Grupa: 334 CB
*/

#ifndef HASH_H_
#define HASH_H_

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*
 *  Structure that represents a hash table
 */
typedef struct HashTable_ {
    List *buckets;
    unsigned int size;
} HashTable;

/*
 *  Function that computes the hashcode of a string
 */
unsigned int hash(const char *str, unsigned int hash_length);

/*
 *  Function that initialize a hash hable
 */
void table_init(HashTable *t, unsigned int size);

/*
 *  Function that adds a new word in a hash table
 */
void table_add(HashTable *t, char *word);

/*
 *  Function that removes a word from a hash table
 */
void table_remove(HashTable *t, char *word);

/*
 *  Function that checks if hash table contains a word
 */
int table_find(HashTable *t, char *word);

/*
 *  Function that removes all the elements in a hash table
 */
void table_clear(HashTable *t);

/*
 *  Function that prints a bucket of a hash table
 */
void table_print_bucket(HashTable *t, int index, FILE *out);

/*
 *  Function that prints every bucket in a hash table on a new line
 */
void table_print(HashTable *t, FILE *out);

/*
 *  Function that frees all the allocates resources for a hash table
 */
void table_free(HashTable *t);

/*
 *  Function that resizes a hash table by creating a new one
 *  and copying all the elements.
 */
HashTable table_resize(HashTable *t, unsigned int size);


#endif

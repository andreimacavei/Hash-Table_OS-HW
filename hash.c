/*
 *  Autor: Andrei Macavei
 *  Grupa: 334 CB
*/

#include "hash.h"

/**
 * Functie de i bazata pe djb2 a lui Dan Bernstein
 * http://www.cse.yorku.ca/~oz/i.html
 * @return valoarea de dispersie (cheia)
 */
unsigned int hash(const char *str, unsigned int hash_length)
{
    unsigned int i = 5381;
    int c;

    while ((c = *str++) != 0)
        /* i * 33 + c */
        i = ((i << 5) + i) + c;

    return (i % hash_length);
}

void table_init(HashTable *t, unsigned int size)
{
    unsigned int i;

    t->buckets = (List *)malloc(size * sizeof(List));
    DIE(t->buckets == NULL, "table_init");
    t->size = size;

    for (i = 0; i < size; i++)
        list_init(&t->buckets[i]);
}

void table_add(HashTable *t, char *word)
{
    List *list = t->buckets;
    unsigned int i = hash(word, t->size);
    int r;

    if (strcmp(word, "") == 0)
        return;

    r = list_find(&list[i], word);
    if (r == 0)
        list_add(&list[i], word);
}

void table_remove(HashTable *t, char *word)
{
    List *list = t->buckets;
    unsigned int i;

    i = hash(word, t->size);
    list_remove(&list[i], word);
}

int table_find(HashTable *t, char *word)
{
    List *list = t->buckets;
    unsigned int i, r;

    i = hash(word, t->size);
    r = list_find(&list[i], word);

    return r;
}

void table_clear(HashTable *t)
{
    List *list = t->buckets;
    unsigned int i;

    for (i = 0; i < t->size; i++)
        list_clear(&list[i]);
}

void table_print_bucket(HashTable *t, int index, FILE *out)
{
    List *list = t->buckets;

    DIE(index >= t->size, "table_print_bucket invalid index");
    list_print(&list[index], out);
    if (list[index].head->next != NULL)
        fprintf(out, "\n");
}

void table_print(HashTable *t, FILE *out)
{
    List *list = t->buckets;
    unsigned int i;

    for (i = 0; i < t->size; i++) {
        list_print(&list[i], out);

        if (list[i].head->next != NULL)
            fprintf(out, "\n");
    }

}

void table_free(HashTable *t)
{
    List *list = NULL;
    unsigned int i;

    table_clear(t);
    for (i = 0; i < t->size; i++) {
        list = &t->buckets[i];
        free(list->head);
        list->head = list->tail = NULL;

    }
    free(t->buckets);
}

HashTable table_resize(HashTable *t, unsigned int size)
{
    HashTable rt;
    ListNode *n;
    unsigned int i;

    table_init(&rt, size);

    for (i = 0; i < t->size; i++) {
        n = t->buckets[i].head->next;
        while (n != NULL) {
            table_add(&rt, n->word);
            n = n->next;
        }
    }
    table_free(t);

    return rt;
}


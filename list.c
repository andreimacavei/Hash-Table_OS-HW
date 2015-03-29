/*
 *  Autor: Andrei Macavei
 *  Grupa: 334 CB
*/

#include "list.h"


void list_init(List *list)
{
    list->head = (ListNode *)malloc(sizeof(ListNode));

    DIE(list->head == NULL, "list_init malloc");
    list->head->word = NULL;
    list->head->next = NULL;
    list->tail = list->head;
}

void list_add(List *list, char *word)
{
    unsigned int length = strlen(word);
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));

    DIE(node == NULL, "list_add malloc");
    node->word = (char *)malloc((length+1) * sizeof(char));
    DIE(node->word == NULL, "list_add malloc");

    strcpy(node->word, word);
    node->next = NULL;

    list->tail->next = node;
    list->tail = list->tail->next;
}

void list_remove(List *list, char *word)
{
    ListNode *prev = list->head, *curr = list->head->next;

    while (curr != NULL) {
        if (strcmp(word, curr->word) == 0) {
            prev->next = curr->next;

            if (curr == list->tail)
                list->tail = prev;

            free(curr->word);
            free(curr);
            break;
        }

        prev = curr;
        curr = curr->next;
    }
}

int list_find(List *list, char *word)
{
    ListNode *node = list->head->next;
    int res = 0;

    while (node != NULL) {
        if (strcmp(word, node->word) == 0) {
            res = 1;
            break;
        }
        node = node->next;
    }
    return res;
}

void list_clear(List *list)
{
    ListNode *aux, *node = list->head->next;

    while (node != NULL) {
        aux = node;
        node = node->next;
        free(aux->word);
        free(aux);
    }
    list->head->next = NULL;
    list->tail = list->head;
}

void list_print(List *list, FILE *output)
{
    ListNode *node = list->head->next;

    while (node != NULL) {
        fprintf(output, "%s ", node->word);
        node = node->next;
    }
}

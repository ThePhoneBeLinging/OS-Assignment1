
/* You are not allowed to use <stdio.h> */
#include "io.h"
#include "mm.h"
#include <stdlib.h>

typedef struct value {
    int val;
    struct value *next;
    struct value *prev;
} value;

typedef struct Collection {
    value *head;
    value *tail;
    int count;
} Collection;

void freeCollection(Collection *collection) {
    value *current;
    while (collection->head != NULL) {
        current = collection->head;
        collection->head = collection->head->next;
        simple_free(current);
    }
    simple_free(collection);
}

/**
 * @name  main
 * @brief This function is the entry point to your program
 * @return 0 for success, anything else for failure
 *
 *
 * Then it has a place for you to implementation the command 
 * interpreter as  specified in the handout.
 */
int main()
{
    char c;
    Collection *collection = simple_malloc(sizeof(Collection));
    collection->head = NULL;
    collection->tail = NULL;
    collection->count = 0;

    while (1)
    {
        c = read_char();

        switch (c)
        {
            case 'a':
                {
                    value *newVal = simple_malloc(sizeof(value));
                    newVal->val = collection->count;
                    newVal->next = NULL;

                    if (collection->head == NULL) {
                        collection->head = newVal;
                        collection->tail = newVal;
                    } else {
                        newVal->prev = collection->tail;
                        collection->tail->next = newVal;
                        collection->tail = newVal;
                    }
                    collection->count++;
                    continue;
                }
            case 'b':
                {
                    collection->count++;
                    continue;
                }
            case 'c':
                {
                    if (collection->tail != NULL) {
                        if (collection->tail == collection->head) {
                            simple_free(collection->tail);
                            collection->head = NULL;
                            collection->tail = NULL;
                        } else {
                            value *temp = collection->tail;
                            collection->tail = collection->tail->prev;
                            collection->tail->next = NULL;
                            simple_free(temp);
                        }
                    }
                    collection->count++;
                    continue;
                }
                default:
                {
                    break;
                }
        }
        break;
    }

    while (c != '\n' && c != EOF)
    {
        c = read_char(); 
    }

    value *temp = collection->head;
    while (temp != NULL)
    {
        write_int(temp->val);
        if (temp->next != NULL)
        {
            write_char(',');
        }
        temp = temp->next;
    }
    write_char(';');
    write_char('\n');

    freeCollection(collection);
    return 0;
}

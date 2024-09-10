
/* You are not allowed to use <stdio.h> */
#include "io.h"
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
        free(current);
    }
    free(collection);
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
int
main()
{
    char c;
    Collection *collection = malloc(sizeof(Collection));
    collection->head = NULL;
    collection->tail = NULL;
    collection->count = 0;

    while (1) {
        c = read_char();

        switch (c)
        {
            case 'a':
                {
                    value *newVal = malloc(sizeof(value));
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
                            free(collection->tail);
                            collection->head = NULL;
                            collection->tail = NULL;
                        } else {
                            value *temp = collection->tail;
                            collection->tail = collection->tail->prev;
                            collection->tail->next = NULL;
                            free(temp);
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

    value *temp = collection->head;
    while (temp != NULL) {
        write_int(temp->val);
        if (temp->next != NULL) {
            write_char(',');
        }
        temp = temp->next;
    }
    write_char(';');
    write_char('\n');

    freeCollection(collection);
  /*-----------------------------------------------------------------
   *TODO:  You need to implement the command line driver here as
   *       specified in the assignment handout.
   *
   * The following pseudo code describes what you need to do
   *  
   *  Declare the counter and the collection structure variables
   *
   *
   *  In a loop
   *    1) Read a command from standard in using read_char function
   *    2) If the command is not 'a', 'b', 'c': then break the loop
   *    3) Process the command as specified in the handout
   *  End loop
   *
   *  Print your collection of elements as specified in the handout
   *    as a comma delimited series of integers
   *-----------------------------------------------------------------*/

  return 0;
}

/**
 * @file   mm.c
 * @Author 02335 team
 * @date   September, 2024
 * @brief  Memory management skeleton.
 *
 */

#include <stdint.h>

#include "mm.h"


/* Proposed data structure elements */

typedef struct header {
    struct header *next;     // Bit 0 is used to indicate free block
    uint64_t user_block[0];   // Standard trick: Empty array to make sure start of user block is aligned
} BlockHeader;

/* Macros to handle the free flag at bit 0 of the next pointer of header pointed at by p */
#define GET_NEXT(p)    (void *) (((uintptr_t) p->next) & ~1)    /* NOT DONE TODO: Mask out free flag */
#define SET_NEXT(p, n)  p->next = (void *)(((uintptr_t)(n) & ~1) | ((uintptr_t)GET_FREE(p))) /* TODO: Preserve free flag */
#define GET_FREE(p)    (uint8_t) ( (uintptr_t) (p->next) & 0x1 )   /* OK -- do not change */
#define SET_FREE(p, f) p->next = (void *)(((uintptr_t)GET_NEXT(p) & ~1) | ((uintptr_t)(f & 1)))
#define SIZE(p) (size_t) ((uintptr_t)GET_NEXT(p) - (uintptr_t)p - sizeof(BlockHeader)) /* MAYBE DONE TODO: Calc size of block from p and p->next */

#define MIN_SIZE     (8)   // A block should have at least 8 bytes available for the user


static BlockHeader *first = NULL;
static BlockHeader *current = NULL;

/**
 * @name    simple_init
 * @brief   Initialize the block structure within the available memory
 *
 */
void simple_init() {
    uintptr_t aligned_memory_start = memory_start + (memory_start % 64);
    uintptr_t aligned_memory_end = memory_end - (memory_end % 64);
    BlockHeader *last;

    /* Already initalized ? */
    if (first == NULL) {
        /* Check that we have room for at least one free block and an end header */
        if (aligned_memory_start + 2 * sizeof(BlockHeader) + MIN_SIZE <= aligned_memory_end) {
            first = (BlockHeader *) aligned_memory_start;
            last = (BlockHeader *) aligned_memory_end;
            SET_FREE(first, 1);
            SET_NEXT(first, last);
            SET_NEXT(last, first);
            SET_FREE(last, 1);
            current = first;
        }
    }
}


/**
 * @name    simple_malloc
 * @brief   Allocate at least size contiguous bytes of memory and return a pointer to the first byte.
 *
 * This function should behave similar to a normal malloc implementation.
 *
 * @param size_t size Number of bytes to allocate.
 * @retval Pointer to the start of the allocated memory or NULL if not possible.
 *
 */
void *simple_malloc(size_t size) {
    // Initialize memory system if not already initialized
    if (first == NULL) {
        simple_init();
        if (first == NULL) return NULL;
    }

    size_t aligned_size = (size + 7) & ~7;

    // Search for a free block starting from 'current'
    BlockHeader *startSearch = current;
    do {
        // Check if the current block is free
        if (GET_FREE(current)) {

            if (SIZE(current) >= aligned_size) {
                if (SIZE(current) - aligned_size >= sizeof(BlockHeader) + MIN_SIZE) {
                    BlockHeader *newBlock = (BlockHeader *) ((uintptr_t)current + sizeof(BlockHeader) + aligned_size);
                    SET_NEXT(newBlock, GET_NEXT(current));
                    SET_NEXT(current, newBlock);
                    SET_FREE(current, 0);
                    SET_FREE(newBlock, 1);

                } else {
                    SET_FREE(current, 0);
                }

                void *currentAddress = (void *)((uintptr_t)current + sizeof(BlockHeader));

                current = GET_NEXT(current);

                return currentAddress;
            }
        }

        current = GET_NEXT(current);
    } while (current != startSearch);

    return NULL;
}



/**
 * @name    simple_free
 * @brief   Frees previously allocated memory and makes it available for subsequent calls to simple_malloc
 *
 * This function should behave similar to a normal free implementation.
 *
 * @param void *ptr Pointer to the memory to free.
 *
 */
void simple_free(void *ptr) {
    BlockHeader *block = (BlockHeader *) ((uintptr_t) ptr - sizeof(BlockHeader));

    if (GET_FREE(block)) {
        // Block is not in use -- probably an error
        return;
    }

    BlockHeader* tempBlock = first;

    while (GET_NEXT(tempBlock) != block)
    {
        tempBlock = GET_NEXT(tempBlock);
    }
    tempBlock->next = GET_NEXT(block);
}

/* Include test routines */

#include "mm_aux.c"

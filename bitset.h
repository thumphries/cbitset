/**
 * Simple bitset, via the C-FAQ (http://c-faq.com/misc/bitsets.html)
 */

#ifndef CBITSET_H
#define CBITSET_H

#include <limits.h>		/* for CHAR_BIT */

#ifndef CHAR_BIT
#define CHAR_BIT (8)
#endif

#define BITMASK(b)     (1 << ((b) % CHAR_BIT))
#define BITSLOT(b)     ((b) / CHAR_BIT)
#define BITSET(a, b)   ((a)[BITSLOT(b)] |= BITMASK(b))
#define BITCLEAR(a, b) ((a)[BITSLOT(b)] &= ~BITMASK(b))
#define BITTEST(a, b)  ((a)[BITSLOT(b)] & BITMASK(b))
#define BITNSLOTS(nb)  ((nb + CHAR_BIT - 1) / CHAR_BIT)
#define BITNSIZE(nb)   (CHAR_BIT * BITNSLOTS(nb))

#define BITSET_SUCCESS (0)
#define BITSET_ERROR   (1)

typedef struct bitset {
    char *bs;
    unsigned int size;
} bitset;

int bitset_alloc(bitset** bs, unsigned int size);

int bitset_init(bitset *bs, unsigned int size);

int bitset_free(bitset *bs);

int bitset_test(bitset *bs, unsigned int bit);

int bitset_set(bitset *bs, unsigned int bit);

int bitset_clear(bitset *bs, unsigned int bit);

int bitset_toggle(bitset *bs, unsigned int bit);

/*
    Here are some usage examples. To declare an ``array'' of 47 bits:
     
            char bitarray[BITNSLOTS(47)];

    To set the 23rd bit:
            BITSET(bitarray, 23);

    To test the 35th bit:
            if(BITTEST(bitarray, 35)) ...

    To compute the union of two bit arrays and place it in a third
    array (with all three arrays declared as above):

            for(i = 0; i < BITNSLOTS(47); i++)
            	array3[i] = array1[i] | array2[i];
*/

#endif // CBITSET_H

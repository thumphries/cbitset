
#include <stdio.h>
#include "bitset.h"

#define BITS 1024

int main (int argc, char **argv) {
    int err;
    bitset *bs;
    int i;

    err = bitset_alloc(&bs, BITS);
    if (err) {
        printf("bitset_alloc failed!\n");
        return 1;
    }

    for(i = 0; i < BITS; i++) {
        err = bitset_set(bs, i);
        if (err) {
            printf("bitset_set failed for bit %d (size %d)\n", i, bs->size);
            return 1;
        }
    }

    for(i = 0; i < BITS; i++) {
        err = bitset_test(bs, i);
        if (!err) {
            printf("bit %d was cleared somehow\n", i);
            return 1;
        }
        err = bitset_toggle(bs, i);
        if (err) {
            printf("Failed to toggle bit %d\n");
            return 1;
        }
        err = bitset_clear(bs, i);
        if (err) {
            printf("Failed to clear bit %d\n");
            return 1;
        }
        if (bitset_test(bs, i)) {
            printf("cleared bit %d tested positive...\n", i);
            return 1;
        }
    }

    return (bitset_free(bs));
}

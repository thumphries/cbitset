
#include <stdlib.h>
#include <strings.h>
#include "bitset.h"

int bitset_alloc(bitset** bs, unsigned int size) {
    (*bs) = malloc(sizeof(struct bitset));
    if (*bs == NULL) return BITSET_ERROR;
    ((*bs)->bs) = malloc(BITNSIZE(size));

    if ((*bs)->bs == NULL) {
        free((*bs));
        return BITSET_ERROR;
    } else {
        return bitset_init((*bs), size);
    }
}

int bitset_init(bitset *bs, unsigned int size) {
    if (bs == NULL) return -BITSET_ERROR;
    bs->size = size;
    bzero((void *) bs->bs, BITNSIZE(size));
    return BITSET_SUCCESS;
}

int bitset_free(bitset *bs) {
    if (bs == NULL || bs->bs == NULL) return -BITSET_ERROR;
    free(bs->bs);
    free(bs);
    return BITSET_SUCCESS;
}

int bitset_test(bitset *bs, unsigned int bit) {
    if (bs == NULL || bit >= bs->size) return -BITSET_ERROR;
    return BITTEST((bs->bs), bit);
}

int bitset_set(bitset *bs, unsigned int bit) {
    if (bs == NULL || bit >= bs->size) return -BITSET_ERROR;
    BITSET((bs->bs), bit);
    return BITSET_SUCCESS;
}

int bitset_clear(bitset *bs, unsigned int bit) {
    if (bs == NULL || bit >= bs->size) return -BITSET_ERROR;
    BITCLEAR((bs->bs), bit);
    return BITSET_SUCCESS;
}

int bitset_toggle(bitset *bs, unsigned int bit) {
    if (bs == NULL || bit >= bs->size) return -BITSET_ERROR;
    if (bitset_test(bs, bit) > 0) {
        return bitset_clear(bs, bit);
    } else {
        return bitset_set(bs, bit);
    }
}

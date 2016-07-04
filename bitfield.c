#include <string.h>
#include <stdio.h>

#include "bitfield.h"
#include "memory.h"


uint8_t bitfield_is_bit_set(bitfield *field, uint64_t bitPos) {
    uint64_t offset = bitPos / 64;
    uint64_t offPos = bitPos % 64;

    uint64_t mask = 1;
    mask <<= offPos;

    printf("offset %llu pos %llu mask %llu 0x%016llx p[offset] 0x%016llx\n", offset, offPos, mask, mask, field->p[offset]);
    printf("masked %llu\n", field->p[offset] & mask);
    
    if(0 == (field->p[offset] & mask)) {
        return 0;
    }
    return 1; 
}

void bitfield_set_bit(bitfield *field, uint64_t bitPos) {
    uint64_t offset = bitPos / 64;
    uint64_t offPos = bitPos % 64;

    uint64_t mask = 1;
    mask <<= offPos;

    field->p[offset] |= mask;

    printf("setbit %llu 0x%016llx\n", field->p[offset], field->p[offset]);
}

void bitfield_unset_bit(bitfield *field, uint64_t bitPos) {
    uint64_t offset = bitPos / 64;
    uint64_t offPos = bitPos % 64;

    uint64_t mask = -1; // 0xff...
    mask <<= 1; // set 0

    for(uint64_t i = 0; i < offPos; i++) { // to 0 offPos-1 positions
        mask <<= 1;
        mask++;
    }

    printf("mask done   0x%016llx\n", mask);

    field->p[offset] &= mask;

    printf("field after mask 0x%016llx\n", field->p[offset]);
}

uint64_t bitfield_next_free_bit(bitfield *field) {
    uint64_t offset = 0;
    uint64_t offPos = 0;
    uint8_t  mask   = 1;

    for(; offset < field->n; offset++) {
        uint64_t data = field->p[offset];

        for(offPos = 0; offPos < 64; offPos++) {
            uint8_t res = mask & data;

            if (res == 0) {
                return offset * 64 + offPos;
            }
            data >>= 1;
        }
    }

    return (mask-2); // 0xff...
}

bitfield* bitfield_new(uint64_t bytes) {
    bitfield *p = malloc(sizeof(bitfield));

    p->n = bytes / 8;
    p->p = memalloc(bytes);
    memset(p->p, 0, bytes);

    return p;
}

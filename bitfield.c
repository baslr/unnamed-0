#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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

bitfield* bitfield_new(uint64_t size) {
    bitfield *p = malloc(sizeof(bitfield));

    p->n = size;
    p->p = memalloc(size);
    memset(p->p, 0, size);

    return p;
}

#ifndef _BITFIELD_H_
#define _BITFIELD_H_

#include <stdlib.h>

struct struct_bitfield {
    uint64_t *p;
    uint64_t n;
};

typedef struct struct_bitfield bitfield; 

uint8_t  bitfield_is_bit_set(bitfield *field, uint64_t bitPos);
void     bitfield_set_bit(bitfield *field, uint64_t bitPos);
void     bitfield_unset_bit(bitfield *field, uint64_t bitPos);
uint64_t bitfield_next_free_bit(bitfield *field);

bitfield* bitfield_new(uint64_t bytes); // bytes should be multiple of 8 eg. 8, 16, 24

#endif

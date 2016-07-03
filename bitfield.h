#ifndef _BITFIELD_H_
#define _BITFIELD_H_


#include <stdint.h>

struct struct_bitfield {
    uint64_t *p;
    uint64_t n;
};

typedef struct struct_bitfield bitfield; 

uint8_t bitfield_is_bit_set(bitfield *field, uint64_t bitPos);
void    bitfield_set_bit(bitfield *field, uint64_t bitPos);

bitfield* bitfield_new(uint64_t size); // size multiple of 8

#endif

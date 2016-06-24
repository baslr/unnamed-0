#ifndef _H_MEMORY
#define  _H_MEMORY

#include <stdlib.h>

void* memalloc(uint64_t length);
void  memfree(void *p);

#endif
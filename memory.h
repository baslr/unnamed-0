#ifndef _H_MEMORY
#define  _H_MEMORY

#include <stdlib.h>

void* memalloc(uint64_t length);
void* memrealloc(void* pCurrent, uint64_t oldLenght, uint64_t newLength);
void  memfree(void *p);

#endif
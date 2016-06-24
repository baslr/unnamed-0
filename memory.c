#include <stdio.h>
#include "memory.h"



void* memalloc(uint64_t length) {

  void *p;

  #if __APPLE__
    if (posix_memalign(&p, 64, length)) {
        printf("mem allocation failed %lld bytes\n", length);
        p = NULL;
    } // if
  #endif

  #if __LINUX__
    p = aligned_alloc (64, length);
    if (p == NULL) {
      printf("mem allocation failed %lld bytes\n", length);
    }
  #endif


  printf("content 0x%016llx\n", (uint64_t)p);
  printf("address 0x%016llx\n", (uint64_t)&p);
  

  return p;
}


void memfree(void *p) {
  free(p);
}
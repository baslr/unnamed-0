#include <stdio.h>
#include <string.h>
#include "memory.h"

/*

always allocate aligned memory

*/

void* memalloc(uint64_t length) {

  void *p;

  #if __APPLE__
    if (posix_memalign(&p, 64, length)) {
        printf("mem allocation failed %llu bytes\n", length);
        p = NULL;
    } // if
  #endif

  #if __LINUX__
    p = aligned_alloc (64, length);
    if (p == NULL) {
      printf("mem allocation failed %llu bytes\n", length);
    }
  #endif


  printf("content 0x%016llx\n", (uint64_t)p);
  printf("address 0x%016llx\n", (uint64_t)&p);
  

  return p;
}

void* memrealloc(void* p, uint64_t old, uint64_t length) {
  void *pNew = memalloc(length);

  if (pNew == NULL) {
    printf("memrealloc failed %llu bytes\n", length);
  }

  // Copies n characters from str2 to str1. If str1 and str2 overlap the behavior is undefined.
  // void *memcpy(void *str1, const void *str2, size_t n);
  memcpy(pNew, p, old);
  memfree(p);
  p = NULL;

  return pNew;
}


void memfree(void *p) {
  free(p);
}
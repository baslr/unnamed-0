#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "memory.h"

// __attribute__((align(64)))

struct struct_edge_header {
    uint64_t _id;
    uint64_t _key;
    uint64_t _rev;
    uint64_t _from;
    uint64_t _to;
    uint64_t _d[3];
};
typedef struct struct_edge_header edge_header;

struct struct_doc_header {
    uint64_t _id;
    uint64_t _key;
    uint64_t _rev;
    uint64_t _d[1];
};
typedef struct struct_doc_header doc_header;

uint64_t globalRef = 0;
uint64_t globalKey  = 0;


void print_edge_header(edge_header *pHeader, uint64_t count) {
    uint64_t end = (uint64_t)pHeader + 64 * count;

    while((uint64_t)pHeader < end) {
        printf("Header @0x%016llx _key=%lld _rev=%lld _from=%lld _to=%lld\n",
        (uint64_t)pHeader, pHeader->_key, pHeader->_rev, pHeader->_from, pHeader->_to);
        pHeader++;   
    } // for
}

void print_doc_header(doc_header *pHeader, uint64_t count) {
    for(uint64_t i = 0; i < count; i++, pHeader ++) {
        printf("Header @0x%016llx _key=%lld _rev=%lld %lld\n",
        (uint64_t)pHeader, pHeader->_key, pHeader->_rev, i);   
    } // for
}

void init_new_edge_header(edge_header *pHeader, uint64_t count) {
    for(uint64_t i = 0; i < count; i++,pHeader++) {
        pHeader->_key = globalKey++;
        pHeader->_rev = globalRef++;
        pHeader->_from = 0;
        pHeader->_to = 0;
    } // for
}

void init_new_doc_header(doc_header *pHeader, uint64_t count) {
    for(uint64_t i = 0; i < count; i++,pHeader++) {
        pHeader->_key = globalKey++;
        pHeader->_rev = globalRef++;
    } // for
}




int main()
{

    edge_header *pE = memalloc(64);

    printf("\ncontent 0x%016llx\n", (uint64_t)pE);
    printf("address 0x%016llx\n", (uint64_t)&pE);

    memfree(pE);

    #if __linux__
        printf("linux? %d\n", __linux__);
    #endif
    /*
    edge_header *p = malloc(64 * 1024 * 1024);

    if (p == NULL) {
        return 1;
    }




    edge_header *pt = malloc(64);

    print_edge_header(pt, 2);

    

    pt++;

    printf("0x%016llx\n", (uint64_t)pt);



    edge_header *ept = NULL;


    posix_memalign((void**)&ept, 64, 64);

    printf("0x%016llx\n", (uint64_t)ept);

    return 0;



    printf("%ld\n", sizeof(edge_header) );

    clock_t uptime = clock();
    
    // init_new_edge_header(p, 1024*1024);
    clock_t uptime2 = clock() - uptime;
  
    print_edge_header(p, 1024*1024);

    printf("%ld\n", uptime2);

    //printf("0x%016llx\n", (uint64_t)p);
    */



  return(0);
}



/*


edge _from _to



edge index _from[]
edge index _to[]





star doc id -> hash -> lookup in edge index _from

-> load edges -> load docs



*/
#include "mem.h"

struct MemMap *memmap;

void mem_init(){
    memmap = malloc(sizeof(struct MemMap));
}

char * mem_getPointer(){
    return memmap->mem;
}

struct MemMap * mem_getMap(){
    return memmap;
}

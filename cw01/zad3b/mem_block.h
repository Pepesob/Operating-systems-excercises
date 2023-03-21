#ifndef MEM_BLOCK_H
#define MEM_BLOCK_H

#include <stdio.h>

typedef struct {
    void** pointers;
    size_t memory_size;
    int i;
} memory_block;


#endif //MEM_BLOCK_H

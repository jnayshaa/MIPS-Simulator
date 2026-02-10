#ifndef CACHE_H
#define CACHE_H

// Direct mapped cache with 64 lines and 4-byte blocks
#define CACHE_LINES 64
#define BLOCK_SIZE 4

// To switch to a direct-mapped cache with 32 lines and 8-byte blocks, change to:
// #define CACHE_LINES 32
// #define BLOCK_SIZE 8

#include <stdint.h>

typedef struct {
    int valid;
    uint32_t tag;
} CacheLine;

extern CacheLine cache[];
extern int cache_requests;
extern int cache_hits;
extern int mem_ops;

void cache_init(void);
int cache_access(uint32_t addr);

#endif
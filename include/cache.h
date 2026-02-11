#ifndef CACHE_H
#define CACHE_H

#include <stdint.h>
#include <stdio.h>

typedef struct {
    int valid;
    uint32_t tag;
} CacheLine;

typedef struct {
    int lines;           // number of cache lines
    int block_size;      // words per block
    CacheLine *lines_array;
    int cache_requests;
    int cache_hits;
    int mem_ops;
} Cache;

// Two direct-mapped cache configurations
extern Cache cache_64_1word; // 64 lines, 1 word per line
extern Cache cache_32_2word; // 32 lines, 2 words per line

// Pointer to the currently active cache
extern Cache *active_cache;

// Functions
void cache_init(Cache *cache, int lines, int block_size);
int cache_access(Cache *cache, uint32_t addr);
void print_cache_stats(Cache *cache);

#endif
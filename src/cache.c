#include "cache.h"
#include <stdlib.h>
#include <string.h>

// Allocate cache line arrays
CacheLine cache_lines_64[64];
CacheLine cache_lines_32[32];

// Define the cache instances
Cache cache_64_1word = {64, 1, cache_lines_64, 0, 0, 0};
Cache cache_32_2word = {32, 2, cache_lines_32, 0, 0, 0};

// Initialize cache: marks all lines invalid and resets stats
void cache_init(Cache *cache, int lines, int block_size) {
    cache->lines = lines;
    cache->block_size = block_size;
    cache->cache_requests = 0;
    cache->cache_hits = 0;
    cache->mem_ops = 0;

    for (int i = 0; i < lines; i++) {
        cache->lines_array[i].valid = 0;
        cache->lines_array[i].tag = 0;
    }
}

// Access cache at given address
// Returns 1 for hit, 0 for miss
int cache_access(Cache *cache, uint32_t addr) {
    cache->cache_requests++;

    // Compute block number and index
    uint32_t block_addr = addr / (cache->block_size * 4); // 4 bytes per word
    uint32_t idx = block_addr % cache->lines;
    uint32_t tag = block_addr / cache->lines;

    if (cache->lines_array[idx].valid && cache->lines_array[idx].tag == tag) {
        cache->cache_hits++;
        return 1; // hit
    }

    // Miss: load block from memory
    cache->lines_array[idx].valid = 1;
    cache->lines_array[idx].tag = tag;
    cache->mem_ops++; // one memory operation per block fetch
    return 0;         // miss
}

// Print cache statistics
void print_cache_stats(Cache *cache) {
    printf("Cache configuration: %d lines, %d words per line\n",
           cache->lines, cache->block_size);
    printf("Cache requests: %d\n", cache->cache_requests);
    printf("Cache hits: %d\n", cache->cache_hits);
    printf("Memory operations (block loads): %d\n", cache->mem_ops);
    if (cache->cache_requests > 0)
        printf("Hit rate: %.2f%%\n",
               (100.0 * cache->cache_hits) / cache->cache_requests);
    printf("\n");
}
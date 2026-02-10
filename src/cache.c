#include "cache.h"

CacheLine cache[CACHE_LINES];
int cache_requests = 0;
int cache_hits = 0;
int mem_ops = 0;

void cache_init(void) {
    for (int i = 0; i < CACHE_LINES; i++) {
        cache[i].valid = 0;
        cache[i].tag = 0;
    }
}

int cache_access(uint32_t addr) {
    mem_ops++;
    cache_requests++;

    uint32_t block_addr = addr / BLOCK_SIZE;
    uint32_t idx = block_addr % CACHE_LINES;
    uint32_t tag = block_addr / CACHE_LINES;

    if (cache[idx].valid && cache[idx].tag == tag) {
        cache_hits++;
        return 1;  // hit
    }
    // miss
    cache[idx].valid = 1;
    cache[idx].tag = tag;
    return 0;
}
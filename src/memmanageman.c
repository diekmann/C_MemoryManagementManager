/**
 * @file memmanageman.c
 * @brief TODO
 * @author diekmann
 *
 * 
 *
 * @date 05.06.2013 - first implementation
 *
 *
 * @version 0.1
 */

#include <stddef.h>
#include <malloc.h>
#include <strings.h>
#include "memmanageman.h"


void* GenericMemoryManager_malloc_f(struct GenericMemoryManager* this)
{
    void *m = malloc(this->memsize);
    #ifdef DEBUG
        printf("[INFO] allocated %zu bytes of memory at %p\n", this->memsize, m);
    #endif
    ++this->malloc_stats;
    return m;
}

    
void GenericMemoryManager_free_f(struct GenericMemoryManager* this, void* m)
{
    #ifdef DEBUG
        printf("[INFO] freeing %zu bytes of memory at %p\n", this->memsize, m);
    #endif
    bzero(m, this->memsize);
    free(m);
    ++this->free_stats;
}

void GenericMemoryManager_print_stats(struct GenericMemoryManager* this)
{
    printf("Num malloc: %u, Num free: %u \n", this->malloc_stats, this->free_stats);
}

struct GenericMemoryManager* GenericMemoryManager_new(size_t memsize)
{
    struct GenericMemoryManager *m = malloc(sizeof(struct GenericMemoryManager));
    m->memsize = memsize;
    
    
    m->malloc = *GenericMemoryManager_malloc_f;
    m->free = *GenericMemoryManager_free_f;
    
    #ifdef DEBUG
        printf("[INFO] Created new GenericMemoryManager at %p for memory of size"
            " %zu, malloc at %p, free at %p \n", m, m->memsize, m->malloc, m->free);
    #endif
    return m;
}


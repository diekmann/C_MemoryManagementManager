/**
 * @file memmanageman.h
 * @brief TODO
 * @author diekmann
 *
 * @version 0.1
 */

#include <stddef.h>

struct GenericMemoryManager;

typedef void* (*GenericMemoryManager_malloc_f_t)(struct GenericMemoryManager*);
typedef void  (*GenericMemoryManager_free_f_t)(struct GenericMemoryManager*, void*);

struct GenericMemoryManager
{
    size_t memsize;
    unsigned int malloc_stats;
    unsigned int free_stats;
    GenericMemoryManager_malloc_f_t malloc;
    GenericMemoryManager_free_f_t free;
};


struct GenericMemoryManager* GenericMemoryManager_new(size_t);
void GenericMemoryManager_print_stats(struct GenericMemoryManager*);

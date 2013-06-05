/**
 * @file memmanageman.h
 * @brief TODO
 * @author diekmann
 *
 * @version 0.1
 */

#ifndef MEMMANAGEMAN
#define MEMMANAGEMAN

#include <stddef.h>

#include "typedlinkedlist.h"

struct GenericMemoryManager;


typedef void* (*GenericMemoryManager_malloc_f_t)(struct GenericMemoryManager*);
typedef void  (*GenericMemoryManager_free_f_t)(struct GenericMemoryManager*, void*);

struct ManagedMemoryArea
{
	void *start;
	unsigned int id;
};

DEFINETYPEDLLIST(ManagedMemoryArea, struct ManagedMemoryArea);

struct GenericMemoryManager
{
    size_t memsize;
    unsigned int malloc_stats;
    unsigned int free_stats;
    GenericMemoryManager_malloc_f_t malloc;
    GenericMemoryManager_free_f_t free;   
	struct ManagedMemoryArea_list *mamanged_memory_chunks;
};


struct GenericMemoryManager* GenericMemoryManager_new(size_t);
void GenericMemoryManager_delete(struct GenericMemoryManager *);
void GenericMemoryManager_print_stats(struct GenericMemoryManager*);

#endif /* MEMMANAGEMAN */

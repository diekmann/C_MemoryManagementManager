/**
 * @file memmanageman.h
 * @brief A memory management manager freamework
 * @author diekmann
 *
 * @version 0.2
 */

#ifndef MEMMANAGEMAN
#define MEMMANAGEMAN

#include <stddef.h>

#include "typedlinkedlist.h"

struct GenericMemoryManager;

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
	struct ManagedMemoryArea_list *mamanged_memory_chunks;
};


struct GenericMemoryManager* GenericMemoryManager_new(size_t);
void GenericMemoryManager_delete(struct GenericMemoryManager *);
void GenericMemoryManager_print_stats(struct GenericMemoryManager*);


void* GenericMemoryManager_malloc_f(struct GenericMemoryManager*);
void GenericMemoryManager_free_f(struct GenericMemoryManager* this, void* m);


#define DEFINETYPEDMEMEORYMANAGER( name, type, memsize ) \
struct MemoryManager_ ## name \
{ \
	struct GenericMemoryManager *mm;\
    type* (*malloc)(struct MemoryManager_ ## name*);\
    void  (*free)(struct MemoryManager_ ## name*, type*);\
    void  (*delete)(struct MemoryManager_ ## name*);\
}; \
\
\
type* MemoryManager_ ## name ## _malloc_f(struct MemoryManager_ ## name* this)\
{\
	assert(this != NULL);\
    type *m = GenericMemoryManager_malloc_f(this->mm);\
    puts("TODO");\
    return m;\
}\
void MemoryManager_ ## name ## _free_f(struct MemoryManager_ ## name* this, type* m)\
{\
	assert(this != NULL);\
	if(m == NULL) return;\
    GenericMemoryManager_free_f(this->mm, m);\
}\
void MemoryManager_ ## name ## _delete_f(struct MemoryManager_ ## name* this)\
{\
	assert(this != NULL);\
	GenericMemoryManager_delete(this->mm);\
	free(this);\
}\
\
\
struct MemoryManager_ ## name* MemoryManager_ ## name ## _new()\
{\
    struct GenericMemoryManager *m = GenericMemoryManager_new(memsize);\
    struct MemoryManager_ ## name *mm = malloc(sizeof(struct MemoryManager_ ## name));\
    mm->mm = m;\
    mm->malloc = MemoryManager_ ## name ## _malloc_f;\
    mm->free = MemoryManager_ ## name ## _free_f;\
    mm->delete = MemoryManager_ ## name ## _delete_f;\
    return mm;\
}\


#define TYPETYPEDMEMEORYMANAGER( name ) \
struct MemoryManager_ ## name




#endif /* MEMMANAGEMAN */

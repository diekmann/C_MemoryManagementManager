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


#define DEFINETYPEDMEMEORYMANAGER( name, type, memsize ) \
struct MemoryManger_ ## name \
{ \
	struct GenericMemoryManager *mm;\
    type* (*malloc)(struct MemoryManger_ ## name*);\
    void  (*free)(struct GenericMemoryManager*, void*);\
}; \
\
\
type* MemoryManager_ ## name ## _malloc_f(struct MemoryManger_ ## name* this)\
{\
	assert(this != NULL);\
    type *m = GenericMemoryManager_malloc_f(this->mm);\
    puts("TODO");\
    return m;\
}\
\
\
struct MemoryManger_ ## name* MemoryManger_ ## name ## _new()\
{\
    struct GenericMemoryManager *m = GenericMemoryManager_new(memsize);\
    struct MemoryManger_ ## name *mm = malloc(sizeof(struct MemoryManger_ ## name));\
    mm->mm = m;\
    mm->malloc = MemoryManager_ ## name ## _malloc_f;\
    mm->free = NULL;\
    return mm;\
}\


#define TYPETYPEDMEMEORYMANAGER( name ) \
struct MemoryManger_ ## name



//#define NEWTYPEDMEMEORYMANAGER( varname, name, type, memorysize ) 
//struct MemoryManger_ ## name varname;
//varname.mm = GenericMemoryManager_new(memorysize)




#endif /* MEMMANAGEMAN */

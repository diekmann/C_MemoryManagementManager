/**
 * @file memmanageman.c
 * @brief A memory management manager freamework
 * @author diekmann
 *
 * 
 *
 * @date 05.06.2013 - first implementation
 * @date 16.06.2013 - stable testing version 0.2
 *
 * @bug free accepts void pointers
 *
 * @version 0.2
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
    
    { /* insert in list */
		struct ManagedMemoryArea_list* current = this->mamanged_memory_chunks;
		struct ManagedMemoryArea_list* head = current;
		for(; current; current = current->next){
			head = current;
		}
		
		struct ManagedMemoryArea_list *new = malloc((sizeof(struct ManagedMemoryArea_list)));
		
		int id;
		
		// append to head
		if(head == NULL){
			this->mamanged_memory_chunks = new;
			id = 0;
		}else{
			head->next = new;
			id = head->elem.id + 1;
		}
		
		new->elem.start = m;
		new->elem.id = id;
    }
    return m;
}

    
void GenericMemoryManager_free_f(struct GenericMemoryManager* this, void* m)
{
    #ifdef DEBUG
        printf("[INFO] freeing %zu bytes of memory at %p\n", this->memsize, m);
    #endif
    bzero(m, this->memsize);
    
    {// delete from list
		struct ManagedMemoryArea_list* current = this->mamanged_memory_chunks;
		struct ManagedMemoryArea_list* prev = NULL;
		int found = 0;
		for(; current; current = current->next){
			if(current->elem.start == m){
				#ifdef DEBUG
					printf("[INFO] free: found memory with id %d\n", current->elem.id);
				#endif
				found = 1;
				break;
			}
			prev = current;
		}
	
		if(found){
			if(prev){
				prev->next = current->next;
			}else{
				this->mamanged_memory_chunks = NULL;
			}
			free(current);
		}else{
			printf("[ERROR] memory at %p not managed by this manager!\n", m);
		}
	}
	
    free(m);
    ++this->free_stats;
}

void GenericMemoryManager_print_stats(struct GenericMemoryManager* this)
{
    printf("Num malloc: %u, Num free: %u \n", this->malloc_stats, this->free_stats);
    
    printf("Managed chunks:\n");
    struct ManagedMemoryArea_list* current = this->mamanged_memory_chunks;
	for(; current; current = current->next){
    	printf("  id: %u\n", current->elem.id);
	}
}

struct GenericMemoryManager* GenericMemoryManager_new(size_t memsize)
{
    struct GenericMemoryManager *m = malloc(sizeof(struct GenericMemoryManager));
    m->memsize = memsize;
    m->mamanged_memory_chunks = NULL;
    
    #ifdef DEBUG
        printf("[INFO] Created new GenericMemoryManager at %p for memory of size"
            " %zu\n", m, m->memsize);
    #endif
    return m;
}

void GenericMemoryManager_delete(struct GenericMemoryManager *this)
{
    
    #ifdef DEBUG
        printf("[INFO] Deleting GenericMemoryManager at %p for memory of size"
            " %zu\n", this, this->memsize);
    #endif
    if(this->mamanged_memory_chunks != NULL){
    	printf("[ERROR] Memory Mamanager still has managed memory chunks, cannot delete\n");
    }else{
    	if(this->malloc_stats != this->free_stats){
    		printf("[ERROR] numer of frees neq number of mallocs\n");
    	}
    	free(this);
    }
}


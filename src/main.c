/**
 * @file main.c
 * @brief main entry point
 * @author diekmann
 *
 * 
 *
 * @date 0506.2013 – first implementation
 *
 * @todo  sth
 *
 * @test yeah ...
 *
 * @bug may be 
 *
 * @version 0.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "util.h"
#include "memmanageman.h"


/** @mainpage TestProject
 * see files for doc
 *
 */


DEFINETYPEDMEMEORYMANAGER( ijmanager, int );

/**
 * @brief The ultimate main function
 * @param argc the argument count
 * @param argv the argument vector
 * @return return value back to OS
 */
int main(int argc, char **argv){
	UNUSED(argc)
	UNUSED(argv)
	
	printf("Hello World from %s in line %d\n", __FILE__, __LINE__);
	
	printf("gcd of 8, 4 is %d\n", gcd(8,4));
	
	
	NEWTYPEDMEMEORYMANAGER( mmij, ijmanager, int, sizeof(int) );
	// mmij is now of type struct MemoryManger_ijmanager_int mmij
	// this is a _typed_ memory manager for ints of size sizeof(int)
	// mmij.mm access the memory manager
	// it is as simple as shown below
	
	
	// TODO: actually it returns void*, make it return int*
	int *i = mmij.mm->malloc(mmij.mm);
	*i = 42;
	
	int *j = mmij.mm->malloc(mmij.mm);
	*j = 8;
	
	printf("i=%d j=%d\n", *i, *j);
	
	
	GenericMemoryManager_print_stats(mmij.mm);	
	
	mmij.mm->free(mmij.mm, j);
	mmij.mm->free(mmij.mm, i);
	
	GenericMemoryManager_print_stats(mmij.mm);
	
	GenericMemoryManager_delete(mmij.mm);
	
	return 0;
} 


/**
 * @file main.c
 * @brief main entry point
 * @author diekmann
 *
 * 
 *
 * @date 05.06.2013 – first implementation
 *
 * @version 1.0
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



/**
 * @brief The ultimate main function
 * @param argc the argument count
 * @param argv the argument vector
 * @return return value back to OS
 */
int main(int argc, char **argv){
	UNUSED(argc)
	UNUSED(argv)
	
	DEFINETYPEDMEMEORYMANAGER( ij_int_manager, int, sizeof(int) );
	struct MemoryManager_ij_int_manager *mmij = MemoryManager_ij_int_manager_new();
	
	int *i = mmij->malloc(mmij);
	*i = 42;
	
	int *j = mmij->malloc(mmij);
	*j = 8;
	
	printf("i=%d j=%d\n", *i, *j);
	
	
	GenericMemoryManager_print_stats(mmij->mm);	
	
	mmij->free(mmij, j);
	mmij->free(mmij, i);
	
	GenericMemoryManager_print_stats(mmij->mm);
	
	mmij->delete(mmij);
	
	return 0;
} 


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
	
	struct GenericMemoryManager *mm = GenericMemoryManager_new(sizeof(int));
	int *i = mm->malloc(mm);
	*i = 42;
	printf("i=%d\n", *i);
	mm->free(mm, i);
	
	GenericMemoryManager_print_stats(mm);
	
	return 0;
} 


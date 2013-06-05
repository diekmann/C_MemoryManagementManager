/**
 * @file typedlinkedlist.h
 * @brief Linked List implementation
 * @author diekmann
 *
 * @version 0.2
 */

#ifndef TYPEDLINKEDLIST
#define TYPEDLINKEDLIST

#include <stddef.h>


#define DEFINETYPEDLLIST( name, type ) \
struct name ## _list \
{ \
	type elem; \
	struct name ## _list *next;\
}\



#endif /* TYPEDLINKEDLIST */

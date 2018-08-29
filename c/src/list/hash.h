
#ifndef __HASH_H__
#define __HASH_H__

#include "list.h"

#define HASH_MASK 0xFF

struct hash_table{
	struct list_hook bucket[HASH_TABLE_SIZE];
};

struct hash_hook{
	struct list_hook hh;
	unsigned long key;
};


#define hash_func(k) \
	((k) ^ (k)>>8 ^ (k)>>16 ^ (k)>>24 ) & HASH_MASK


:q

	

#endif

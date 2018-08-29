
#ifndef _HASH_H_
#define _HASH_H_

#include "list.h"
#define HASH_MASK 0xff

#define hash_func(k) \
	( ( (k) ^ (k>>8) ^ (k>>16) ^ (k>>24) ) & HASH_MASK )  

struct ht_hook{
	struct ht_hook* next;
	struct ht_hook* prev;
	void* node;
	unsigned long key;
};
struct ht{
	struct list_head bucket[HASH_MASK];
}ht;

void 
init_hash_table(struct ht* ht_p);
	
void
add_hash_item(unsigned long key, struct list_head* l, struct ht* htp);

void
remove_hash_item(struct ht_hook *hh, struct ht* htp);



#endif

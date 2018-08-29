#include <stdlib.h>
#include "hash.h"

void 
init_hash_table(struct ht* ht_p)
{
	int i;
	struct ht* htp = ht_p;
	for (i=0; i<HASH_MASK; i++){
		LIST_HEAD_INIT( &(htp->bucket[i]), NULL);
	}
}
	
void
add_hash(int data, struct list_head* l, struct ht* htp)
{
	int i;

	i = hash_func(data);
	list_add_tail(&(htp->bucket[i]), l );
	
}


void
del_hash_desc(struct list_head* l, struct ht* htp)
{
	list_del_init(l);
}

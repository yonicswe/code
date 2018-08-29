

#include <stdlib.h>
#include "list.h"

#define HASH_TABLE_SIZE 0xff
#define HASH_TABLE_MASK 0xff

struct yoni_task{
	unsigned int itt;	
	unsigned int conn;
	struct list_head hash_list;
};

struct hash_table{
	struct list_head bucket[HASH_TABLE_SIZE];
};


unsigned int
hash_func(unsigned int key)
{
	unsigned int hash_val;

	hash_val = (key ^ (key>>8) ^ (key>>16) ^ (key>>24)) & HASH_TABLE_MASK;
	return hash_val;

}

struct yoni_task*
alloc_task(unsigned int itt, unsigned int conn)
{
	struct yoni_task* p_task = NULL;
	p_task = (struct yoni_task*)malloc(sizeof(struct yoni_task));
	memset(p_task, 0, sizeof(struct yoni_task));
	INIT_LIST_HEAD(&p_task->hash_list);
	p_task->itt = itt;
	p_task->conn = conn;
	return p_task;

}

void
free_task(struct yoni_task* p_task)
{
	printf("freeing task:0x%p\n",p_task);
	free(p_task);
}

//
// initialize hash table for yoni tasks.
//
void
hash_init_task(struct hash_table* h_tbl)
{
	int i;

	for (i=0; i<HASH_TABLE_SIZE; i++){
		INIT_LIST_HEAD(&h_tbl->bucket[i]);
	}


}

//
// add a new yoni_task to hash table.
//
int
hash_add_task(struct hash_table* p_htbl, struct yoni_task* p_task)
{
	struct list_head* p_bucket;
	struct list_head* p_list;
	struct yoni_task* dbg_task;
	unsigned int bucket_idx;
	// choose a bucket to place the task
	bucket_idx =  hash_func(p_task->itt ^ p_task->conn);

	p_bucket = &(p_htbl->bucket[bucket_idx]);
	// make sure that the task does not already exist in the table.
	p_list = p_bucket->next;
	while (p_bucket != p_list ){
		dbg_task = list_entry(p_list, struct yoni_task, hash_list);
		if (dbg_task->itt == p_task->itt && dbg_task->conn == p_task->conn) {
			printf("Already exist itt:%u for conn: 0x%x\n",p_task->itt, p_task->conn);
			return 1;
		}
		p_list = p_list->next;
	}

	list_add_tail(&p_task->hash_list, p_bucket); 
	printf("added task:0x%p, itt:%u, conn:0x%x, to bucket:%u\n",
			p_task, p_task->itt, p_task->conn, bucket_idx);
	return 0;
}

//
// find a task in the hash table.
//
struct yoni_task*
hash_find_task(struct hash_table* p_htbl, unsigned int find_itt, int conn)
{
	unsigned int itt = find_itt;
	struct list_head* p_bucket;
	struct list_head* p_list;
	struct yoni_task* found_task;
	unsigned int bucket_idx;
	
	// resolve the bucket in which the task is
	bucket_idx = hash_func(itt ^ conn);
	p_bucket = &(p_htbl->bucket[bucket_idx]);
	
	//find the task;
	p_list = p_bucket->next;
	while (p_list != p_bucket) {
		found_task = list_entry(p_list, struct yoni_task, hash_list);
		if (found_task->itt == itt && found_task->conn == conn){
			printf("found task, itt:%d, conn:0x%x\n",find_itt, conn);
			return found_task;
		}
		else 
			printf("skip task, itt:%d, conn:0x%x\n",found_task->itt, found_task->conn);

		p_list = p_list->next;
	}

	return NULL; 
}


//
// delete a task from hash table.
//
int
hash_del_task(struct hash_table* p_htbl, unsigned int del_itt, unsigned int conn)
{
	unsigned int itt = del_itt;
	unsigned int bucket_idx;
	struct list_head* p_list;
	struct list_head* p_bucket;
	struct yoni_task* del_task;

	bucket_idx = hash_func(itt ^ conn);
	p_bucket = &p_htbl->bucket[bucket_idx];

	p_list = p_bucket->next;
	while (p_list != p_bucket) {
		del_task = list_entry(p_list, struct yoni_task, hash_list);
		if (del_task->itt == itt && del_task->conn == conn){
			list_del_init(&del_task->hash_list); 
			free_task(del_task);
			return 0;
		}
		else 
			printf("%s: skip task, itt:%u, conn:0x%x\n",del_task->itt, del_task->conn);
		p_list = p_list->next;
	}

	return 1; 
}





//
// the hash table.
//
struct hash_table yoni_hash_table;


//
// Main
//
int
main(int argc, char* argv[]) 

{
	int i;
	int ret;
	int a[] =    {34,  234, 1542, 34, 234, 12,  2543, 34};
	int conn[] = {0x12,0x12,0x12,0x13,0x13,0x13,0x13, 0x12};
	int size_a = sizeof(a) / sizeof(int);
	struct yoni_task* p_task;
	int conn1;
	int conn2;

	hash_init_task(&yoni_hash_table);

	//
	// alloc and add tasks to hash_list.
	//
	printf("allocating tasks\n");
	for ( i=0; i<size_a; i++){
		ret =0;
		p_task = alloc_task(a[i], conn[i]); 
		ret = hash_add_task(&yoni_hash_table, p_task);
		if (ret !=0 ) 
			free_task(p_task);		
		
	}
	
	//
	// find the tasks
	//
	for ( i=0; i<size_a; i++){
		p_task = hash_find_task(&yoni_hash_table, a[i],conn[i]); 
		if (p_task == NULL ) 
			printf("task, itt:%u NOT FOUND\n",p_task->itt);
	}

	//
	// delete and free tasks.
	//
	printf("deleting tasks\n");
	for ( i=0; i<size_a; i++){
		ret = 0;
		p_task = alloc_task(a[i],conn[i]); 
		ret = hash_del_task(&yoni_hash_table, a[i],conn[i]);
		if (ret != 0 )
			printf("task, itt:%u not found\n",a[i]);
	}
	

	return 0;
}

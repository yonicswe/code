
#include <stdlib.h>
#include "../list.h"

#define HASH_MASK 0xff
#define HASH_TABLE_SIZE HASH_MASK

struct test_task { 
	unsigned int itt;
	unsigned int conn;
	struct list_head hash_list;
};

struct hash_table { 
	struct list_head bucket[HASH_TABLE_SIZE];
};


struct test_task*
alloc_test_task(unsigned int itt, unsigned int conn)
{
	struct test_task* p_task=NULL;

	p_task = (struct test_task*)malloc(sizeof(struct test_task));
	if (p_task == NULL ) 
		goto exit_alloc_task;
	p_task->itt = itt;
	p_task->conn = conn;

exit_alloc_task:
	return p_task;
}

void 
free_test_task(struct test_task* p_task)
{
	free (p_task); 
}


unsigned int 
hash_func(unsigned int key) 
{
	unsigned int hash_val;
	hash_val = (key ^ (key>>24) ^ (key^16) ^ (key>>8) ) & HASH_MASK;
	return hash_val; 
}

void
hash_table_init(struct hash_table* p_htbl)
{
	int i;

	for (i=0; i<HASH_TABLE_SIZE; i++){
		INIT_LIST_HEAD(&p_htbl->bucket[i]);
	} 
}

void
hash_add_task(struct hash_table* p_htbl, struct test_task* p_task)
{
	unsigned int bucket_index;
	unsigned int itt = p_task->itt;
	unsigned int conn = p_task->conn;
	struct list_head* p_list;

	// find the bucket to place the task
	bucket_index = hash_func(itt ^ conn);

	// get the list head  of this bucket.
	p_list = &p_htbl->bucket[bucket_index];

	// add the task to the end of the list.
	list_add_tail(&p_task->hash_list, p_list); 
}

struct test_task*
hash_del_task(struct hash_table* p_htbl, unsigned int del_itt, unsigned int del_conn)
{
	unsigned int bucket_index;
	unsigned int itt = del_itt;
	unsigned int conn = del_conn;
	struct list_head* p_list;
	struct list_head* p_bucket;
	struct test_task* p_task;

	// find the bucket to place the task
	bucket_index = hash_func(itt ^ conn);

	// get the list head  of this bucket.
	p_bucket = &p_htbl->bucket[bucket_index];

	// find the task in the list
	p_list = p_bucket->next;
	while (p_list != p_bucket) {
		p_task = list_entry(p_list, struct test_task, hash_list);
		if (p_task->itt == itt && p_task->conn == conn){
			list_del_init(p_list);
			return p_task;
		} 
		p_list = p_list->next;
	}

	return NULL;


}

struct test_task*
hash_find_task(struct hash_table* p_htbl, unsigned find_itt, unsigned int find_conn)
{
	unsigned int bucket_index;
	unsigned int itt = find_itt;
	unsigned int conn = find_conn;
	struct list_head* p_list;
	struct list_head* p_bucket;
	struct test_task* p_task;

	// find the bucket to place the task
	bucket_index = hash_func(itt ^ conn);

	// get the list head  of this bucket.
	p_bucket = &p_htbl->bucket[bucket_index];

	// find the task in the list
	p_list = p_bucket->next;
	while (p_list != p_bucket) {
		p_task = list_entry(p_list, struct test_task, hash_list);
		if (p_task->itt == itt && p_task->conn == conn)
			return p_task;
		p_list = p_list->next;
	}

	return NULL; 
}


void 
hash_table_print(struct hash_table* p_htbl)
{

	unsigned int bucket_index;
	struct list_head* p_list;
	struct list_head* p_bucket;
	struct test_task* p_task;

	printf("hash_table\n-----------\n");
	
	for (bucket_index=0; bucket_index < HASH_TABLE_SIZE; bucket_index++){
		p_bucket = &p_htbl->bucket[bucket_index];
		if (list_empty(p_bucket) )		
			continue;
		
		p_list = p_bucket->next;
		printf("bucket: %d\n",bucket_index);
		while (p_list != p_bucket){
			p_task = list_entry(p_list, struct test_task, hash_list);	
			printf("\ttask:0x%p, itt:%u, conn:%u\n", p_task, p_task->itt, p_task->conn);
			p_list = p_list->next;
		} 
	}

}


//
// Main
//
int 
main(int argc, char* argv[]) 
{
	unsigned int itt_arr[]  = {1234, 5466, 1233, 32,   1234, 32};
	unsigned int conn_arr[] = {0xaa, 0xaa, 0xaa, 0xaa, 0xbb, 0xbb };
	unsigned int size_conn_arr = sizeof(conn_arr)/sizeof(unsigned int);
	int i;
	struct hash_table test_hash_table;
	struct test_task* p_task;
	int found;

	hash_table_init(&test_hash_table);
	
	for (i=0; i<size_conn_arr; i++){
		p_task = alloc_test_task(itt_arr[i], conn_arr[i]);
		hash_add_task(&test_hash_table, p_task);
		printf("task: 0x%p, itt:%u, conn:%u, added\n",p_task, p_task->itt, p_task->conn);
	}

	hash_table_print(&test_hash_table);

	for (i=0; i<size_conn_arr; i++){
		p_task  = hash_find_task(&test_hash_table, itt_arr[i], conn_arr[i]);
		if (p_task != NULL)
			printf("task: 0x%p, itt:%u, conn:%u, found\n", p_task, p_task->itt, p_task->conn);
		else
			printf("task: itt:%u, conn:%u, not found\n", itt_arr[i], conn_arr[i]);
	}	
	
	for (i=0; i<size_conn_arr; i++){
		p_task = hash_del_task(&test_hash_table, itt_arr[i], conn_arr[i]);	
		if (p_task != NULL){
			printf("task: 0x%p, itt:%u, conn:%u, free\n",p_task, p_task->itt, p_task->conn);
			free_test_task(p_task);
		}
		else
			printf("task: itt:%u, conn:%u, not found\n", itt_arr[i], conn_arr[i]);
	
		hash_table_print(&test_hash_table);
	}


	return 0;

}



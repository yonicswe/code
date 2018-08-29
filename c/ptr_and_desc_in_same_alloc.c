

struct some_desc {
	int some_data1;
	int some_data2;
};


int
alloc_some_desc_list(int entries, struct some_desc*** some_desc_list)
{
	struct some_desc*  some_desc_p;
	void* 			   some_desc_arr;
	int				   index;
	
	/* allocate */
	some_desc_arr = (char*)malloc(entries * (sizeof(void*) + sizeof(struct some_desc)));

	/* initialize */ 
	*some_desc_list = (struct some_desc**)some_desc_arr;
	some_desc_p = (struct some_desc*)(some_desc_arr + entries * sizeof(void*));
	for(index=0; index< entries ; index++){
		(*some_desc_list)[index] = &some_desc_p[index];		
	}

	return 0;
}



int
main(void)
{
	int 			   entries = 3;
	int				   index;
	struct some_desc** some_desc_list;
	
	alloc_some_desc_list(entries, &some_desc_list);
		
	// populate list 
	for(index=0; index< entries ; index++){
		some_desc_list[index]->some_data1 = index * 2;
		some_desc_list[index]->some_data2 = index * 3;
	}
	
	for(index=0; index< entries ; index++){
		printf("desc[%d]: data1: %d, data2: %d\n",index,some_desc_list[index]->some_data1,
				some_desc_list[index]->some_data1);
	}


	
	free(some_desc_list);

	return 0;
}

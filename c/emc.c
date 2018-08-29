enum task_state {
		 TASK_STATE_INIT,
		 	 TASK_STATE_ADDED_TO_SESSION,
			 	 TASK_STATE_REMOVED_FROM_SESSION,
				 	 TASK_STATE_TIMEDOUT,
					 	 TASK_STATE_FREED,
						 	 TASK_STATE_NUM
};

char *task_state_name[TASK_STATE_NUM+1] = {
		 "TASK_STATE_INIT",
		 	 "TASK_STATE_ADDED_TO_SESSION",
			 	 "TASK_STATE_REMOVED_FROM_SESSION",
				 	 "TASK_STATE_TIMEDOUT",
					 	 "TASK_STATE_FREED",
						 	 "ILLEAGLE"
};

#define get_task_state_name(state) \
	task_state_name[(state>=TASK_STATE_NUM || state<0) ? TASK_STATE_NUM : state]

		
int
main(void)
{
	int addr1[30];
	int addr2[30];
	
	printf("state: %s\n",get_task_state_name(TASK_STATE_INIT) );
	printf("state: %s\n",get_task_state_name(TASK_STATE_ADDED_TO_SESSION) );
	printf("state: %s\n",get_task_state_name(-1) );
	printf("state: %s\n",get_task_state_name(56) );

	
	memcpy(addr1, addr2, 30*sizeof(int));

	
	return 0;

}

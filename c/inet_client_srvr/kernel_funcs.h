
#define MAX_THREAD_NAME 15
typedef void (*thread_func)(void*);

struct thread
{
	struct task_struct	*local_thread;
	struct semaphore	start_sem;
	struct semaphore	stop_sem;
	thread_func		start_func;
	void			*thread_param;
	char			thread_name[MAX_THREAD_NAME+1];
};


enum {
	OS_TCP_SOCK, 
	OS_UDP_SOCK
}SOCK_TYPES;

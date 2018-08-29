
#include "kernel_funcs.h"

int 
inet_sock_create(struct socket *sock, OS_SOCK_TYPES sock_type)
{
	int rc;
	int sock_type;

	sock_type = PF_INET;              

	if ((rc = sock_create(sock_type, SOCK_STREAM, IPPROTO_TCP, sock))<0) {
		printk("%s() failed to create socket ret=%d\n", __func__, rc);
	}

	(*sock)->sk->allocation = GFP_ATOMIC;

	if (rc < 0)
		return 1;

	return 0;
}


int 
inet_sock_bind(struct socket sock, unsigned int port, char *strAddr)
{
	struct sockaddr_in laddr;
	int rc;

	memset((char *)&laddr, 0, sizeof(laddr));
	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(port);

	if (strAddr == NULL)
		laddr.sin_addr.s_addr  = INADDR_ANY;
	else if (!strcmp(strAddr,"0.0.0.0"))
		laddr.sin_addr.s_addr  = INADDR_ANY;
	else
		laddr.sin_addr.s_addr = in_aton(strAddr);

	if ( (rc = sock->ops->bind(sock, (struct sockaddr*) &laddr, sizeof(laddr))) < 0 ) {
		printk("%s() failed bind rc: %d\n", __func__, rc);
		return 1;
	}

	return 0;
}

/***********************************************************************
* Name: int OS_SockListen(OS_Socket sock)
*
* Purpose: Listen on the specified Socket.
*
* Algorithm: None
*
***********************************************************************/
int 
inet_sock_listen(struct socket sock)
{
	int rc;

	if ((rc = sock->ops->listen(sock, 32))<0) {
		printk("%s() sock->ops->listen() return=%d\n",__func__, rc);
		return 1;
	}

	return 0;
}

/***********************************************************************
* Name: int OS_SockAccept(OS_Socket sock, OS_Socket *newsock)
*
* Purpose: Accept a connection request on a listening socket.
*
* Algorithm: None
*
***********************************************************************/
int 
inet_sock_accept(struct  socket sock, struct socket *newsock)
{
	int rv;
	*newsock = sock_alloc();

	(*newsock)->ops = sock->ops;
	(*newsock)->type = sock->type;

	if ((rv = (*newsock)->ops->accept(sock, *newsock, 0))<0)
	{
		if (rv == -ERESTARTSYS)
		{
			if (signal_pending(current))
				return 1;
		}
		else
		{
			printk("%s() newsock->ops->accept() return=%d\n",__func__, rv);
			return 1;
		}
	}

	return 0;
}



/***********************************************************************
* Name: int OS_SockClose(OS_Socket sock)
*
* Purpose: Close an active Socket and return its resources to the system.
*
* Algorithm: None
*
***********************************************************************/
int inet_sock_close(struct socket sock)
{
	int rv;

	if ((rv = sock->ops->release(sock)) != 0)
	{
		printk("%s() sock->ops->release() ret=%d\n",__func__, rv);
		return 1;
	}

	return 0;
}


static void
thread_wrapper_func(struct thread *thp)
{
    daemonize();

    lock_kernel();
    mb();

    // fill in thread structure
    thp->local_thread = current;

    // set signal mask to what we want to respond
    siginitsetinv(&current->blocked, sigmask(SIGKILL)|sigmask(SIGINT)|sigmask(SIGTERM));

    memset(current->comm,0,16);
    snprintf(current->comm,15,"%s",thp->thread_name);

    printk("%s: starting thread [%s] task=0x%p\n",__func__, current->comm, current);

    unlock_kernel();

    // tell the creator that we are ready and let him continue
    up(&thp->start_sem);

    // do the real thread function
    thp->start_func(thp->thread_param);
    printk("%s: thread func [%s] finished task=0x%p\n",__func__, current->comm, current);

    if (thp->local_thread == NULL) {
	   // kill_thread already called and did not free thread object
	    kfree(thp);
    }
    else {
	    // lock the kernel, __OS_KillThread will unlock it
	    lock_kernel();
	    thp->local_thread = NULL;
	    mb();
    	    // let __OS_KillThread continue, it will call unlock_kernel()
	    up(&thp->stop_sem);
    }
    printk("%s: reparent_to_init\n",__func__);
    reparent_to_init();
}


struct thread*
create_thread(thread_func start_func,
	      void *Param,
	      char *name)
{
	struct thread *th = kmalloc(sizeof(struct thread));

	if (!th)
		return NULL;

	th->start_func = start_func;
	th->thread_param = Param;

	if (name==NULL) {
		name=DEFAULT_THREAD_NAME;
	}

	strncpy(thread->thread_name, name, MAX_THREAD_NAME);
	thread->thread_name[MAX_THREAD_NAME]='\0';

	sema_init(&thread->start_sem, 0);
	sema_init(&thread->stop_sem, 0);

	kernel_thread((int (*)(void *)) thread_wrapper_func, th, 0);

	// wait till it has reached the setup_thread routine 
	down(&thread->start_sem);

	return thread;
}


int
kill_thread(struct thread *thp)
{
    int ret;

    if (thp == NULL) {
        printk("%s thread pointer: NULL\n");
        return 1;
    }

    lock_kernel();
    mb();

    printk("%s() kernel_locked\n",__func__);
    if (OS_Thread->local_thread != NULL) {
        if (OS_Thread->local_thread == current){
	    ITRACE(TRACE_THREAD,"%s() Thread Called kill for itself from:%s\n",
		   __func__, caller);
	    OS_Thread->local_thread = NULL;
            goto exit_kill_thread;
        }

        mb();
        ret = kill_proc(OS_Thread->local_thread->pid, SIGKILL, 1);
	if (ret < 0) {
            VD_LOG(VDLOG_PANIC,"%s() Failed killing thread pid=%d\n",__func__, OS_Thread->local_thread->pid);
        }
	ITRACE(TRACE_THREAD,"%s() Thread pid=%d killed\n",__func__, OS_Thread->local_thread->pid);
    }
    else {
	VD_LOG(VDLOG_ERROR,"%s() Thread:0x%p name:%s, local_thread NULL! called by:%s\n",
	       __func__, OS_Thread, OS_Thread->thread_name, caller);
	BUG();
    }

    ITRACE(TRACE_THREAD,"%s() Waiting for thread 0x%p to exit\n",__func__, OS_Thread);
    down(&OS_Thread->stop_sem);

    ITRACE(TRACE_THREAD,"%s() Thread 0x%p exited unlocking kernel\n",__func__, OS_Thread);

    /* release the big kernel lock */
    unlock_kernel();
    ITRACE(TRACE_THREAD, "%s() kernel_unlocked\n",__func__);

    OS_Free (OS_Thread);

exit_kill_thread:
    EXIT_LOG;
    return OS_OK;
}

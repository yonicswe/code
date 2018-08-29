
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// protos
void child_process(char* ip_addr);
void usage(void);

void 
usage(void)
{
	 printf("client [ip_address]\n");
}



// functions
void
child_process(char* ip_addr)
{

	int flag=0;
	int stat;

       do {
               // connect to the ip address.
               if (flag == 0 ) {
                       printf("child: pid: %d ip:[%s]\n",getpid(), ip_addr);
                       flag=1;
               }


       } while ( 1 );

	printf("child: exit\n",ip_addr);
}

void
father_process(int child_pid)
{

	int flag=0;
	int stat;

       do {
               // connect to the ip address.
               if (flag == 0 ) {
                       printf("father: pid:%d, forked child %d\n",getpid(), child_pid);
                       flag=1;
               }


       } while ( 1 );

	printf("father: forked child %d\n",child_pid);

                       printf("father: pid:%d, forked child %d\n",getpid(), child_pid);
	waitpid(child_pid, NULL, 0);
	printf("father: exit\n");
}




void
fork_process(char* ip_addr)
{
	pid_t child_pid = 0;
	int pipes[2];

	/* make pipes */
	if (pipe(pipes) < 0) {
		printf("father: Failed to create pipes\n");
		return;
	}

fork_again:
	child_pid = fork();
	if (child_pid < 0) {
		printf("father: cannot fork\n");
		sleep(1);
		goto fork_again;
	}
	else if (child_pid == 0) {
		/* close the read side */
		close(pipes[0]);
		
		printf("child: calling child_process\n");
		child_process(ip_addr);
		return;
	}
       else {
		// close the write side 
		close(pipes[1]);        
		father_process(child_pid);
		return;
	}   
}



int 
main (int argc, char *argv[])
{
	char ip_addr[50];
	int stat;

	if (argc < 2) {
		usage();
		exit(1);
	}

	// get IP from parameter 
	strcpy(ip_addr, argv[1]);

	fork_process(ip_addr);


       printf("main: exit\n");

	exit(0);
}

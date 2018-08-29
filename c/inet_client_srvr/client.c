
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>

static int wake_up;
	 
void 
usage(void)
{
	 printf("client <ip_address> <port>\n");
	 
}

static void
sigalarm_handler(int unused)
{
	printf("%s\n",__func__);
	wake_up=1;
}

int 
main (int argc, char *argv[])
{
	char ip_addr[50];
	unsigned int port;

	//struct sigaction action;
	//struct sigaction old;

	if (argc < 3) {
		usage();
		exit(1);
	}


	// register signal handler.
	signal(SIGKILL|SIGINT|SIGQUIT|SIGABRT, sigalarm_handler);
	
	// get IP from parameter 
	strcpy(ip_addr, argv[1]);
	port = atoi(argv[2]);

	// connect.
	printf("connect ip:%s:%u\n",ip_addr, port);
	inet_connect(ip_addr, port);

       // wait.
	while (!wake_up) {
		printf("sleep 10\n");
		if (!wake_up) {
			sleep(10);
		}
	}

	// disconnect
	printf("disconnect ip:[%s]\n",ip_addr);
	
       printf("main: exit\n");

	exit(0);
}

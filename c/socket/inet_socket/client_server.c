#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <time.h>

const u_short PORT_NO = 12345;
const int     NO_MSGS = 10;
const int     MAX_MSG = 256;

bool init_wsock()
{
	WSADATA wsaData;
	WORD    wVersionRequested = MAKEWORD(2, 0);
  
	if (!WSAStartup(wVersionRequested, &wsaData)) {
		if (wsaData.wVersion == wVersionRequested)
			return true;
		WSACleanup();
	} 

	return false;
}

void exit_failure(SOCKET sock)
{
	closesocket(sock); WSACleanup();
	exit(EXIT_FAILURE);
}

void gen_rand_msg(char buff[], int len)
{
	for (int i = len - 1; i >= 0; --i)
		buff[i] = ' ' + rand() % (127 - ' ');
}

int async_send(SOCKET sock, char *buff, int len)
{
	do {
		int res = send(sock, buff, len, 0);
		if (res == SOCKET_ERROR)
			return 1;
		buff += res; len -= res;
	} while (len > 0);

	return 0;
}

u_long send_stuff(SOCKET sock)
{
	u_long on = 1;
	ioctlsocket(sock, FIONBIO, &on);

	fd_set write_fs;
	FD_ZERO(&write_fs); FD_SET(sock, &write_fs);
	timeval tv = { 0, 10000 };

	srand(time(0));

	u_long b_send = 0;

	for (int i = NO_MSGS; i > 0; --i) {
		int res = select(1, 0, &write_fs, 0, &tv);

		if (SOCKET_ERROR == res) {
			fprintf(stderr, "\nselect() error\n"); 
			return b_send;
		}
		if (!res) {
			fprintf(stderr, "\nselect() timeout\n");
			return b_send;
		}
		
		char buff[MAX_MSG];
		int len = rand() % MAX_MSG;
		gen_rand_msg(buff, len);

		b_send += len;
		if (async_send(sock, buff, len)) {
			fprintf(stderr, "\nsend() error\n"); 
			return b_send;	// a small bug here, but ...
		}
	}

	return b_send;
}

u_long receive_stuff(SOCKET sock)
{
	u_long on = 1;
	ioctlsocket(sock, FIONBIO, &on);

	fd_set read_fs;
	FD_ZERO(&read_fs); FD_SET(sock, &read_fs);
	timeval tv = { 0, 10000 };

	u_long b_received = 0;

	for (;;) {
		int res = select(1, &read_fs, 0, 0, &tv);

		if (SOCKET_ERROR == res) {
			fprintf(stderr, "\nselect() error\n"); 
			return b_received;
		}
		if (!res) {
			fprintf(stderr, "\nselect() timeout\n");
			return b_received;
		}

		char buff[MAX_MSG];
		
		if (!(res = recv(sock, buff, sizeof(buff), 0))) 
			return b_received;	// the server closed the connection ?
		
		b_received += res;
		
		for (int i = 0; i < res; ++i) putchar(buff[i]);

	}
}

int main(int argc, char *argv[])
{
	if (!init_wsock()) 
		return EXIT_FAILURE;

	SOCKET my_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		
	if (INVALID_SOCKET == my_sock) {
		WSACleanup(); 
		return EXIT_FAILURE;
	}

	char hostname[256];
	
	if (SOCKET_ERROR == gethostname(hostname, sizeof(hostname) - 1))
		exit_failure(my_sock);
	
	sockaddr_in sa = { 0 };

	if (hostent *hoststuff = gethostbyname(hostname)) {
		sa.sin_family = AF_INET;
		sa.sin_port = htons(PORT_NO);
		sa.sin_addr.s_addr = *(long *)hoststuff->h_addr_list[0];
	} else exit_failure(my_sock);

	if (argc == 1) {
		puts("server mode");
		if (SOCKET_ERROR == bind(my_sock, (sockaddr *)&sa, sizeof(sa)))
			exit_failure(my_sock);

		if (SOCKET_ERROR == listen(my_sock, 10))
			exit_failure(my_sock);

		sockaddr_in client_addr;
		int 		claddr_len = sizeof(client_addr);

		SOCKET client_sock = accept(my_sock, (sockaddr *)&client_addr, &claddr_len);
		if (INVALID_SOCKET != client_sock) {
			u_long b_send = send_stuff(client_sock);
			closesocket(client_sock);
			printf("\nbytes send: %u", b_send);
		}
	} else {
		puts("client mode");
		if (SOCKET_ERROR != connect(my_sock, (sockaddr *)&sa, sizeof(sa))) {
			u_long b_received = receive_stuff(my_sock);
			printf("\nbytes received: %u", b_received);
		}
	}

	closesocket(my_sock); WSACleanup();
	return EXIT_SUCCESS;
}


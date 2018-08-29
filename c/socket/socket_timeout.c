int sockfd;
struct sockaddr_in self;
struct sockaddr_in client_addr;
int addrlen=sizeof(client_addr);
ssize_t nBytes;

sockfd = socket(AF_INET, SOCK_STREAM, 0);

self.sin_family = AF_INET;
self.sin_port = htons(PORT);
self.sin_addr.s_addr = INADDR_ANY;

int on = 1;
setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on);

// 1 Sec Timeout
tv.tv_sec  = 1;  
tv.tv_usec = 0;
setsockopt( sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv);

bind(sockfd, (struct sockaddr*)&self, sizeof(self));

listen(sockfd, 20);

clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);

nBytes = recv(clientfd, buffer, MAXBUF-1, 0);
// Without 'setsockopt( sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv);' the calls to accept and recv work, but recv blocks.  
// With 'setsockopt( sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv);' the call to accept produces the error 'Resource temporarily unavailable'.  
// Can somebody please tell me what is wrong with this approach?

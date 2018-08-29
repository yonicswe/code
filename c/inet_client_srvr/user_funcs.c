//
// code taken from linux-iscsi file: iscsi-io
// 
// 
// 
// 



//#include <unistd.h>
//#include <errno.h>


#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#include <sys/uio.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

static int timedout;

static void
sigalarm_handler(int unused)
{
	timedout = 1;
}

int
inet_connect(char* tgt_ip, unsigned int tgt_port)
{
	int ret, rc, sock=-1, onearg;
	struct in_addr addr4socket;
	struct sockaddr_in addr;
	struct sigaction action;
	struct sigaction old;

	/* set a timeout, since the socket calls may take a long time to 
	 * timeout on their own 
	 */
	memset(&action, 0, sizeof (struct sigaction));
	memset(&old, 0, sizeof (struct sigaction));
	action.sa_sigaction = NULL;
	action.sa_flags = 0;
	action.sa_handler = sigalarm_handler;
	sigaction(SIGALRM, &action, &old);
	timedout = 0;
	alarm(10); // send an alarm signal in 10 seconds 
		   // by then the connect should succeed.

	/* create a socket */
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0) {
		printf("cannot create TCP socket\n");
		goto done;
	}

	onearg = 1;
	rc = setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &onearg,
			sizeof (onearg));
	if (rc < 0) {
		printf("cannot set TCP_NODELAY option on socket\n");
		close(sock);
		goto done;
	}

	/* optionally set the window sizes 
	if (session->tcp_window_size) {
		int window_size = session->tcp_window_size;
		socklen_t arglen = sizeof (window_size);

		if (setsockopt
		    (sock, SOL_SOCKET, SO_RCVBUF, (char *) &window_size,
		     sizeof (window_size)) < 0) {
			logmsg(AS_NOTICE,
			       "failed to set TCP recv window size to %u\n",
			       window_size);
		} else
		    if (getsockopt
			(sock, SOL_SOCKET, SO_RCVBUF, (char *) &window_size,
			 &arglen) >= 0) {
			debugmsg(4,
				 "set TCP recv window size to %u, "
				 "actually got %u\n",
				 session->tcp_window_size, window_size);
		}

		window_size = session->tcp_window_size;
		arglen = sizeof (window_size);

		if (setsockopt
		    (sock, SOL_SOCKET, SO_SNDBUF, (char *) &window_size,
		     sizeof (window_size)) < 0) {
			logmsg(AS_NOTICE,
			       "failed to set TCP send window size to %u\n",
			       window_size);
		} else
		    if (getsockopt
			(sock, SOL_SOCKET, SO_SNDBUF, (char *) &window_size,
			 &arglen) >= 0) {
			debugmsg(4,
				 "set TCP send window size to %u, "
				 "actually got %u\n",
				 session->tcp_window_size, window_size);
		}
	} */

	// Build a TCP connection to the target
	memset(&addr, 0, sizeof (addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(tgt_port);
	//inet_aton(tgt_ip, &addr4socket);
	//memcpy(&addr.sin_addr.s_addr, &addr4socket.s_addr, 16);
	inet_aton

	printf("connecting to %s:%d", inet_ntoa(addr.sin_addr), 3260);
	rc = connect(sock, (struct sockaddr *) &addr, sizeof (addr));
	if (timedout) {
		printf("socket %d connect timed out", sock);
		goto done;
	}
	else if (rc < 0) {
		printf("cannot make connection to %s:%d",inet_ntoa(addr.sin_addr), tgt_port);
		close(sock);
		goto done;
	}
	else {
		struct sockaddr_in local;
		socklen_t len = sizeof (local);

		if (getsockname(sock, (struct sockaddr *) &local, &len) >= 0) {
			printf("connected local port %d to %s:%d\n",
			       ntohs(local.sin_port),
			       inet_ntoa(addr.sin_addr), tgt_port);
		}
	}

done:
	alarm(0);
	sigaction(SIGALRM, &old, NULL);
	
	return sock;
}

void
inet_disconnect(int sock)
{
	printf("disconnecting sock: %d\n",sock);
	close(sock);
}

/*
static void
iscsi_log_text(struct IscsiHdr *pdu, char *data)
{
	int dlength = ntoh24(pdu->dlength);
	char *text = data;
	char *end = text + dlength;

	while (text && (text < end)) {
		debugmsg(4, ">    %s", text);
		text += strlen(text);
		while ((text < end) && (*text == '\0'))
			text++;
	}
}

int
iscsi_send_pdu(struct iscsi_session *session, struct IscsiHdr *pdu, char *data,
	       int timeout)
{
	int rc, ret = 0;
	char *header = (char *) pdu;
	char *end;
	char pad[4];
	struct iovec vec[3];
	int pad_bytes;
	int pdu_length = sizeof (*pdu) + pdu->hlength + ntoh24(pdu->dlength);
	int remaining;
	struct sigaction action;
	struct sigaction old;

	// set a timeout, since the socket calls may take a long time 
	// to timeout on their own 
	memset(&action, 0, sizeof (struct sigaction));
	memset(&old, 0, sizeof (struct sigaction));
	action.sa_sigaction = NULL;
	action.sa_flags = 0;
	action.sa_handler = sigalarm_handler;
	sigaction(SIGALRM, &action, &old);
	timedout = 0;
	alarm(timeout);

	memset(&pad, 0, sizeof (pad));
	memset(&vec, 0, sizeof (vec));

	if (daemon_config.debug_level > 0) {
		switch (pdu->opcode & ISCSI_OPCODE_MASK) {
		case ISCSI_OP_LOGIN_CMD:{
				struct IscsiLoginHdr *login_pdu =
				(struct IscsiLoginHdr *) pdu;

				debugmsg(4,
					 "sending login PDU with current stage "
					 "%d, next stage %d, transit 0x%x, isid"
					 " 0x%02x%02x%02x%02x%02x%02x",
					 ISCSI_LOGIN_CURRENT_STAGE(login_pdu->
								   flags),
					 ISCSI_LOGIN_NEXT_STAGE(login_pdu->
								flags),
					 login_pdu->
					 flags & ISCSI_FLAG_LOGIN_TRANSIT,
					 login_pdu->isid[0], login_pdu->isid[1],
					 login_pdu->isid[2], login_pdu->isid[3],
					 login_pdu->isid[4],
					 login_pdu->isid[5]);
				iscsi_log_text(pdu, data);
				break;
			}
		case ISCSI_OP_TEXT_CMD:{
				struct IscsiTextHdr *text_pdu =
				(struct IscsiTextHdr *) pdu;

				debugmsg(4,
					 "sending text pdu with itt %u, "
					 "CmdSN %u:",
					 ntohl(text_pdu->itt),
					 ntohl(text_pdu->cmdsn));
				iscsi_log_text(pdu, data);
				break;
			}
		case ISCSI_OP_NOOP_OUT:{
				struct IscsiNopOutHdr *text_pdu =
				(struct IscsiNopOutHdr *) pdu;

				debugmsg(4,
					 "sending Nop-out pdu with itt %u, "
					 "ttt %u, CmdSN %u:",
					 ntohl(text_pdu->itt),
					 ntohl(text_pdu->ttt),
					 ntohl(text_pdu->cmdsn));
				iscsi_log_text(pdu, data);
				break;
			}
		default:
			debugmsg(4, "sending pdu opcode 0x%x:", pdu->opcode);
			break;
		}
	}

	// send the PDU header
	header = (char *) pdu;
	end = header + sizeof (*pdu) + pdu->hlength;

	while (header < end) {
		vec[0].iov_base = header;
		vec[0].iov_len = end - header;

		rc = writev(session->socket_fd, vec, 1);
		if (timedout) {
			logmsg(AS_ERROR, "socket %d write timed out",
			       session->socket_fd);
			ret = 0;
			goto done;
		}
		else if (rc == 0) {
			logmsg(AS_ERROR, "socket %d closed by target",
			       session->socket_fd);
			ret = 0;
			goto done;
		}
		else if ((rc < 0) && (errno != EAGAIN)) {
			errormsg("short PDU write on socket %d",
				 session->socket_fd);
			ret = 0;
			goto done;
		}
		else if (rc > 0) {
			debugmsg(4, "wrote %d bytes of PDU header", rc);
			header += rc;
		}
		if (iscsi_process_should_exit()) {
			ret = 0;
			goto done;
		}
	}

	// send all the data and any padding 
	if (pdu_length % PAD_WORD_LEN)
		pad_bytes = PAD_WORD_LEN - (pdu_length % PAD_WORD_LEN);
	else
		pad_bytes = 0;

	end = data + ntoh24(pdu->dlength);
	remaining = ntoh24(pdu->dlength) + pad_bytes;

	while (remaining > 0) {
		vec[0].iov_base = data;
		vec[0].iov_len = end - data;
		vec[1].iov_base = (void *) &pad;
		vec[1].iov_len = pad_bytes;

		rc = writev(session->socket_fd, vec, 2);
		if (timedout) {
			logmsg(AS_ERROR, "socket %d write timed out",
			       session->socket_fd);
			ret = 0;
			goto done;
		}
		else if (rc == 0) {
			logmsg(AS_ERROR, "socket %d closed by target",
			       session->socket_fd);
			ret = 0;
			goto done;
		}
		else if ((rc < 0) && (errno != EAGAIN)) {
			errormsg("short PDU write on socket %d",
				 session->socket_fd);
			ret = 0;
			goto done;
		}
		else if (rc > 0) {
			debugmsg(4, "wrote %d bytes of PDU data", rc);
			remaining -= rc;
			if (data < end) {
				data += rc;
				if (data > end)
					data = end;
			}
		}
		if (iscsi_process_should_exit()) {
			ret = 0;
			goto done;
		}
	}

	ret = 1;

	done:
	alarm(0);
	sigaction(SIGALRM, &old, NULL);
	timedout = 0;
	return ret;
}

int
iscsi_recv_pdu(struct iscsi_session *session, struct IscsiHdr *pdu,
	       int max_header_length, char *data, int max_data_length,
	       int timeout)
{
	uint32_t h_bytes = 0;
	uint32_t ahs_bytes = 0;
	uint32_t d_bytes = 0;
	uint32_t ahslength = 0;
	uint32_t dlength = 0;
	uint32_t pad = 0;
	int rlen = 0;
	int failed = 0;
	char *header = (char *) pdu;
	char *end = data + max_data_length;
	struct sigaction action;
	struct sigaction old;

	// set a timeout, since the socket calls may take a long 
	// time to timeout on their own 
	memset(&action, 0, sizeof (struct sigaction));
	memset(&old, 0, sizeof (struct sigaction));
	action.sa_sigaction = NULL;
	action.sa_flags = 0;
	action.sa_handler = sigalarm_handler;
	sigaction(SIGALRM, &action, &old);
	timedout = 0;
	alarm(timeout);

	// read a response header 
	do {
		rlen =
		read(session->socket_fd, header, sizeof (*pdu) - h_bytes);
		if (timedout) {
			logmsg(AS_ERROR, "socket %d header read timed out",
			       session->socket_fd);
			failed = 1;
			goto done;
		}
		else if (rlen == 0) {
			logmsg(AS_ERROR, "socket %d closed by target",
			       session->socket_fd);
			failed = 1;
			goto done;
		}
		else if ((rlen < 0) && (errno != EAGAIN)) {
			errormsg("short PDU header read from socket %d",
				 session->socket_fd);
			failed = 1;
			goto done;
		}
		else if (rlen > 0) {
			debugmsg(4, "read %d bytes of PDU header", rlen);
			header += rlen;
			h_bytes += rlen;
		}
		if (iscsi_process_should_exit()) {
			failed = 1;
			goto done;
		}
	} while (h_bytes < sizeof (*pdu));

	debugmsg(4,
		 "read %d PDU header bytes, opcode 0x%x, dlength %u, "
		 "data %p, max %u",
		 h_bytes, pdu->opcode, ntoh24(pdu->dlength), data,
		 max_data_length);

	// check for additional headers 
	ahslength = pdu->hlength;	// already includes padding 
	if (ahslength) {
		logmsg(LOG_NOTICE,
		       "additional header segment length %u not supported",
		       ahslength);
		failed = 1;
		goto done;
	}

	// read exactly what we expect, plus padding 
	dlength = pdu->dlength[0] << 16;
	dlength |= pdu->dlength[1] << 8;
	dlength |= pdu->dlength[2];

	if (data + dlength >= end) {
		logmsg(LOG_NOTICE,
		       "buffer size %u too small for data length %u",
		       max_data_length, dlength);
		failed = 1;
		goto done;
	}

	// read the rest into our buffer 
	d_bytes = 0;
	while (d_bytes < dlength) {
		rlen =
		read(session->socket_fd, data + d_bytes, dlength - d_bytes);
		if (timedout) {
			logmsg(AS_ERROR, "socket %d data read timed out",
			       session->socket_fd);
			failed = 1;
			goto done;
		}
		else if (rlen == 0) {
			logmsg(AS_ERROR, "socket %d closed by target",
			       session->socket_fd);
			failed = 1;
			goto done;
		}
		else if ((rlen < 0 && errno != EAGAIN)) {
			errormsg
			("short PDU data read from socket %d, "
			 "read %d of %d",
			 session->socket_fd, d_bytes, dlength);
			failed = 1;
			goto done;
		}
		else if (rlen > 0) {
			debugmsg(4, "read %d bytes of PDU data", rlen);
			d_bytes += rlen;
		}
		if (iscsi_process_should_exit()) {
			failed = 1;
			goto done;
		}
	}

	// handle PDU data padding 
	pad = dlength % PAD_WORD_LEN;
	if (pad) {
		int pad_bytes = pad = PAD_WORD_LEN - pad;
		char bytes[PAD_WORD_LEN];

		while (pad_bytes > 0) {
			rlen = read(session->socket_fd, &bytes, pad_bytes);
			if (timedout) {
				logmsg(AS_ERROR, "socket %d pad read timed out",
				       session->socket_fd);
				failed = 1;
				goto done;
			}
			else if (rlen == 0) {
				logmsg(AS_ERROR, "socket %d closed by target",
				       session->socket_fd);
				failed = 1;
				goto done;
			}
			else if ((rlen < 0 && errno != EAGAIN)) {
				errormsg("short PDU pad read from socket %d",
					 session->socket_fd);
				failed = 1;
				goto done;
			}
			else if (rlen > 0) {
				debugmsg(4, "read %d pad bytes", rlen);
				pad_bytes -= rlen;
			}
			if (iscsi_process_should_exit()) {
				failed = 1;
				goto done;
			}
		}
	}

	if (daemon_config.debug_level > 0) {
		switch (pdu->opcode) {
		case ISCSI_OP_TEXT_RSP:
			debugmsg(4,
				 "finished reading text PDU, %u hdr, %u "
				 "ah, %u data, %u pad",
				 h_bytes, ahs_bytes, d_bytes, pad);
			iscsi_log_text(pdu, data);
			break;
		case ISCSI_OP_LOGIN_RSP:{
				struct IscsiLoginRspHdr *login_rsp =
				(struct IscsiLoginRspHdr *) pdu;

				debugmsg(4,
					 "finished reading login PDU, %u hdr, "
					 "%u ah, %u data, %u pad",
					 h_bytes, ahs_bytes, d_bytes, pad);
				debugmsg(4,
					 "login current stage %d, next stage "
					 "%d, transit 0x%x",
					 ISCSI_LOGIN_CURRENT_STAGE(login_rsp->
								   flags),
					 ISCSI_LOGIN_NEXT_STAGE(login_rsp->
								flags),
					 login_rsp->
					 flags & ISCSI_FLAG_LOGIN_TRANSIT);
				iscsi_log_text(pdu, data);
				break;
			}
		case ISCSI_OP_ASYNC_EVENT:
			// FIXME: log the event info 
			break;
		default:
			break;
		}
	}

	done:
	alarm(0);
	sigaction(SIGALRM, &old, NULL);
	if (timedout || failed) {
		timedout = 0;
		return 0;
	}
	else {
		return h_bytes + ahs_bytes + d_bytes;
	}
} */




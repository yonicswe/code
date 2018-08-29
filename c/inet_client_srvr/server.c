
#ifndef MODULE
#define MODULE
#endif

#ifndef __KERNEL__
#define __KERNEL__
#endif

#include <linux/config.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

struct socket* listening_socket;
static unsigned int finish;


MODULE_PARM(srv_port,"i");
MODULE_PARM_DESC(srv_port,"server's listening port");

int 
init_listening_socket(unsigned int listen_port)
{
	if ( inet_sock_create(&listening_socket, OS_TCP_SOCK, TRUE) == OS_SOCK_ERROR) {
		goto failed_create_listening_socket;
	}
	if ( inet_sock_bind(listening_socket, usListeningPort, NULL) == OS_SOCK_ERROR ) {
		goto failed_bind_socket;
	}
	if (inet_sock_listen(listening_socket) == OS_SOCK_ERROR) {
		goto failed_listen_socket;
	}

	printk("%s: listen socket initialized\n",__func__);
	return 0;

failed_listen_socket:
failed_bind_socket:
	inet_sock_close(listening_socket);

failed_create_listening_socket:
	listening_socket = NULL;
	printk("%s: failed to bind socket, listening port: %u\n",__func__, listen_port);
	return 1;
}


void vAcceptConnections(void* p/*p_acpt_conn_param_t param*/)
{
	int iMaxTCPWinSize = MAX_TCP_WIN_SIZE;
	long lDataLength = BHS_SIZE;
	int iOne = 1;
	OS_Socket Socket;
	//OS_ERR os_status = OS_OK;

	INET_PTL_ConnDescriptor *pConnection = NULL;
	int Ret = 0;

	//os_status = OS_GiveMutex(param->thread_started);
	//if ( OS_OK != os_status ) {
	//    VD_LOG(VDLOG_ERROR, "%s: Error in notifying the creation of vAcceptConnections thread\n",__func__);
	//}

	ENTER_LOG;
	ITRACE(TRACE_INET_PTL_GEN,"%s: Listener thread started (no portals)\n",__func__);

	for (;;) {

		wait_event_interruptible(INET_states_wq,INET_accepting_state!=0);
		if (signal_pending(current)) {
			break;
		}
		ITRACE(TRACE_INET_PTL_GEN,"%s: going to listen (no portals)\n",__FUNCTION__);

		if ( OS_SockAccept( ListeningSocket, &Socket) != OS_SOCK_OK ) {
			if (signal_pending(current)) {
				break;
			}
			VD_LOG(VDLOG_ERROR,"%s: Failed to accept new connection.",__func__);
			continue;
		}

		/* Setting the socket to ignore Nagle Algorithm */
		OS_SockSetOpt(Socket, TCP_OPT_NODELAY, &iOne);

		/* Setting the Socket to signal only after receiving the whole BHS */
		OS_SockSetOpt(Socket, TCP_OPT_RCVLOWAT, &lDataLength);

		/* Set TCP window size */
		OS_SockSetOpt(Socket, TCP_OPT_RCVBUF, &iMaxTCPWinSize);
		OS_SockSetOpt(Socket, TCP_OPT_SNDBUF, &iMaxTCPWinSize);

		pConnection = kmem_cache_alloc(inet_conn_cache,GFP_KERNEL);
		if (pConnection == NULL) {
			VD_LOG(VDLOG_ERROR,"%s: Failed to allocate INET_PTL_ConnDescriptor!\n",__func__);
			continue;
		}
		vInitPTL_ConnDescriptor(pConnection);

		if (bAcceptNewConnection((ptl_conn_handle_t) pConnection,
					 &pConnection->itarget_conn_h, // this will return the itarget connectionInfo pointer
					 INET_CONN,
					 &inet_ptl_functions)             == FALSE) {
			VD_LOG(VDLOG_ERROR,"%s() bAcceptNewConnection Failed\n",__func__);
			OS_SockClose(Socket);
			// no need to free the pConnection since we did not initialize it yet
			continue;
		}
		printk("%s() bAcceptNewConnection Succeeded\n",__func__);
		ITRACE(TRACE_INET_PTL_GEN,
		       "%s: new connection requested from INET listen thread, "
		       "bAcceptNewConnection returned handle - conn=0x%p\n",
		       __func__, pConnection->itarget_conn_h);

		// Initialize the connection
		pConnection->enConnStatus = PTL_CONN_UP;
		pConnection->bDataDigest = FALSE;
		pConnection->bHeaderDigest = FALSE;

		/* Initializing the connection's Socket Parameters */
		pConnection->ConnSocketInfo.Socket = Socket;
		pConnection->ConnSocketInfo.ulRecvAccumData = 0;
		pConnection->ConnSocketInfo.ulRecvCurrBlockOffset = 0;
		pConnection->ConnSocketInfo.ulRecvCurrByteOffset = 0;
		pConnection->ConnSocketInfo.ulSendDataSize = 0;
		pConnection->ConnSocketInfo.ulRecvAdditionalDataSize = 0;
		pConnection->ConnSocketInfo.ulSendAdditionalDataSize = 0;
		pConnection->ConnSocketInfo.pRecvAdditionalDataBuff = NULL;
		pConnection->ConnSocketInfo.pSendAdditionalDataBuff = NULL;
		pConnection->ConnSocketInfo.enRecvSocketMode = SOKET_RCV_READY;

		// start the connection's thread
		Ret = iPassConnectionToThread(pConnection);
		if (Ret != 0) {
			kmem_cache_free(inet_conn_cache, pConnection);
			VD_LOG(VDLOG_ERROR,"%s: Failed to pass new connection to thread.",__func__);
			continue;
		}
	}
	ITRACE(TRACE_INET_PTL_GEN,"%s: Listener thread exited (no portals)\n",__func__);

	EXIT_LOG;
}


// int iPassConnectionToThread(INET_PTL_ConnDescriptor *pConnection)
// {
//
//        pConnection->RecvThread = OS_CreateThread((OS_ThreadFunc)vSinglePDUDecoder,
//                                                  (void*)pConnection/*(&pdu_sdc_param)*/,
//                                                  "inet_recv" );
//        if (pConnection->RecvThread == NULL) {
//                VD_LOG(VDLOG_ERROR,"%s(): failed to create decoder thread\n",__func__);
//                //OS_DestroyMutex( pdu_sdc_param.thread_started );
//                return -1;
//        }
//
//        ITRACE(TRACE_INET_PTL_GEN,
//               "%s() created inet_recv thread (desc=0x%p) for conn=0x%p\n",
//               __func__, pConnection->RecvThread, pConnection);
//
//        return 0;
// }


void 
start_server(unsigned int port)
{

	while (!finish) {
	 
		if ( inet_sock_accept(ListeningSocket, &Socket) != OS_SOCK_OK ) {
			 if (signal_pending(current)) {
				 break;
			 }
			 VD_LOG(VDLOG_ERROR,"%s: Failed to accept new connection.",__func__);
			 continue;
		 }

		printk("accecpted 
	 }
}

int 
init_module(void) 
{
	init_listening_socket(srv_port);
	
	start_server(srv_port);

	return 0;
}

void 
cleanup_module(void)
{
	printk("module exit\n");

}


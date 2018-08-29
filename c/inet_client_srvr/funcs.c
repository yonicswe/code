

int OS_SockCreate(OS_Socket *sock, OS_SOCK_TYPES enSockType, int bBlocking)
{
    int rc;
    int sock_type;

    //    sock_type = UseSDPSock ? 26 : PF_INET;
    sock_type = PF_INET;
    

    if ((rc = sock_create(sock_type, SOCK_STREAM, IPPROTO_TCP, sock))<0) {
        ITRACE(TRACE_INET_PTL_GEN,"%s() sock_create() ret=%d\n", __func__, rc);
    }

    (*sock)->sk->allocation = GFP_ATOMIC;

    if (rc < 0) 
        return OS_SOCK_ERROR;

    return OS_SOCK_OK;
}


int OS_SockBind(OS_Socket sock, USHORT port, char *strAddr)
{
    struct sockaddr_in laddr;
    int rc;

    memset((char *)&laddr, 0, sizeof(laddr));
    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(port);

    if(strAddr == NULL)
        laddr.sin_addr.s_addr  = INADDR_ANY;
    else if(!strcmp(strAddr,"0.0.0.0"))
        laddr.sin_addr.s_addr  = INADDR_ANY;
    else
        laddr.sin_addr.s_addr = OS_SockConvertAddr(strAddr);

    if( (rc = sock->ops->bind(sock, (struct sockaddr*) &laddr, sizeof(laddr))) < 0 ) {
        ITRACE(TRACE_INET_PTL_GEN,"%s() sock->ops->bind() return=%d\n", __func__, rc);
        return OS_SOCK_ERROR;
    }

    return OS_SOCK_OK;
}

/***********************************************************************
* Name: int OS_SockListen(OS_Socket sock)
*
* Purpose: Listen on the specified Socket.
*
* Algorithm: None
*
***********************************************************************/
int OS_SockListen(OS_Socket sock)
{
    int rc;

    if ((rc = sock->ops->listen(sock, 32))<0) {
        ITRACE(TRACE_INET_PTL_GEN,"%s() sock->ops->listen() return=%d\n",__func__, rc);
        return OS_SOCK_ERROR;
    }

    return OS_SOCK_OK;
}

/***********************************************************************
* Name: int OS_SockAccept(OS_Socket sock, OS_Socket *newsock)
*
* Purpose: Accept a connection request on a listening socket.
*
* Algorithm: None
*
***********************************************************************/
int OS_SockAccept(OS_Socket sock, OS_Socket *newsock)
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
            return OS_SIG;
        }
        else
        {
            ITRACE(TRACE_INET_PTL_GEN,"%s() newsock->ops->accept() return=%d\n",__func__, rv);
            return OS_SOCK_ERROR;
        }
    }

    return OS_SOCK_OK;
}



/***********************************************************************
* Name: int OS_SockClose(OS_Socket sock)
*
* Purpose: Close an active Socket and return its resources to the system.
*
* Algorithm: None
*
***********************************************************************/
int OS_SockClose(OS_Socket sock)
{
    int rv;

    if ((rv = sock->ops->release(sock)) != 0) 
    {
        ITRACE(TRACE_INET_PTL_GEN,"%s() sock->ops->release() ret=%d\n",__func__, rv);
        return OS_SOCK_ERROR;
    }

    return OS_SOCK_OK;
}

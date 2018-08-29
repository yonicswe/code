#include <stdio.h> 
#include <string.h> 
#include <infiniband/verbs.h> 

#include "common.h"

int responder(uint16_t            lid,
              struct ibv_cq*      send_cq,
              struct ibv_cq*      recv_cq,
              struct ibv_pd*      pd,
              char*               buf,
              struct ibv_mr*      mr)
{
    struct ibv_qp*          qp;
    struct ibv_qp_init_attr qp_init_attr;
    struct ibv_wc           wc;            // work completion
    uint16_t                dlid;
    uint32_t                dqpn;
    int                     r =0;

    //----------------------------------------------------------------------
    //  queue pair
    //----------------------------------------------------------------------
    memset(&qp_init_attr, 0, sizeof(qp_init_attr));

    qp_init_attr.send_cq          = send_cq;
    qp_init_attr.recv_cq          = recv_cq;
    //     qp_init_attr.qp_type          = IBV_QPT_UD;
    qp_init_attr.qp_type          = IBV_QPT_RC;
    qp_init_attr.cap.max_send_wr  = 2;
    qp_init_attr.cap.max_recv_wr  = 2;
    qp_init_attr.cap.max_send_sge = 1;
    qp_init_attr.cap.max_recv_sge = 1;

    qp = ibv_create_qp(pd, &qp_init_attr);
    if (!qp) 
    {
        fprintf(stderr, "%s() ibv_create_qp() failed\n", __func__);
        return -1;
    } 

    r = post_recv(buf + RECV_BUFFER(0), 
                  RECV_BUFFER_SIZE, 
                  mr, 
                  qp);
    if (0 != r)
        goto failed;

    printf("%s() post receive\n", __func__);

    modify_ud_qp(qp); 

    printf("%s() started with lid:qp: %lu:%lu\n", __func__, lid, qp->qp_num);

    while (0 == finish)
    {

        // wait for completion on recv Q
        while ( 0 == ibv_poll_cq(recv_cq, 1, &wc))
            usleep(100);

        if (wc.opcode != IBV_WC_RECV)
        {
            fprintf(stderr, "%s() opcode != IBV_WC_RECV on recv completion Q\n",__func__);
            r = -1;
            goto failed;
        }

        char* recv_msg = (char*) ((size_t)buf + RECV_BUFFER(0) + GRH_SIZE);
        size_t recv_msg_size = wc.byte_len - GRH_SIZE;
        recv_msg[recv_msg_size] = 0;
        printf("%s() received \"%s\"\n", __func__, recv_msg);

        // post a new buffer for receive
        r = post_recv(buf + RECV_BUFFER(0), 
                      RECV_BUFFER_SIZE, 
                      mr, 
                      qp);

        if (0 != r)
            goto failed;

        printf("%s() post receive\n", __func__);

        // send back the received msg.
        dlid = wc.slid;
        dqpn = wc.src_qp;

        strcat(recv_msg, "-ret");
        r = send_msg(dlid, dqpn, qp, pd, buf, mr, recv_msg); 
        if (0 != r)
        {
            fprintf(stderr, "%s() failed send_msg()\n", __func__);
            goto failed;
        } 

        while ( 0 == ibv_poll_cq(send_cq, 1, &wc))
        {
            if (IBV_WC_SEND == wc.opcode)
                break;
            sleep(1);
        } 

        printf("%s() sent \"%s\"\n", __func__, recv_msg);

    } // while


    return 0;

failed:    
    return r;
}

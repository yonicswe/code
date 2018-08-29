#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <signal.h>

#include <infiniband/verbs.h> 

#include "common.h"
#include "requester.h"
#include "responder.h"

int finish =0;

//======================================================
//          prototypes
//====================================================== 
int init_ib(struct ibv_context** ctx,
            uint16_t*            lid,
            struct ibv_pd**      pd, 
            char**               buf,
            struct ibv_mr**      mr,
            struct ibv_cq**      send_cq,
            struct ibv_cq**      recv_cq);

int destroy_ib(struct ibv_context* ctx,
               struct ibv_pd*      pd,
               char*               buf,
               struct ibv_mr*      mr,
               struct ibv_cq*      send_cq,
               struct ibv_cq*      recv_cq);

static int verbose_flag;

//======================================================
//          functions
//====================================================== 

void sig_handler(int signo)
{
    printf("%s() signal %d\n", __func__, signo);
    switch(signo)
    {
        case SIGUSR1:
        case SIGKILL:
        case SIGSTOP:
        case SIGTERM:
            finish =1;
            break;
        default:
            printf("%s() unknown signal\n", __func__);
    }
}

void register_signal_handler()
{
    if (signal(SIGUSR1, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGUSR1\n");
//     if (signal(SIGKILL, sig_handler) == SIG_ERR)
//         printf("\ncan't catch SIGKILL\n");
//     if (signal(SIGSTOP, sig_handler) == SIG_ERR)
//         printf("\ncan't catch SIGSTOP\n");
    if (signal(SIGTERM, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGTERM\n"); 
} 

int init_ib(struct ibv_context** ctx,
            uint16_t*            lid,
            struct ibv_pd**      pd, 
            char**               buf,
            struct ibv_mr**      mr,
            struct ibv_cq**      send_cq,
            struct ibv_cq**      recv_cq)
{
    struct ibv_context* ctx_ = NULL; 
    struct ibv_pd*      pd_ = NULL;
    struct ibv_mr*      mr_ = NULL;
    struct ibv_cq*      send_cq_ = NULL;
    struct ibv_cq*      recv_cq_ = NULL;
    char*               buf_ = NULL;
    struct ibv_device** dev_list;
    int                 r=0;

    // get only one device
    dev_list = ibv_get_device_list(NULL);

    if (NULL == dev_list)
    {
        printf("%s() cannot find ib device to use.\n", __func__);
        r = ENODEV;
        goto failed;
    }

    ctx_ = ibv_open_device(dev_list[0]);
    if (NULL == ctx_) 
    {
        fprintf(stderr, "%s() failed to open device '%s'\n",
                __func__, ibv_get_device_name(dev_list[0]));
        r = ENODEV;
        goto failed;
    } 

    struct ibv_port_attr port_attr;
    ibv_query_port(ctx_, 1, &port_attr);
    uint16_t lid_ = port_attr.lid;

    //----------------------------------------------------------------------
    //  protection domain
    //----------------------------------------------------------------------
    pd_ = ibv_alloc_pd(ctx_); 
    if (NULL == pd_)
    {
        fprintf(stderr, "%s() ibv_alloc_pd() failed\n", __func__);
        r = ENOMEM;
        goto failed; 
    }

    //----------------------------------------------------------------------
    //  memory region
    //----------------------------------------------------------------------
    buf_ = malloc(MR_SIZE);
    if (NULL == buf_) 
    {
        fprintf(stderr, "%s() failed to malloc(%d)\n", __func__, MR_SIZE);
        r = ENOMEM;
        goto failed;        
    }

    mr_ = ibv_reg_mr(pd_, 
                     buf_, 
                     MR_SIZE, 
                     IBV_ACCESS_LOCAL_WRITE |
                     IBV_ACCESS_REMOTE_WRITE | 
                     IBV_ACCESS_REMOTE_READ);
    if (NULL == mr_) 
    {
        fprintf(stderr, "%s() ibv_reg_mr() failed\n", __func__);
        r = ENOMEM;
        goto failed_mem;
    }

    //----------------------------------------------------------------------
    //  completion queues
    //----------------------------------------------------------------------
    send_cq_ = ibv_create_cq(ctx_, 
                             100, 
                             NULL, 
                             NULL,  // completion event channel
                             0);    // interrupt vector 
    if (NULL == send_cq_)
    { 
        fprintf(stderr, "%s() ibv_create_cq() failed\n", __func__);
        r = ENOMEM;
        goto failed_mem;
    } 

    recv_cq_ = ibv_create_cq(ctx_, 
                             100, 
                             NULL, 
                             NULL,  // completion event channel
                             0);    // interrupt vector 
    if (NULL == recv_cq_)
    { 
        fprintf(stderr, "%s() ibv_create_cq() failed\n", __func__);
        r = ENOMEM;
        goto failed_mem;
    } 

    *ctx = ctx_;
    *lid = lid_;
    *pd  = pd_;
    *buf = buf_;
    *mr  = mr_;
    *send_cq  = send_cq_;
    *recv_cq  = recv_cq_;
    
    return 0;

failed_mem:    
    // TODO: 
    //    ibv_dealloc_pd();
    //    ibv_close_device();

    free(buf_);

failed:
    return r;

}

int destroy_ib(struct ibv_context* ctx,
               struct ibv_pd*      pd,
               char*               buf,
               struct ibv_mr*      mr,
               struct ibv_cq*      send_cq,
               struct ibv_cq*      recv_cq)
{
    int r =0;

    r = ibv_destroy_cq(send_cq);
    if (0 != r)
    {
        fprintf(stderr, "%s() ibv_destroy_cq() failed\n", __func__);
        goto failed; 
    }

    r = ibv_destroy_cq(recv_cq);
    if (0 != r)
    {
        fprintf(stderr, "%s() ibv_destroy_cq() failed\n", __func__);
        goto failed; 
    }

    r = ibv_dereg_mr(mr);
    if (0 != r)
    {
        fprintf(stderr, "%s() ibv_dereg_mr() failed\n", __func__);
        goto failed;
    }

    r = ibv_dealloc_pd(pd);
    if (0 != r)
    {
        fprintf(stderr, "%s() ibv_dealloc_pd() failed\n", __func__);
        goto failed;
    }

    r = ibv_close_device(ctx);
    if (0 != r) 
    {
        fprintf(stderr, "%s() failed to close device '%s'\n", __func__, 
                ibv_get_device_name(ctx->device));
        goto failed;
    }


failed:
    free(buf);
    return r;    
}

int modify_ud_qp(struct ibv_qp *qp) 
{
    int r =0;

    struct ibv_qp_attr attr; 
    memset(&attr, 0, sizeof(attr));

    attr = (struct ibv_qp_attr) { 
            .qp_state   = IBV_QPS_INIT, 
            .pkey_index = 0,
            .port_num   = 1,    // physical port 
            .qkey       = QKEY 
    };

    r = ibv_modify_qp(qp, 
                      &attr,
                      IBV_QP_STATE | IBV_QP_PKEY_INDEX | IBV_QP_PORT | IBV_QP_QKEY);
    if (0 != r)
    {
        fprintf(stderr, "%s() ibv_modify_qp() failed transition to INIT\"%s\"\n", __func__, strerror(errno));
        goto failed;
    }

    memset(&attr, 0, sizeof(attr));
    attr.qp_state = IBV_QPS_RTR;
    r = ibv_modify_qp(qp, &attr, IBV_QP_STATE);
    if (0 != r)
    {
        fprintf(stderr, "%s() ibv_modify_qp() failed transition to RTR\n", __func__);
        goto failed;
    }

    memset(&attr, 0, sizeof(attr));
    attr.qp_state = IBV_QPS_RTS;
    attr.sq_psn = 0;
    r = ibv_modify_qp(qp, &attr, IBV_QP_STATE | IBV_QP_SQ_PSN);
    if (0 != r)
    {
        fprintf(stderr, "%s() ibv_modify_qp() failed transition to RTS\n", __func__);
        goto failed;
    }

    return 0;

failed:
    return r;    
}

int post_recv(unsigned char*  addr,
              size_t          recv_size,
              struct ibv_mr*  mr, 
              struct ibv_qp*  qp)
{
    int                  r=0;
    struct ibv_recv_wr*  recv_bad_wr;
    struct ibv_recv_wr   recv_wr;

    struct ibv_sge se = {
        .addr   = (uintptr_t)addr, 
        .length = recv_size,
        .lkey   = mr->lkey
    };

    memset(&recv_wr, 0, sizeof(recv_wr));

    recv_wr = (struct ibv_recv_wr) {
        .wr_id   = 0,
        .next    = NULL,
        .sg_list = &se,
        .num_sge = 1
    };


    r = ibv_post_recv(qp, &recv_wr, &recv_bad_wr);
    if (0 != r)
    {
        fprintf(stderr, "%s() ibv_port_recv() failed\n", __func__); 
    }

    return r;

}

int send_msg(uint16_t        dlid,  // destination LID
             uint16_t        dqpn,  // destination QP number
             struct ibv_qp*  qp,
             struct ibv_pd*  pd,
             char*           buf,
             struct ibv_mr*  mr, 
             char*           msg)
{
    int                r=0; 
    struct ibv_ah_attr ah_attr;
    struct ibv_ah*     ah;

    //========================================================
    // address handle
    //========================================================
    memset(&ah_attr, 0, sizeof(ah_attr));
    ah_attr = (struct ibv_ah_attr) {
        .dlid          = dlid,
        .sl            = 0,
        .src_path_bits = 0,
        .static_rate   = 0xFF,
        .is_global     = 0,
        .port_num      = 1    
    };

    ah = ibv_create_ah(pd, &ah_attr);
    if (NULL == ah)
    {
        fprintf(stderr, "%s() ibv_create_ah failed\n", __func__);
        r = -1;
        goto failed;
    }

    char* send_buffer = buf + SEND_BUFFER(0);
    size_t msg_size   = strlen(msg);
    msg_size = (msg_size > SEND_BUFFER_SIZE) ? SEND_BUFFER_SIZE : msg_size;
    strncpy(send_buffer, msg, msg_size);


    struct ibv_sge       ge; 
    memset(&ge, 0, sizeof(ge));

    ge = (struct ibv_sge) {
        .addr   = (uintptr_t) send_buffer, 
        .length = msg_size,
        .lkey   = mr->lkey
    };

    struct ibv_send_wr   send_wr;
    struct ibv_send_wr*  s_bad_wr;
    memset(&send_wr, 0, sizeof(send_wr));

    send_wr = (struct ibv_send_wr) {
        .wr_id             = 1, 
        .next              = NULL,
        .sg_list           = &ge,
        .num_sge           = 1,
        .opcode            = IBV_WR_SEND,
        .send_flags        = IBV_SEND_SIGNALED,
        .wr.ud.remote_qpn  = dqpn,
        .wr.ud.remote_qkey = QKEY,
        .wr.ud.ah          = ah
    };

    r = ibv_post_send(qp, &send_wr, &s_bad_wr);
    if (r = 0)
        goto failed;


    return 0;

failed:
    return r;        
}

void usage()
{
    printf("Usage: --client <qp> --message \"message\"\n");
    printf("       --server <qp>\n");
}

int main (int argc, char** argv)
{
    int                 c;
    int                 r;
    int                 requester_mode=0;
    int                 responder_mode=0;
    uint16_t            dlid;
    uint32_t            dqpn;
    char*               message=NULL; 
    struct ibv_context* ctx = NULL;
    uint16_t            lid = 0;
    struct ibv_pd*      pd = NULL;
    char*               buf = NULL;
    struct ibv_mr*      mr = NULL; 
    struct ibv_cq*      send_cq = NULL;
    struct ibv_cq*      recv_cq = NULL;

    if (1 == argc)
        usage();

    register_signal_handler();

    while (1)
    {
        static struct option long_options[] =
        {
            {"verbose", no_argument,       &verbose_flag,   1},
            {"brief",   no_argument,       &verbose_flag,   0},
            {"help",    no_argument,       0,             'h'},
            {"client",  required_argument, 0,             'c'},
            {"server",  no_argument,       0,             's'},
            {"message", required_argument, 0,             'm'},
            {0, 0, 0, 0}
        };

        int option_index = 0;

        c = getopt_long_only (argc, 
                argv, 
                "hc:s:m:",
                long_options, 
                &option_index);

        if (c == -1)
            break;

        switch (c)
        {
            case 0:
                // If this option set a flag, do nothing else now. 
                if (long_options[option_index].flag != 0)
                    break;

                printf ("option %s", long_options[option_index].name);
                if (optarg)
                    printf (" with arg %s", optarg);

                printf ("\n");

                break;

            case 'h':
                usage();
                break;

            case 'c':
                requester_mode=1;
                char* token;
                token = strtok(optarg, ":");
                dlid =  strtol(token, NULL, 10);
                token = strtok(NULL, ":");
                dqpn = strtol(token, NULL, 10);
                break;

            case 's':
                responder_mode=1;
                break;

            case 'm':
                // printf ("requester message `%s'\n", optarg);
                message = malloc(strlen(optarg));
                strncpy(message, optarg, strlen(optarg));
                break;

            case '?':
                break;

            default:
                abort ();
        }
    }

    if (verbose_flag)
        puts ("verbose flag is set");

    if (optind < argc)
    {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);

        putchar ('\n');
    }

    //----------------------------------------------------------------------
    //  init
    //----------------------------------------------------------------------
    if (1 == requester_mode || 1 == responder_mode)
    {
        r = init_ib(&ctx, &lid,  &pd, &buf, &mr, &send_cq, &recv_cq);
        if (0 != r)
            goto failed;
    }

    //----------------------------------------------------------------------
    //  run
    //----------------------------------------------------------------------
    if (1 == requester_mode)
    { 
        r = requester(dlid, dqpn, message, send_cq, recv_cq, pd, buf, mr);

        if (NULL != message)
            free(message);

        if (0 != r)
            goto failed;
    }
    else if (1 == responder_mode)
    {
        r =  responder(lid, send_cq, recv_cq, pd, buf, mr);
        if (0 != r)
            goto failed;
    } 

    //----------------------------------------------------------------------
    //  destroy
    //----------------------------------------------------------------------
    if (1 == requester_mode || 1 == responder_mode)
    {
        r = destroy_ib(ctx, pd, buf, mr, send_cq, recv_cq);
        if (0 != r)
            goto failed;
    }

    exit (0);

failed:    
    exit(-1);
}


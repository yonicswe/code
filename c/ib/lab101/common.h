#pragma once


#define QKEY 0x1111

#define GRH_SIZE          40
#define MAX_PAYLOAD       60

#define RECV_BUFFER_SIZE      (GRH_SIZE + MAX_PAYLOAD)
#define RECV_BUFFER_COUNT     10 
#define RECV_BUFF_VEC_SIZE    (RECV_BUFFER_SIZE * RECV_BUFFER_COUNT)

#define SEND_BUFFER_SIZE      RECV_BUFFER_SIZE
#define SEND_BUFFER_COUNT     5
#define SEND_BUFFER_VEC_SIZE  (SEND_BUFFER_SIZE * SEND_BUFFER_COUNT)

//  +----+----+----+----+----+----+----+----+----+----+----+
//  |    |    |    |    |    |    |    |    |    |    |    |
//  +----+----+----+----+----+----+----+----+----+----+----+
//  |<---- recv buffers ---->|<------  send buffers ------>|
//  |                                                      |
//  |<---------------- MR_SIZE --------------------------->|

#define RECV_BUFFER(i) ( (i % RECV_BUFFER_COUNT) * RECV_BUFFER_SIZE )
#define SEND_BUFFER(i) ( RECV_BUFF_VEC_SIZE + ( (i % SEND_BUFFER_COUNT) * SEND_BUFFER_SIZE) ) 

#define MR_SIZE (RECV_BUFF_VEC_SIZE + SEND_BUFFER_VEC_SIZE)

extern int finish;
int modify_ud_qp(struct ibv_qp *qp);

int post_recv(unsigned char*  addr,
              unsigned long   recv_size,
              struct ibv_mr*  mr, 
              struct ibv_qp*  qp); 

int send_msg(uint16_t        dlid,  // destination LID
             uint16_t        dqpn,  // destination QP number
             struct ibv_qp*  qp,    // local qp
             struct ibv_pd*  pd,
             char*           buf,
             struct ibv_mr*  mr, 
             char*           msg);

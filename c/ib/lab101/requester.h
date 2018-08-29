#pragma once

int requester(uint16_t            dlid,    // destination LID
              uint32_t            dqpn,    // destination QP number 
              const char*         message,
              struct ibv_cq*      send_cq,
              struct ibv_cq*      recv_cq,
              struct ibv_pd*      pd,
              char*               buf,
              struct ibv_mr*      mr);


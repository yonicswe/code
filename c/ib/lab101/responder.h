#pragma once

int responder(uint16_t            lid,
              struct ibv_cq*      send_cq,
              struct ibv_cq*      recv_cq,
              struct ibv_pd*      pd,
              char*               buf,
              struct ibv_mr*      mr);


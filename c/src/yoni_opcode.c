
#include <stdlib.h>

/* Initiator iSCSI opcodes   */
#define NOP_OUT_PDU_OPCODE              0x00 /* NOP-Out */
#define SCSI_CMD_PDU_OPCODE             0x01 /* SCSI Command */
#define TASK_MNG_PDU_OPCODE             0x02 /* SCSI Task Management Function Request */
#define LOG_IN_OPCODE                   0x03 /* Login Request */
#define TEXT_REQ_PDU_OPCODE             0x04 /* Text Request */
#define DATA_WRITE_PDU_OPCODE           0x05 /* SCSI Data-out (for WRITE operations) */
#define LOG_OUT_PDU_OPCODE              0x06 /* Logout Request */
#define SNACK_PDU_OPCODE                0x10 /* SNACK Request */


/* Target iSCSI opcodes */
#define NOP_IN_PDU_OPCODE               0x20 /* NOP-In */
#define SCSI_RES_PDU_OPCODE             0x21 /* SCSI Response */
#define TASK_MNG_RES_PDU_OPCODE         0x22 /* SCSI Task Management Function Response */
#define LOG_IN_RESPONSE                 0x23 /* Login Response */
#define TEXT_RES_PDU_OPCODE             0x24 /* Text Response */
#define DATA_READ_PDU_OPCODE            0x25 /* SCSI Data-in */
#define LOG_OUT_RESPONSE                0x26 /* Logout Response */
#define R2T_PDU_OPCODE                  0x31 /* Ready To Transfer (R2T) */
#define ASYNC_PDU_OPCODE                0x32 /* Asynchronous Message */
#define REJECT_OPCODE                   0x3F /* Reject */

char *opcode_str[0x3f];

void
init_opcode_str(void)
{
    opcode_str[NOP_OUT_PDU_OPCODE       ]="NOP_OUT_PDU_OPCODE     ";
    opcode_str[SCSI_CMD_PDU_OPCODE      ]="SCSI_CMD_PDU_OPCODE    ";
    opcode_str[TASK_MNG_PDU_OPCODE      ]="TASK_MNG_PDU_OPCODE    ";
    opcode_str[LOG_IN_OPCODE            ]="LOG_IN_OPCODE          ";
    opcode_str[TEXT_REQ_PDU_OPCODE      ]="TEXT_REQ_PDU_OPCODE    ";
    opcode_str[DATA_WRITE_PDU_OPCODE    ]="DATA_WRITE_PDU_OPCODE  ";
    opcode_str[LOG_OUT_PDU_OPCODE       ]="LOG_OUT_PDU_OPCODE     ";
    opcode_str[SNACK_PDU_OPCODE         ]="SNACK_PDU_OPCODE       ";
    opcode_str[NOP_IN_PDU_OPCODE        ]="NOP_IN_PDU_OPCODE      ";
    opcode_str[SCSI_RES_PDU_OPCODE      ]="SCSI_RES_PDU_OPCODE    ";
    opcode_str[TASK_MNG_RES_PDU_OPCODE  ]="TASK_MNG_RES_PDU_OPCODE";
    opcode_str[LOG_IN_RESPONSE          ]="LOG_IN_RESPONSE        ";
    opcode_str[TEXT_RES_PDU_OPCODE      ]="TEXT_RES_PDU_OPCODE    ";
    opcode_str[DATA_READ_PDU_OPCODE     ]="DATA_READ_PDU_OPCODE   ";
    opcode_str[LOG_OUT_RESPONSE         ]="LOG_OUT_RESPONSE       ";
    opcode_str[R2T_PDU_OPCODE           ]="R2T_PDU_OPCODE         ";
    opcode_str[ASYNC_PDU_OPCODE         ]="ASYNC_PDU_OPCODE       ";
    opcode_str[REJECT_OPCODE            ]="REJECT_OPCODE          ";
}

int 
main (int argc, char *argv[])
{

    int opcode;
    opcode = atoi(argv[1]);

    init_opcode_str();

    if (opcode < NOP_OUT_PDU_OPCODE || opcode > REJECT_OPCODE) {
        printf("unknown opcode\n");
        return 0;
    }

    printf("opcode = %s\n",opcode_str[opcode]);
}

/*
 * Copyright (C) Voltaire Ltd. 2004.  ALL RIGHTS RESERVED.
 *
 * Description: SDP proxy PDU transport layer.
 */

#include <linux/slab.h>

#include "os_types.h"
#include "os_funcs.h"
#include "bhs.h"
#include "ptl_types.h"
#include "mem_pool.h"
#include "pdu_info.h"
#include "devs_mapper.h"
#include "task_info.h"
#include "mem_util.h"
#include "negotiations.h"
#include "connection_info.h"
#include "itarget_types.h"
#include "itarget.h"
#include "scsi_interface.h"
#include "cmd_pdu_handler.h"
#include "iser_types.h"
#include "iser_api.h"
#include "iser_ext_api.h"
#include "iser_ptl.h"
#include "itarget_init.h"
#include "itargetManagementConstants.h"
#include "itargetManagementDatatypes.h"
#include "session.h"
#include "session_mgr.h"
#include "perf.h"
#include "trace.h"

//===============================================
//              Globals
//===============================================
struct iser_ptl_global_t iser_ptl_global;
//char *opcodes[0x3f];
char *iser_buf_types[4];

extern int enable_conn_req;

//===============================================
//              prototypes.
//===============================================
#define STATIC

//--------------------------
// call-back functions to be invoked by iscsi
// registered via NewConnectionRequest(..,struct ptl_functions,..)
//--------------------------
STATIC int iser_ptl_remove_conn(ptl_conn_handle_t, int );
STATIC ptl_ret_t iser_ptl_send_pdu(ptl_conn_handle_t, PDUInfo*, int);
STATIC void iser_ptl_set_header_digest(ptl_conn_handle_t);
STATIC void iser_ptl_set_data_digest(ptl_conn_handle_t);
STATIC void init_debug_str(void);
STATIC void iscsi_to_iser_pdu(PDUInfo*, struct iser_send_pdu_t*);
STATIC int iser_to_iscsi_pdu(struct iser_recv_pdu_t*, struct iser_ptl_conn_t*, PDUInfo**);
STATIC int save_iser_pdu_to_task(struct iser_ptl_task_t*, struct iser_recv_pdu_t*);
STATIC void iser_ptl_delete_connection_list(struct list_head *head_ptr);
STATIC void iser_ptl_delete_connection(struct iser_ptl_conn_t *ptl_conn_p);
STATIC void iser_ptl_delete_task_list(struct list_head*);
STATIC void iser_ptl_delete_task(struct iser_ptl_task_t*);
STATIC int release_iser_pdus_from_task(struct iser_ptl_task_t* , struct iser_ptl_conn_t*);
void print_iscsi_pdu_data_buf(char*, unsigned int);
void print_iser_pdu(struct iser_recv_pdu_t*, struct iser_ptl_conn_t*);
void print_iscsi_pdu(PDUInfo* iscsi_pdu,int trace_ctxt,char *msg_str);
STATIC ptl_ret_t iser_ptl_get_data_in_buffer(UINT,UINT,SG_ListInfo **,SG_ListInfo **, int);

//===============================================
//              Declarations
//===============================================

STATIC void
init_debug_str(void)
{
/*     opcodes[PDU_OPCODE_NOP_OUT       ]="NOP_OUT"; */
/*     opcodes[PDU_OPCODE_SCSI_CMD      ]="SCSI_CMD"; */
/*     opcodes[PDU_OPCODE_TASK_MNG_REQ  ]="TASK_MNG_REQ"; */
/*     opcodes[PDU_OPCODE_LOGIN_REQ     ]="LOGIN_REQ"; */
/*     opcodes[PDU_OPCODE_TEXT_REQ      ]="TEXT_REQ"; */
/*     opcodes[PDU_OPCODE_DATA_OUT      ]="DATA_OUT"; */
/*     opcodes[PDU_OPCODE_LOGOUT_REQ    ]="LOGOUT_REQ"; */
/*     opcodes[PDU_OPCODE_SNACK         ]="SNACK"; */
/*     opcodes[PDU_OPCODE_NOP_IN        ]="NOP_IN"; */
/*     opcodes[PDU_OPCODE_SCSI_RESPONSE ]="SCSI_RESPONSE"; */
/*     opcodes[PDU_OPCODE_TASK_MNG_RESP ]="TASK_MNG_RESP"; */
/*     opcodes[PDU_OPCODE_LOGIN_RESP    ]="LOGIN_RESP"; */
/*     opcodes[PDU_OPCODE_TEXT_RESP     ]="TEXT_RESP"; */
/*     opcodes[PDU_OPCODE_DATA_IN       ]="DATA_IN"; */
/*     opcodes[PDU_OPCODE_LOGOUT_RESP   ]="LOGOUT_RESP"; */
/*     opcodes[PDU_OPCODE_R2T           ]="R2T"; */
/*     opcodes[PDU_OPCODE_ASYNC_MSG     ]="ASYNC_MSG"; */
/*     opcodes[PDU_OPCODE_REJECT        ]="REJECT"; */

    iser_buf_types[ISER_BUF_TYPE_SINGLE     ]="ISER_BUF_TYPE_SINGLE";
    iser_buf_types[ISER_BUF_TYPE_IOVEC_VIRT ]="ISER_BUF_TYPE_IOVEC_VIRT";
    iser_buf_types[ISER_BUF_TYPE_IOVEC_PHYS ]="ISER_BUF_TYPE_IOVEC_PHYS";
    iser_buf_types[ISER_BUF_TYPE_SCATTERLIST]="ISER_BUF_TYPE_SCATTERLIST";
}


//---------------------------------------------------------------------------
/*!
  @description
  print a buffer filled with string seperated with '\0'.
  replace '\0' with ' ' then print the buffer.
  @returns
*/
//---------------------------------------------------------------------------
void
print_iscsi_pdu_data_buf(char* data_buf,     //!< IN - iscsi pdu data buffer.
                         unsigned int size)  //!< IN - the buffer size
{
    char buffer[1024];

    int i;

    if (data_buf == NULL) {
        return;
    }

    if (size != 0 && data_buf != NULL) {

        for (i=0 ; i < size && i<1023 ; i++) {
            if ( data_buf[i] != '\0')
                buffer[i] = data_buf[i];
            else
                buffer[i] = ' ';
        }

        buffer[i] = '\0';

        ITRACE(TRACE_ISER_PTL_PDU_DATA,"%s\n",buffer);
    }
}

//---------------------------------------------------------------------------
/*!
  @description
  print an iser pdu.
  @returns
*/
//---------------------------------------------------------------------------
void
print_iser_pdu(
              struct iser_recv_pdu_t  *p_ctrl_pdu,
              struct iser_ptl_conn_t  *ptl_conn_p)
{
    ScsiCmdPduHdr *iscsi_bhs_p = (ScsiCmdPduHdr *)p_ctrl_pdu->p_bhs;
    DWORD itt = ntohl(iscsi_bhs_p->itt);
    DWORD received_data_size = ntohl( ((ScsiCmdPduHdr *)p_ctrl_pdu->p_bhs->buf)->ulDataLength );

    UINT opcode=PDUOPCODE_MASK(iscsi_bhs_p->byOpcode);

    ITRACE(TRACE_ISER_PTL_PDU_DATA,
           "%s() received %s, pdu=0x%p ITT:0x%X, dsl=%d, iser(buf=0x%p, len=%u) from conn=0x%p\n",
           __func__,
           opcode_of(opcode),
           p_ctrl_pdu,
           itt,
           received_data_size,
           p_ctrl_pdu->rx_data.p_buf,
           p_ctrl_pdu->rx_data.size,
           ptl_conn_p);

    if (p_ctrl_pdu->rx_data.p_buf != NULL &&
        ((opcode == PDU_OPCODE_LOGIN_RESP) || (opcode == PDU_OPCODE_LOGIN_REQ)) ) {

        ITRACE(TRACE_ISER_PTL_PDU_DATA,
               "%s() iser.buf.type=%s, data: ",
               __func__,iser_buf_types[p_ctrl_pdu->rx_data.type]);

        print_iscsi_pdu_data_buf(p_ctrl_pdu->rx_data.p_buf,
                                 p_ctrl_pdu->rx_data.size);
    }
}

//---------------------------------------------------------------------------
/*!
  @description
  print an iser pdu.
  @returns
*/
//---------------------------------------------------------------------------
void
print_iscsi_pdu(PDUInfo* iscsi_pdu,
                int trace_ctxt,
                char *msg_str)
{
	ScsiCmdPduHdr *iscsi_bhs_p;
	DWORD itt;
	DWORD dsl;
	UINT opcode;
	struct ConnectionInfo *pConn;

	if (iscsi_pdu == NULL) {
		VD_LOG(VDLOG_ERROR,"%s: (%s) - NULL PDU\n",__func__,msg_str);
		return;
        }

	iscsi_bhs_p = (ScsiCmdPduHdr *)iscsi_pdu->BHS;
	itt = ntohl(iscsi_bhs_p->itt);
	dsl = ntohl( iscsi_bhs_p->ulDataLength );
	opcode = PDUOPCODE_MASK(iscsi_bhs_p->byOpcode);
	pConn = iscsi_pdu->pConn;

	if (trace_ctxt >= 0)
		ITRACE(trace_ctxt,
		       "%s: %s, pdu: %s, ITT:0x%X, dsl=%u, PDUInfo:0x%p, Conn:0x%p\n",
		       __func__, msg_str, opcode_of(opcode), itt,
		       dsl, iscsi_pdu, pConn);
	else
		VD_LOG(VDLOG_ERROR,
		       "%s: %s, pdu: %s, ITT:0x%X, dsl=%u, PDUInfo:0x%p, Conn:0x%p\n",
		       __func__, msg_str, opcode_of(opcode), itt,
		       dsl, iscsi_pdu, pConn);
}
//---------------------------------------------------------------------------
/*!
  @description
  print a connection's task list.
  assume that the task_list is locked.
  @returns
*/
//---------------------------------------------------------------------------
STATIC void
print_task_list(struct iser_ptl_conn_t *ptl_conn_p)
{
    int curr=0;
    char tmp_buf[100] = {0};
    char buffer[0x800] = {0};

    struct list_head* list_ptr;
    struct iser_ptl_task_t* ptl_task_p;

    list_for_each (list_ptr, &ptl_conn_p->task_list_head){
        ptl_task_p = list_entry(list_ptr, struct iser_ptl_task_t, task_list);

        sprintf(tmp_buf, "(ITT:0x%X, task=0x%p)->",ptl_task_p->itt, ptl_task_p);
        strcpy (&buffer[curr], tmp_buf);
        curr += strlen(tmp_buf);

        if (curr >= 0x800)
            break;

        tmp_buf[0]='\0';
    }

    ITRACE(TRACE_ISER_PTL_TASK,"TaskList(size=%u): %s\n",ptl_conn_p->task_list_size, buffer);
}

//---------------------------------------------------------------------------
/*!
  @description
  convert a PDU from iTarget's format to iSER's format.

  @returns
*/
//---------------------------------------------------------------------------
STATIC void
iscsi_to_iser_pdu(PDUInfo* iscsi_pdu,                //!< IN - iTarget's pdu to convert
                  struct iser_send_pdu_t* iser_pdu)  //!< OUT - iSER converted.
{
    SG_ListInfo *pDataSgList;
    SG_Entry *pListHead;
    unsigned int sg_list_sz;
    struct scatterlist *scatter_list;

    ENTER_LOG;

    iser_pdu->p_bhs = (union iser_pdu_bhs_t*)iscsi_pdu->BHS;

    pDataSgList = iscsi_pdu->pDataPtr;
    if (pDataSgList == NULL) {
        iser_pdu->data.tx.buf.p_buf = NULL;
        iser_pdu->data.tx.buf.size = 0;
        iser_pdu->data.tx.buf.type = ISER_BUF_TYPE_SINGLE;
	iscsi_pdu->scatterlist = NULL;
    }
    else {
	sg_list_sz = pDataSgList->SG_EntriesNum;
        if (sg_list_sz == 1) {
            pListHead = pDataSgList->pListHead;
            if (pListHead == NULL) {
                VD_LOG(VDLOG_PANIC,
                       "%s: PDU:0x%p, SgList:0x%p has NULL SgEntry\n",
                       __func__, iscsi_pdu, pDataSgList);
                BUG();
            }
            iser_pdu->data.tx.buf.p_buf = pListHead->pBuff;
            iser_pdu->data.tx.buf.size = pListHead->ulValidDataSize;
            iser_pdu->data.tx.buf.type = ISER_BUF_TYPE_SINGLE;
	    iscsi_pdu->scatterlist = NULL;
	}
	else {
	    scatter_list = kmalloc(sg_list_sz * sizeof(struct scatterlist),GFP_KERNEL);
	    panic_on(scatter_list == NULL);
	    build_st(scatter_list,pDataSgList);
	    iscsi_pdu->scatterlist = scatter_list;

	    iser_pdu->data.r2t.dst_buf.p_buf = scatter_list;
	    iser_pdu->data.r2t.dst_buf.size = sg_list_sz;
	    iser_pdu->data.r2t.dst_buf.type = ISER_BUF_TYPE_SCATTERLIST;
	}
    }
    EXIT_LOG;
}

//---------------------------------------------------------------------------
/*!
  @description
  convert ISER's PDU to iTarget's PDU.

  @returns
*/
//---------------------------------------------------------------------------
STATIC int
iser_to_iscsi_pdu(struct iser_recv_pdu_t  *p_ctrl_pdu,     //!< IN - ISER's pdu to convert
                  struct iser_ptl_conn_t* ptl_conn_p, //!< IN - ISER PDU received from connection
                  PDUInfo** iscsi_pdu)                     //!< OUT - iTarget's converted.
{
    PDUInfo *pPdu;

    // allocate a PDU descriptor.
    pPdu = vPDUAllocHandler(ptl_conn_p->iscsi_conn_h);
    if (pPdu == NULL) {
        VD_LOG(VDLOG_ERROR,
               "failed allocating PDU, p_conn=0x%p, \n",
               ptl_conn_p->iscsi_conn_h);
        *iscsi_pdu = NULL;
        return FALSE;
    }

    // this is not fake pdu.
    pPdu->rdma_pdu = 0;

    // copy BHS
    memcpy((void*)(pPdu->BHS),
           (void*)(p_ctrl_pdu->p_bhs),
           BHS_SIZE);

    *iscsi_pdu = pPdu;

    return TRUE;
}


//---------------------------------------------------------------------------
/*!
  @description
  save a received pdu from iser layer on its pertaining task.

  @returns
*/
//---------------------------------------------------------------------------
STATIC int
save_iser_pdu_to_task(struct iser_ptl_task_t* ptl_task_p, //!< IN - pdu is saved on this task
                      struct iser_recv_pdu_t* p_ctrl_pdu)      //!< IN received iser pdu.
{
    spin_lock(&ptl_task_p->task_lock);

    if (p_ctrl_pdu != NULL) {
        list_add_tail(&p_ctrl_pdu->pdu_list,&ptl_task_p->release_list_head);
        ITRACE(TRACE_ISER_PTL_TASK,
               "%s() Saved iser-pdu=0x%p to Task=0x%p\n",
               __func__, p_ctrl_pdu, ptl_task_p);
    }

    spin_unlock(&ptl_task_p->task_lock);
    return TRUE;
}


//---------------------------------------------------------------------------
/*!
  Function:  iser_ptl_delete_connection_list

  Parameters: head_ptr - head of the connection list to delete.

  Description:
        remove the entire connection list.
*/
//---------------------------------------------------------------------------
STATIC void
iser_ptl_delete_connection_list(struct list_head *head_ptr)
{

	struct list_head *list_ptr;
	struct list_head *conn_to_delete;
	struct iser_ptl_conn_t* ptl_conn_p;

	ENTER_LOG;

    spin_lock(&iser_ptl_global.conn_list_lock);
	list_for_each_safe(conn_to_delete, list_ptr, head_ptr) {
        ptl_conn_p = list_entry(conn_to_delete,
                                struct iser_ptl_conn_t,
                                conn_list);
		iser_ptl_delete_connection(ptl_conn_p);
	}
    spin_unlock(&iser_ptl_global.conn_list_lock);

	EXIT_LOG;
}


//---------------------------------------------------------------------------
/*!
  Function:  iser_ptl_delete_connection

  Parameters: iscsi_conn_p - the connection to delete.

  Description:
        deltes one connection.
*/
//---------------------------------------------------------------------------
STATIC void
iser_ptl_delete_connection(struct iser_ptl_conn_t *ptl_conn_p)
{
    struct iser_recv_pdu_t *delayed_pdu;
    iser_status_t iser_ret;

    ENTER_LOG;

    delayed_pdu = ptl_conn_p->delayed_pdu;
    if (delayed_pdu != NULL) {
        ptl_conn_p->delayed_pdu = NULL;
        iser_ret = iser_ptl_global.iser_api.release_control(ptl_conn_p,
                                                            delayed_pdu);
        if (iser_ret != ISER_SUCCESS) {
            VD_LOG(VDLOG_ERROR,
                   "%s: Failed release_control for delayed pdu:0x%p (%u)\n",
                   __func__, delayed_pdu, iser_ret);
        }
    }

    spin_lock(&ptl_conn_p->task_list_lock);
    iser_ptl_delete_task_list(&ptl_conn_p->task_list_head);
    if(ptl_conn_p->task_list_size != 0){
	    VD_LOG(VDLOG_PANIC,
		   "%s():%d after deleting connection task list, count = %d\n",
		   __func__,__LINE__,ptl_conn_p->task_list_size);
	    BUG();
    }
    spin_unlock(&ptl_conn_p->task_list_lock);

    spin_lock(&iser_ptl_global.conn_list_lock);
    if (iser_ptl_global.conn_list_size == 0) {
        spin_unlock(&ptl_conn_p->task_list_lock);
        VD_LOG(VDLOG_ERROR,
               "%s: failed to remove connection:0x%p, conn-list empty\n",
               __func__, ptl_conn_p);
        goto exit_delete_connection;
    }
    // remove the connection from the global connection list.
    list_del_init(&ptl_conn_p->conn_list);
    iser_ptl_global.conn_list_size --;
    ITRACE(TRACE_ISER_PTL_GEN,
           "%s: Removing conn:0x%p, remains %u connections\n",
           __func__, ptl_conn_p, iser_ptl_global.conn_list_size);
    spin_unlock(&iser_ptl_global.conn_list_lock);

    kmem_cache_free(iser_ptl_global.conn_slab, ptl_conn_p);

 exit_delete_connection:
    EXIT_LOG;
}

//---------------------------------------------------------------------------
/*!
  Function:  iser_ptl_delete_task_list

  Parameters: head_ptr - head of a connection's task list to delete.

  Description:
        remove the entire task list.
*/
//---------------------------------------------------------------------------
STATIC void
iser_ptl_delete_task_list(struct list_head *head_ptr)
{
    struct list_head *list_ptr;
    struct list_head *task_to_delete;
    struct iser_ptl_task_t* ptl_task_p;

    ENTER_LOG;

    list_for_each_safe(task_to_delete, list_ptr, head_ptr){

        ptl_task_p = list_entry(task_to_delete,
                                     struct iser_ptl_task_t,
                                     task_list);

        iser_ptl_delete_task(ptl_task_p);
    }

    EXIT_LOG;
}

//---------------------------------------------------------------------------
/*!
  Function:  iser_ptl_delete_task

  Parameters: iscsi_task - delete this one task.

  Description:
    delete this task.
    (1) use the connection object to lock the task list
    (2) remove the task from connection's task list.
    (3) unlock task list
    (4) release all saved pdus.
    (5) reset all task list fields
    (6) free task memory

    The task list lock must be held when calling this function
*/
//---------------------------------------------------------------------------
STATIC void
iser_ptl_delete_task(struct iser_ptl_task_t *ptl_task_p)
{
    struct iser_ptl_conn_t* ptl_conn_p = ptl_task_p->conn_h;

    ENTER_LOG;

    //print_task_list(ptl_conn_p);

    list_del_init(&ptl_task_p->task_list);
    ptl_conn_p->task_list_size--;

    //print_task_list(ptl_conn_p);

    if (ptl_task_p->conn_h->conn_state != ISER_PTL_LOGGED_ON) {

        ITRACE(TRACE_ISER_PTL_TASK,
               "%s(): Task desc=0x%p, ITT:0x%X From Conn=0x%p state!=LOGGED_ON\n",
               __func__,
               ptl_task_p,
               ptl_task_p->itt,
               ptl_conn_p);

        release_iser_pdus_from_task(ptl_task_p, ptl_conn_p);
    }


    ITRACE(TRACE_ISER_PTL_TASK,
           "%s(): Removed Task(desc=0x%p, ITT:0x%X)\n",
           __func__,
           ptl_task_p,
           ptl_task_p->itt);

    // memset(ptl_task_p,0,sizeof(struct iser_ptl_task_t));

    kmem_cache_free(iser_ptl_global.task_slab, ptl_task_p);

    EXIT_LOG;
}

//---------------------------------------------------------------------------
/*!
  @description
  called from iser-ptl to release all the pdus previuosly received from iser.


  @returns
  on successes TRUE, otherwise FALSE.
*/
//---------------------------------------------------------------------------
STATIC int
release_iser_pdus_from_task(struct iser_ptl_task_t* ptl_task_p,
                            struct iser_ptl_conn_t* ptl_conn_p)
{
    struct list_head *entry;
    struct list_head *next;
    struct iser_recv_pdu_t *p_ctrl_pdu;
    iser_status_t iser_ret;

    if (ptl_task_p == NULL) {
        VD_LOG(VDLOG_ERROR,"%s() Task == NULL\n",__func__);
        return FALSE;
    }

    spin_lock(&ptl_task_p->task_lock);

    list_for_each_safe(entry,next,&ptl_task_p->release_list_head) {
        p_ctrl_pdu = list_entry(entry,struct iser_recv_pdu_t,pdu_list);
        list_del(&p_ctrl_pdu->pdu_list);

        // Notify ISER to release the pdu since its been already been copied.
        iser_ret = iser_ptl_global.iser_api.release_control(ptl_conn_p,
                                                            p_ctrl_pdu);
        if (iser_ret != ISER_SUCCESS) {
            list_add_tail(&p_ctrl_pdu->pdu_list,&ptl_task_p->release_list_head);
            spin_unlock(&ptl_task_p->task_lock);

            VD_LOG(VDLOG_ERROR,"%s: failed release_control task=0x%p pdu=0x%p\n",
                   __func__, ptl_task_p, p_ctrl_pdu);
            return FALSE;
        }
    }

    spin_unlock(&ptl_task_p->task_lock);
    return TRUE;
}

//---------------------------------------------------------------------------
/*!
  @description
  called by the user (via proc-fs) to actually start the PTL layer.
  after iTarget calls bIserInitPtlLayer() ,PTL does yet convey pdu's
  to iTarget. only after vIserStartPtlLayer() is called pdu's are actually
  disclosed to the iSCSI layer.
  a global ISER-PTL state is set and when a connection request is received
  it will trigger iTarget (i.e. call NewConnectionRequest() )

  The motivation to create such a procedure was a timing problem :
  the iSCSI and SCSI modules were initialized followed with a scsi disk scan
  whoes results were saved in both modules. the problem was that pdus
  were received before the disk scan was completed.
  so the starting process was divided into these 2 stages :
  at the 1st stage - iTarget module is initialized and so is the PTL
                     but pdu's are not yet serviced.
                     so a disk-scan for scsi can be performed without
                     worrying about not servicing pdus
  at the 2nd stage - the PTL is started and now can start servicing pdu's

  this whole process should be changed since this is not a PTL problem
  but an iSCSI one.the starting function should be part of iTarget and
  is not suppose to be registered with the iSER PTL or any for that matter.

  @returns
*/
//---------------------------------------------------------------------------
void
vISERStartPTLLayer(void)
{
    iser_status_t   iser_ret;

    ENTER_LOG;

    if (iser_ptl_global.iser_ptl_state != ISER_PTL_STARTED) {

        iser_ptl_global.listening_port = 3260;	//usGetListeningPort();
        ITRACE(TRACE_ISER_PTL_GEN,
               "%s() registering iSER to listen on port %d\n",
               __func__, iser_ptl_global.listening_port);

        // register with the iser module.
        iser_ret = iser_api_register(ISER_ENTITY_TARGET,
                                     "iTarget",
                                     &iser_ptl_global.iser_api, // OUT
                                     &iser_ptl_global.iser_cb, // IN
                                     &iser_ptl_global.iser_ext_api, // OUT
                                     &iser_ptl_global.iser_ext_cb, // IN
                                     iser_ptl_global.listening_port,
                                     &iser_ptl_global.api_h);

        if (iser_ret == ISER_SUCCESS) {
            ITRACE(TRACE_ISER_PTL_GEN,"%s() iser ptl state = ISER_PTL_STARTED\n",__func__);
            iser_ptl_global.iser_ptl_state = ISER_PTL_STARTED;
        }
    }

    EXIT_LOG;
} /* vISERStartPTLLayer */

//---------------------------------------------------------------------------
/*!
  @description
  vIserStopPtlLayer() is vIserStartPtlLayer() counterPart.
  all connections are disconnected and the ISER-PTL global state is reset
  afterwhich connection requests are no longer services.

  @returns
*/
//---------------------------------------------------------------------------
void
vISERStopPTLLayer(void)
{
    iser_status_t   iser_ret;

    ENTER_LOG;

    if (iser_ptl_global.iser_ptl_state != ISER_PTL_STOPPED) {

        iser_ptl_delete_connection_list(&iser_ptl_global.conn_list_head);

        iser_ret = iser_api_unregister(iser_ptl_global.api_h);
        if (iser_ret == ISER_SUCCESS) {
            ITRACE(TRACE_ISER_PTL_GEN,"%s() iser ptl state = ISER_PTL_STOPPED\n",__func__);
            iser_ptl_global.iser_ptl_state = ISER_PTL_STOPPED;
        }
        else {
            VD_LOG(VDLOG_ERROR,"%s() Failed iser_api_unregister()\n",__func__);
        }
    }

    EXIT_LOG;
} /* vISERStopPTLLayer */

//---------------------------------------------------------------------------
/*!
  @description
  called from iTarget to remove ISER PTL connection.

  @returns
  on success 0, otherwise -1.
*/
//---------------------------------------------------------------------------
int
iser_ptl_remove_conn(ptl_conn_handle_t conn_id,    //!< IN - the PTL connection id.
                       int close_type) //!< IN - type of close (GRACEFUL or ABORTIVE)
{
    struct iser_ptl_conn_t* ptl_conn_p = (struct iser_ptl_conn_t*)conn_id;
    iser_status_t iser_ret;

    ENTER_LOG;

    switch (ptl_conn_p->conn_state) {
    case ISER_PTL_NEW:
    case ISER_PTL_ESTABLISHED:
    case ISER_PTL_LOGGED_ON:

        ptl_conn_p->conn_state = ISER_PTL_DISCONNECT;
        spin_lock(&iser_ptl_global.conn_list_lock);
        iser_ptl_delete_connection(ptl_conn_p);
        spin_unlock(&iser_ptl_global.conn_list_lock);

        ITRACE(TRACE_ISER_PTL_GEN,
               "%s: call iser connection_terminate:0x%p\n",
               __func__, ptl_conn_p);
        /* connection descriptor freed but we pass it to iser only as a handle */
        iser_ret = iser_ptl_global.iser_api.connection_terminate(ptl_conn_p);
        if (iser_ret != ISER_SUCCESS) {
            VD_LOG(VDLOG_ERROR,
                   "%s: failed connection_terminate:0x%p (iser_ret=%u)\n",
                   __func__, ptl_conn_p, iser_ret);
            //BUG();
        }
        ITRACE(TRACE_ISER_PTL_GEN,
               "%s: Connection:0x%p terminated by iser\n",
               __func__, ptl_conn_p);

        break;

    case ISER_PTL_DISCONNECT:
    case ISER_PTL_FAILED:
        spin_lock(&iser_ptl_global.conn_list_lock);
        iser_ptl_delete_connection(ptl_conn_p);
        spin_unlock(&iser_ptl_global.conn_list_lock);
        break;

    default:
        VD_LOG(VDLOG_PANIC,"illegal iser_ptl conn:0x%p state:%d \n",
               ptl_conn_p,ptl_conn_p->conn_state);
        BUG();
        break;
    }

    EXIT_LOG;
    return 0;
} /* iser_ptl_remove_conn */

//---------------------------------------------------------------------------
/*!
  @description
  sends a login response PDU

  @returns
  on success 0, otherwise -1.
*/
//---------------------------------------------------------------------------
STATIC ptl_ret_t
iser_ptl_send_login_rsp(struct iser_ptl_conn_t *ptl_conn_p,
			 PDUInfo *iscsi_pdu)
{
	iser_status_t iser_ret = ISER_SUCCESS;
	ptl_ret_t ret_val = PTL_OK;
	LOGIN_RESPONSE *pResp;
	int bret,moc;
	char tmp[32];
	struct iser_send_pdu_t iser_pdu;
	struct iser_conn_resources_t *iser_res = &ptl_conn_p->iser_conn_resources;

	ENTER_LOG;

	pResp = (LOGIN_RESPONSE*)iscsi_pdu->BHS;
	if (IS_FINAL_LOGIN_RESP(pResp->flags,pResp->statusClass) &&
	    ptl_conn_p->conn_state == ISER_PTL_ESTABLISHED ) {

		/* This will determine the size of R2Ts and Data-INs - i.e. RDMA buffers */
		bSetNumericNegParamValue(ptl_conn_p->iscsi_conn_h,
					 N_MAX_BURST_SIZE,
					 512 * 1024);

		bret = bGetNumericNegParamValue(ptl_conn_p->iscsi_conn_h,
						N_IMMEDIATE_DATA,
						(int *)&ptl_conn_p->immediate_sz);
		if (!bret) {
			VD_LOG(VDLOG_ERROR,
			       "%s() Failed getting N_IMMEDIATE_DATA <key>\n",__func__);
			BUG();
		}
		sprintf(tmp,"%s",(ptl_conn_p->immediate_sz)?"Yes":"No");
		ITRACE(TRACE_ISER_PTL_GEN,
		       "%s(): Notice_key_value: ImmediateData=%s\n",
		       __func__,tmp);
		iser_ptl_global.iser_api.notice_key_values(ptl_conn_p,"ImmediateData",tmp );

		bret = bGetNumericNegParamValue(ptl_conn_p->iscsi_conn_h,
						N_FIRST_BURST_SIZE,
						(int *)&ptl_conn_p->unsolicited_sz);
		if (!bret) {
			VD_LOG(VDLOG_ERROR,
			       "%s() Failed getting N_FIRST_BURST_SIZE <key>\n",__func__);
			BUG();
		}
		sprintf(tmp,"%d",ptl_conn_p->unsolicited_sz);
		ITRACE(TRACE_ISER_PTL_GEN,
		       "%s(): Notice_key_value: FirstBurstLength=%s\n",
		       __func__,tmp);
		iser_ptl_global.iser_api.notice_key_values(ptl_conn_p,"FirstBurstLength",tmp);

		bret = bGetNumericNegParamValue(ptl_conn_p->iscsi_conn_h,
						MAX_RECV_PDU_LENGTH_THIS_SIDE, // DAN
						(int *)&ptl_conn_p->data_seg_sz);
		if (!bret) {
			VD_LOG(VDLOG_ERROR,
			       "%s() Failed getting MAX_RECV_PDU_LENGTH_THIS_SIDE <key>\n",__func__);
			BUG();
		}
		sprintf(tmp,"%d",ptl_conn_p->data_seg_sz);
		ITRACE(TRACE_ISER_PTL_GEN,
		       "%s(): Notice_key_value: TargetRecvDataSegmentLength=%s\n",
		       __func__,tmp);
		iser_ptl_global.iser_api.notice_key_values(ptl_conn_p,"TargetRecvDataSegmentLength",tmp);

		ITRACE(TRACE_ISER_PTL_GEN, "%s(): Allocating connection resources\n",__func__);
		iser_res->conn_type = ISER_TRANSPORT_CONN_IB;
		iser_res->api_h = iser_ptl_global.api_h;
		iser_res->max_recv_pdu_sz = ptl_conn_p->data_seg_sz;
		iser_res->max_recv_dsl = ptl_conn_p->data_seg_sz;
		iser_res->first_burst_length = ptl_conn_p->unsolicited_sz;

		iser_ret = iser_ptl_global.iser_api.allocate_connection_resources(ptl_conn_p,
										  iser_res,
										  &moc);
		if (iser_ret != ISER_SUCCESS) {
			VD_LOG(VDLOG_ERROR,
			       "%s() failed allocate_connection_resources rc=%u\n",
			       __func__,iser_ret);
			goto iser_ptl_send_login_rsp_exit;
		}
		session_set_moc(ptl_conn_p->iscsi_conn_h,moc);
		iscsi_to_iser_pdu(iscsi_pdu, &iser_pdu );

		ITRACE(TRACE_ISER_PTL_GEN, "%s: calling enable_datamover\n",__func__);
		iser_ret=iser_ptl_global.iser_api.enable_datamover(ptl_conn_p,
								   &ptl_conn_p->iser_tport_conn,
								   &iser_pdu);
		ITRACE(TRACE_ISER_PTL_GEN, "%s: enable_datamover returned\n",__func__);
		if (iser_ret != ISER_SUCCESS) {
			VD_LOG(VDLOG_ERROR,"%s: failed enable_datamover rc=%u\n",__func__,iser_ret);
			ptl_conn_p->conn_state = ISER_PTL_FAILED;

			goto iser_ptl_send_login_rsp_exit;
		}

		ITRACE(TRACE_ISER_PTL_GEN,
		       "%s(): conn_state=%d changed to LOGGED_ON\n",
		       __func__, ptl_conn_p->conn_state);

		ptl_conn_p->conn_state = ISER_PTL_LOGGED_ON;

		vSentPDUHandler(ptl_conn_p->iscsi_conn_h, iscsi_pdu);

        }
	else {
		iscsi_to_iser_pdu(iscsi_pdu, &iser_pdu );

		iser_ret = iser_ptl_global.iser_api.send_control(ptl_conn_p,
								 &iser_pdu);
		if (iser_ret != ISER_SUCCESS) {
			print_iscsi_pdu(iscsi_pdu,-1,"failed to send login rsp");
			ret_val = PTL_TRANSPORT_FAILED;
			goto iser_ptl_send_login_rsp_exit;
		}
		vSentPDUHandler(ptl_conn_p->iscsi_conn_h, iscsi_pdu);
	}

iser_ptl_send_login_rsp_exit:
	EXIT_LOG;
	return ret_val;
}

PDUInfo *create_fake_data_out(TaskInfo *pTask, int sn, int itt,
			      int data_len, int offset)
{
	PDUInfo *pdu;
	DataOutPduHdr *dout_hdr_p;
	ScsiCmdPduHdr *cmd_bhs;

        pdu = vPDUAllocHandler(pTask->pCmdPdu->pConn);
        if (pdu == NULL) {
            VD_LOG(VDLOG_ERROR,
                   "%s() Failed to allocate fake Data-OUT PDUInfo, p_conn=0x%p\n",
                   __func__,pTask->pCmdPdu->pConn);

            return NULL;
        }

        pdu->rdma_pdu = 1;

        dout_hdr_p = (DataOutPduHdr*)pdu->BHS;

        dout_hdr_p->byOpcode = PDU_OPCODE_DATA_OUT; // data-out opcode
        dout_hdr_p->byFlags = FINAL_BIT_FLAG;         // final bit only
        dout_hdr_p->usReserved1 = 0;
        dout_hdr_p->ulDataLength = htonl(data_len);

	cmd_bhs = (ScsiCmdPduHdr *)pTask->pCmdPdu->BHS;
	memcpy (dout_hdr_p->arrLUN, cmd_bhs->arrLogUnitNumber, 8);

        dout_hdr_p->itt = htonl(itt); // r2t_bhs_p->itt;
        dout_hdr_p->ttt = htonl(sn);  // r2t_bhs_p->ttt;
        dout_hdr_p->ulReserved2 = 0;
        dout_hdr_p->ulExpStatSN = 0; // ToDo: Verify that it's not used
        dout_hdr_p->ulReserved3 = 0;
        dout_hdr_p->ulDataSN = 0;  // always "first" in sequence
        dout_hdr_p->ulReserved4 = 0;
	dout_hdr_p->ulBuffOffset = htonl(offset);
	return pdu;
}

//---------------------------------------------------------------------------
/*!
  @description
  performs an RDMA read for an R2T PDU

  @returns
  on success 0, otherwise -1.
*/
//---------------------------------------------------------------------------
STATIC ptl_ret_t iser_ptl_handle_r2t(struct iser_ptl_conn_t *ptl_conn_p,
				     PDUInfo *iscsi_pdu,
				     int retry)
{
	DWORD itt;
	TaskInfo *pTask;
	struct iser_ptl_task_t* ptl_task_p;
    	DWORD unsol_burst;
	R2TPduHdr* r2t_header_p;
	DWORD rdma_transfer_len;
	DWORD buff_offset;
	int sn;
	iSCSI_Sequence *seq;
	PDUInfo *fake_dout;
	int err;
	SG_ListInfo *pDataOutSgList;
	struct iser_send_pdu_t iser_pdu;
	iser_status_t iser_ret = ISER_SUCCESS;
	ptl_ret_t ret_val = PTL_OK;

	ENTER_LOG;

	panic_on((void *)ptl_conn_p < (void *)4096);
	panic_on((void *)iscsi_pdu < (void *)4096);
	itt = iscsi_pdu->itt;

	pTask = iscsi_pdu->pTask;
	panic_on((void *)pTask < (void *)4096);

	ptl_task_p = pTask->ptl_task_h;
	panic_on((void *) ptl_task_p < (void *)4096);

	unsol_burst = pTask->Unsolicited.ulBurstSize;

	r2t_header_p = (R2TPduHdr*)iscsi_pdu->BHS;
	panic_on((void *) r2t_header_p < (void *)4096);

	rdma_transfer_len = ntohl(r2t_header_p->ulDesiredDataLen);
	buff_offset = ntohl(r2t_header_p->ulBuffOffset);

	sn = ntohl(r2t_header_p->ulR2TSN);
	seq = &pTask->SolicitedArr[sn];
	if ((void *)seq < (void *)4096){
		VD_LOG(VDLOG_PANIC,
		       "%s() sn=%d pTask->SolicitedArr=0x%p &pTask->SolicitedArr[sn]=0x%p\n",
		       __func__,sn,
		       pTask->SolicitedArr,
		       &pTask->SolicitedArr[sn]);
		BUG();
	}
	if (sn != seq->ulR2TSN) {
		VD_LOG(VDLOG_PANIC,"%s(): sequence != sn\n",__func__);
		BUG();
	}
	if (!retry) {
		fake_dout = create_fake_data_out(pTask, sn, itt,
						 rdma_transfer_len,
						 buff_offset);
		if (fake_dout == NULL){
			ret_val = PTL_TARGET_FAILED;
			goto iser_ptl_handle_r2t_exit;
		}
		seq->pdu = fake_dout;

		// Notify iTarget of a received Data-Out pdu header
		vDataOutPduHeaderReceivedHandler(ptl_conn_p->iscsi_conn_h,
						 pTask,
						 fake_dout,
						 SG_SCATTER_ALLOC, /* using alloc_sg_list_mem() */
						 &err);
		if (err != 0) {
		    VD_LOG(VDLOG_ERROR,
			   "%s() Failed vISER_PDUHeaderReceivedHandler() "
			   "for pdu=0x%p, p_conn=0x%p\n",
			   __func__,
			   fake_dout,
			   ptl_conn_p->iscsi_conn_h);

		    vFreePDUResources(fake_dout);
		    seq->pdu = NULL;

		    ret_val = PTL_TARGET_FAILED;
		    goto iser_ptl_handle_r2t_exit;
		}
	}
	else {
		fake_dout = seq->pdu;
		panic_on((void *)fake_dout < (void *)4096);
	}

	pDataOutSgList = fake_dout->pDataPtr;
	panic_on((void *) pDataOutSgList < (void *)4096);

	err = alloc_sg_list_mem(pDataOutSgList, rdma_transfer_len, retry);
	if (err == 0) {
		ITRACE(TRACE_ISER_PTL_TX_PRINT,
		       "%s() allocated RDMA-READ buff.sz:%u on task itt:0x%X\n",
		       __func__, rdma_transfer_len, itt);
	}
	else {
		ITRACE(TRACE_ISER_PTL_TX_PRINT,
		       "%s() failed to allocate RDMA-READ buffer sz:%d for task itt:0x%X\n",
		       __func__, rdma_transfer_len, itt);

		ret_val = PTL_NO_MEMORY;
		goto iser_ptl_handle_r2t_exit;
	}

	ITRACE(TRACE_ISER_PTL_TASK,
	       "%s() PTLTask:0x%p iSCSI Task:0x%p(ITT:0x%X) R2TPDU:0x%p(ITT:0x%X) offset:0x%X FirstBurst:0x%X\n",
              __func__,
              ptl_task_p, pTask,
              (pTask == NULL ? 0xFFFFFFFF : pTask->itt),
              iscsi_pdu, iscsi_pdu->itt,
              buff_offset, unsol_burst);
	if (buff_offset < unsol_burst) {
		VD_LOG(VDLOG_ERROR,"%s() ITT:0x%X, buff_offset:%d < unsol_burst:%d\n",
		       __func__, itt, buff_offset, unsol_burst);
		ret_val = PTL_TARGET_FAILED;
		goto iser_ptl_handle_r2t_exit;
	}
	/* it's important to change R2T PDU contents only after memory alloc succeeds
	because in case of failure the function may be entered again with the same PDU */
	r2t_header_p->ulBuffOffset = htonl(buff_offset - unsol_burst);

	iser_pdu.p_bhs = (union iser_pdu_bhs_t*) r2t_header_p;

	seq->scatterlist = kmalloc(pDataOutSgList->SG_EntriesNum * sizeof(struct scatterlist),GFP_KERNEL);
	panic_on(seq->scatterlist == NULL);
	build_st(seq->scatterlist,pDataOutSgList);

	iser_pdu.data.r2t.dst_buf.p_buf = seq->scatterlist;
	iser_pdu.data.r2t.dst_buf.size = pDataOutSgList->SG_EntriesNum;
	iser_pdu.data.r2t.dst_buf.type = ISER_BUF_TYPE_SCATTERLIST;

	iser_ret = iser_ptl_global.iser_api.get_data(ptl_task_p->iser_task_h,
						     &iser_pdu,1);

	/* restore the original buffer offset */
	r2t_header_p->ulBuffOffset = htonl(buff_offset);

	if (iser_ret != ISER_SUCCESS) {
		ret_val = (iser_ret == ISER_FAILURE ?
			   PTL_TRANSPORT_FAILED : PTL_TARGET_FAILED);
		print_iscsi_pdu(iscsi_pdu,-1,"failed to get_data for r2t pdu");

		VD_LOG(VDLOG_ERROR,"%s() get_data() failed, ret_val:%d !!\n",
		       __func__,iser_ret);
		goto iser_ptl_handle_r2t_exit;
	}

	vSentPDUHandler(ptl_conn_p->iscsi_conn_h, iscsi_pdu);

iser_ptl_handle_r2t_exit:
	EXIT_LOG;
	return ret_val;
}

//---------------------------------------------------------------------------
/*!
  @description
  performs RDMA write for a data-in PDU

  @returns
  on success 0, otherwise -1.
*/
//---------------------------------------------------------------------------
STATIC ptl_ret_t
iser_ptl_handle_data_in(struct iser_ptl_conn_t *ptl_conn_p,
			PDUInfo *iscsi_pdu)
{
	TaskInfo *pTask;
	struct iser_ptl_task_t *ptl_task_p;
	struct iser_send_pdu_t iser_pdu;
	iser_status_t iser_ret = ISER_SUCCESS;
	ptl_ret_t ret_val = PTL_OK;
	DataInPduHdr* data_in_hdr_p;

	ENTER_LOG;

	pTask = iscsi_pdu->pTask;
	panic_on((void *) pTask < (void *)4096);

	ptl_task_p = pTask->ptl_task_h;
	panic_on((void *) ptl_task_p < (void *)4096);

	data_in_hdr_p = (DataInPduHdr*)iscsi_pdu->BHS;
	//===============================================
	// convert the read response (Data-In PDU) to
	// an iser pdu and  call put_data().
	//
	// the memory for the read command data buffer
	// that was allocated by iTarget by calling
	// iser-ptl's memory allocation call-back method
	// is freed when data_completion_notify() is triggered
	// for a successfull put_data() pertaing this task.
	//===============================================
	iscsi_to_iser_pdu(iscsi_pdu, &iser_pdu);
	ptl_task_p->data_in_pdu = iscsi_pdu;
	iser_ret = iser_ptl_global.iser_api.put_data(ptl_task_p->iser_task_h,
						     &iser_pdu,1);

	if (iser_ret != ISER_SUCCESS) {
		ret_val = (iser_ret == ISER_FAILURE ?
			   PTL_TRANSPORT_FAILED : PTL_TARGET_FAILED);
		print_iscsi_pdu(iscsi_pdu,-1,"failed to put_data for data-in pdu");
		VD_LOG(VDLOG_ERROR,"%s() failed put_data (%u)\n",__func__, iser_ret);
		ptl_task_p->data_in_pdu = NULL;
		goto iser_ptl_handle_data_in_exit;
	}

	ITRACE(TRACE_ISER_PTL_TASK,
               	"%s() Saved DataInPDU=0x%p on task=0x%p\n",
               	__func__,iscsi_pdu, ptl_task_p);

iser_ptl_handle_data_in_exit:
	EXIT_LOG;
	return ret_val;
}

//---------------------------------------------------------------------------
/*!
  @description
  sends a response for a SCSI cmd

  @returns
  on success 0, otherwise -1.
*/
//---------------------------------------------------------------------------
STATIC ptl_ret_t
iser_ptl_send_rsp(struct iser_ptl_conn_t *ptl_conn_p,
		  PDUInfo *iscsi_pdu)
{
	iser_status_t iser_ret = ISER_SUCCESS;
	ptl_ret_t ret_val = PTL_OK;
	ScsiResPduHdr* resp_hdr_p;
	DWORD itt;
	TaskInfo *pTask;
	struct iser_ptl_task_t *ptl_task_p;
	struct iser_send_pdu_t iser_pdu;
	int data_in_done;

	ENTER_LOG;

	pTask = iscsi_pdu->pTask;
	panic_on((void *) pTask < (void *)4096);

	ptl_task_p = pTask->ptl_task_h;
	panic_on((void *) ptl_task_p < (void *)4096);


	resp_hdr_p = (ScsiResPduHdr*)iscsi_pdu->BHS;
	itt = iscsi_pdu->itt;

	iscsi_to_iser_pdu(iscsi_pdu, &iser_pdu);

	if (ptl_task_p->cmd_dir == ISER_DIR_OUT) {
		release_iser_pdus_from_task(ptl_task_p, ptl_conn_p);
		iser_ret = iser_ptl_global.iser_api.send_control(ptl_conn_p,&iser_pdu);
		spin_lock(&ptl_conn_p->task_list_lock);
		iser_ptl_delete_task(ptl_task_p);
		spin_unlock(&ptl_conn_p->task_list_lock);
		vSentPDUHandler(ptl_conn_p->iscsi_conn_h, iscsi_pdu);
	}
	else if (ptl_task_p->cmd_dir == ISER_DIR_IN) {
		iser_ret = iser_ptl_global.iser_api.send_control(ptl_conn_p,&iser_pdu);

		spin_lock(&ptl_task_p->task_lock);
		ITRACE(TRACE_ISER_PTL_TASK, "%s() rsp_rel_state = %d for ITT 0x%x (DriverStatus = 0x%x)\n",
		       __func__,
		       ptl_task_p->rsp_rel_state,
		       itt,
		       ptl_task_p->pTask->enDriverStatus);
		switch (ptl_task_p->rsp_rel_state)
		{
		case RSP_REL_INIT: // The response wasn't sent yet. Wait for it
			ptl_task_p->rsp_rel_state = RSP_REL_WAIT_DATA_CMPL;
			ptl_task_p->resp_pdu = iscsi_pdu;
			ITRACE(TRACE_ISER_PTL_TASK,"%s() saved RespPDU=0x%p on Task=0x%p\n",
			       __func__,iscsi_pdu, ptl_task_p);
			break;

		case RSP_REL_WAIT_RSP: // data_cmpl_notify was already called. Release the response PDU.
			break;

		default: // Unexpected
			VD_LOG(VDLOG_ERROR, "%s() unexpected rsp_rel_state (%d), ITT = 0x%x\n",
			       __func__, ptl_task_p->rsp_rel_state, itt);
			goto iser_ptl_send_rsp_exit;
		}

		if (ptl_task_p->pTask->enDriverStatus ||
		    ptl_task_p->pTask->enSCSIStatus ||
		    ptl_task_p->rsp_rel_state == RSP_REL_WAIT_RSP) {
			data_in_done = 1;
		} else {
			data_in_done = 0;
		}

		spin_unlock(&ptl_task_p->task_lock);

		// The task and rsp PDU should be released here (don't wait for data_cmpl_notify)
		if (data_in_done) {
			spin_lock(&ptl_conn_p->task_list_lock);
			iser_ptl_delete_task(ptl_task_p);
			spin_unlock(&ptl_conn_p->task_list_lock);

			if (!iscsi_pdu) {
				VD_LOG(VDLOG_PANIC, "iscsi_pdu is NULL\n");
				BUG();
			}
			vSentPDUHandler(ptl_conn_p->iscsi_conn_h, iscsi_pdu);
		}
	}
	else if (ptl_task_p->cmd_dir == ISER_DIR_NONE) {
		iser_ret = iser_ptl_global.iser_api.send_control(ptl_conn_p,&iser_pdu);
		spin_lock(&ptl_conn_p->task_list_lock);
		iser_ptl_delete_task(ptl_task_p);
		spin_unlock(&ptl_conn_p->task_list_lock);
		vSentPDUHandler(ptl_conn_p->iscsi_conn_h, iscsi_pdu);
	}
	else {
		VD_LOG(VDLOG_ERROR,"%s() illegal cmd dir in RespPDU=0x%p on Task=0x%p, itt:0x%x\n",
		       __func__,iscsi_pdu, ptl_task_p, itt);
		BUG();
	}

	if (iser_ret != ISER_SUCCESS) {
		ret_val = (iser_ret == ISER_FAILURE ?
			   PTL_TRANSPORT_FAILED : PTL_TARGET_FAILED);
		print_iscsi_pdu(iscsi_pdu,-1,"failed send scsi rsp");
		goto iser_ptl_send_rsp_exit;
	}

iser_ptl_send_rsp_exit:
	EXIT_LOG;
	return ret_val;

}

//---------------------------------------------------------------------------
/*!
  @description
  called from iTarget to send a pdu.

  @returns
  on success 0, otherwise -1.
*/
//---------------------------------------------------------------------------
ptl_ret_t iser_ptl_send_pdu(ptl_conn_handle_t   conn_id,
			    PDUInfo             *iscsi_pdu,
			    int retry)
{
	struct iser_ptl_conn_t *ptl_conn_p = (struct iser_ptl_conn_t *) conn_id;
	struct iser_send_pdu_t iser_pdu;
	iser_status_t iser_ret = ISER_SUCCESS;
	ptl_ret_t ret_val = PTL_OK;
	BYTE *byOpcode;

	ENTER_LOG;

	if (!iscsi_pdu) {
		VD_LOG(VDLOG_PANIC, "iscsi_pdu is NULL\n");
		BUG();
	}

	if (!ptl_conn_p) {
		VD_LOG(VDLOG_PANIC, "ptl_conn_p is NULL\n");
		BUG();
	}

	if ((ptl_conn_p->conn_state == ISER_PTL_DISCONNECT) ||
	    (ptl_conn_p->conn_state == ISER_PTL_FAILED)) {
		VD_LOG(VDLOG_ERROR,
		       "%s() PTL conn is not up, state:%d, Can't send PDU:0x%p\n",
		       __func__, ptl_conn_p->conn_state, iscsi_pdu);
		ret_val = PTL_TRANSPORT_FAILED;
		goto exit_iser_ptl_send_pdu;
	}

	byOpcode = iscsi_pdu->BHS;
	switch (*byOpcode) {
	case PDU_OPCODE_LOGIN_RESP:
		vPDUiSCSICountersSet(iscsi_pdu);
		ret_val = iser_ptl_send_login_rsp(ptl_conn_p, iscsi_pdu);
		if (ret_val != PTL_OK) {
			ITRACE(TRACE_ISER_PTL_GEN,
			       "iser_ptl_send_login_rsp failed (%d)\n",
			       ret_val);
			goto exit_iser_ptl_send_pdu;
		}
		break;

	case PDU_OPCODE_R2T:
		ret_val = iser_ptl_handle_r2t(ptl_conn_p, iscsi_pdu, retry);
		if (ret_val != PTL_OK) {
			ITRACE(TRACE_ISER_PTL_GEN, "iser_ptl_handle_r2t failed (%d)\n",
			       ret_val);
			goto exit_iser_ptl_send_pdu;
		}
		break;

	case PDU_OPCODE_DATA_IN:
		ret_val = iser_ptl_handle_data_in(ptl_conn_p, iscsi_pdu);
		if (ret_val != PTL_OK) {
			ITRACE(TRACE_ISER_PTL_GEN,
			       "iser_ptl_handle_data_in failed (%d)\n",
			       ret_val);
			goto exit_iser_ptl_send_pdu;
		}
		break;

	case PDU_OPCODE_SCSI_RESPONSE:
		vPDUiSCSICountersSet(iscsi_pdu);
		ret_val = iser_ptl_send_rsp(ptl_conn_p, iscsi_pdu);
		if (ret_val != PTL_OK) {
			ITRACE(TRACE_ISER_PTL_GEN, "iser_ptl_send_rsp failed (%d)\n",
			       ret_val);
			goto exit_iser_ptl_send_pdu;
		}
		break;

	case PDU_OPCODE_NOP_IN:
	case PDU_OPCODE_TASK_MNG_RESP:
	case PDU_OPCODE_TEXT_RESP:
	case PDU_OPCODE_LOGOUT_RESP:
	case PDU_OPCODE_ASYNC_MSG:
	case PDU_OPCODE_REJECT:

		vPDUiSCSICountersSet(iscsi_pdu);
		iscsi_to_iser_pdu(iscsi_pdu, &iser_pdu);
		iser_ret = iser_ptl_global.iser_api.send_control(ptl_conn_p,
								 &iser_pdu);
		if (iser_ret != ISER_SUCCESS) {
			ret_val = (iser_ret == ISER_FAILURE ?
				   PTL_TRANSPORT_FAILED : PTL_TARGET_FAILED);
			print_iscsi_pdu(iscsi_pdu,-1,"failed send ctrl rsp");
			goto exit_iser_ptl_send_pdu;
		}
		vSentPDUHandler(ptl_conn_p->iscsi_conn_h, iscsi_pdu);

		break;

	default:
		VD_LOG(VDLOG_ERROR,"%s() Recieved illegal iscsi command (opcode=0x%x)\n",
		       __func__, *byOpcode);
	}

 exit_iser_ptl_send_pdu:
    	EXIT_LOG;
    	return ret_val;
} /* iser_ptl_send_pdu */

//---------------------------------------------------------------------------
/*!
  @description
  called from iTarget to set iSCSI header digest for a connection.

  @returns
*/
//---------------------------------------------------------------------------
void
iser_ptl_set_header_digest(ptl_conn_handle_t conn_id) //!< IN - the PTL connectino id.
{
    ENTER_LOG;

    EXIT_LOG;

    //exit_iser_ptl_set_header_digest:
}

//---------------------------------------------------------------------------
/*!
  @description
  called from iTarget to set iSCSI data digest for a connection.

  @returns
*/
//---------------------------------------------------------------------------
void
iser_ptl_set_data_digest(ptl_conn_handle_t conn_id) //!< IN - the PTL connectino id.
{
    ENTER_LOG;

    EXIT_LOG;

    // exit_iser_ptl_set_data_digest:

}

/* ---------------------------------------------------------------------------
  called from iTarget to allocate an SG_ListInfo container for DATA-IN buffers.
  --------------------------------------------------------------------------- */
STATIC ptl_ret_t iser_ptl_get_data_in_buffer(UINT ulReqDataSize, //!< IN - the total amount of memeory required.
					     UINT ulMaxBuffLen,  //!< IN - the max memeory allowed for one SG_ListInfo
					     SG_ListInfo **pSgListHead,
					     SG_ListInfo **pSgListTail,
					     int retry)
{
    SG_ListInfo* pSG_ListInfo = NULL;
    ptl_ret_t ret_val = PTL_OK;

    ENTER_LOG;

    if (pSgListHead == NULL || pSgListTail == NULL) {
        VD_LOG(VDLOG_PANIC,"%s: NULL SgList head or tail\n",__func__);
        BUG();
    }
    *pSgListHead = *pSgListTail = NULL;
    ITRACE(TRACE_ISCSI_DATA,"%s: requested size=%d max buf len=%d\n",__func__,ulReqDataSize,ulMaxBuffLen);

    pSG_ListInfo = pAllocateSGListInfo(SG_SCATTER_ALLOC);
    if (alloc_sg_list_mem(pSG_ListInfo,ulReqDataSize,retry) != 0) {
        ITRACE(TRACE_ISCSI_DATA,"%s: failed alloc sg list %u bytes\n",__func__, ulReqDataSize);
        vRetMem(pSG_ListInfo);
        ret_val = PTL_NO_MEMORY;
        goto GetDataInBufferExit;
    }
    *pSgListHead = *pSgListTail = pSG_ListInfo;

GetDataInBufferExit:
    EXIT_LOG;
    return ret_val;
} /* iser_ptl_get_data_in_buffer */

//---------------------------------------------------------------------------
/*!
  @description
  called from ISER to notify about an incoming connection request
  The iSER layer provides its own connection handle, to be used in the
  subsequent calls to ISER ( e.g. connection_accept() )
  iser_ptl_connection_request_notify() creates a connection object and
  invokes iTarget's bAcceptNewConnection() with a connection handle as parameter.
  then calls iSER's accept()

  @returns ISER_SUCCESS, ISER_FAILURE
*/
//---------------------------------------------------------------------------
STATIC iser_status_t
iser_ptl_connection_request_notify(iser_conn_request_t conn_req_h,  //!< IN - connection request handle
                                   struct sockaddr_in  *dst_addr,   //!< IN - Target's IP address.
                                   struct sockaddr_in  *src_addr)   //!< IN - Initiator's IP address.
{

	struct iser_ptl_conn_t   *ptl_conn_p;
	iser_status_t            iser_ret = ISER_SUCCESS;

	ENTER_LOG;

	if (iser_ptl_global.iser_ptl_state == ISER_PTL_STOPPED ||
	    enable_conn_req == DISABLED) {

		VD_LOG(VDLOG_ERROR,"%s() Rejecting connection request\n",__func__);
		// ToDo : verify that reject may be done from the same ctxt ?
		// reject the connection and bail out.
		iser_ret = iser_ptl_global.iser_ext_api.connection_accept(conn_req_h, NULL, 0);
		if (iser_ret != ISER_SUCCESS)
			VD_LOG(VDLOG_ERROR,"%s() Failed connection reject %u \n",__func__, iser_ret);
		goto exit_iser_ptl_connection_request_notify;
	}

	//================================================
	// create iser-ptl conncetion object and add it
	// to the global iser ptl connection list.
	//================================================
	ptl_conn_p = kmem_cache_alloc(iser_ptl_global.conn_slab,GFP_KERNEL);

	if (!ptl_conn_p) {
		iser_ret = ISER_FAILURE;
		VD_LOG(VDLOG_ERROR,"%s() Failed kmalloc(iscsi_conn)\n",__func__);
		goto exit_iser_ptl_connection_request_notify;
	}
	memset(ptl_conn_p,0,sizeof(struct iser_ptl_conn_t));

	//================================================
	// create connection object and link it to
	// iser-ptl-global connection list.
	//================================================
	if (dst_addr != NULL) {
		memcpy((void*)&(ptl_conn_p->iser_conn_resources.src_addr),
		       (void*)dst_addr, sizeof(struct sockaddr_in));
	}
	if (src_addr != NULL) {
		memcpy((void*)&(ptl_conn_p->iser_conn_resources.dst_addr),
		       (void*)src_addr, sizeof(struct sockaddr_in));
	}

	ptl_conn_p->iser_conn_req_h = conn_req_h;

	// save iSER's connection handle.
	ptl_conn_p->conn_state = ISER_PTL_NEW;

	// init connection's task list.
	INIT_LIST_HEAD(&(ptl_conn_p->task_list_head));
	ptl_conn_p->task_list_size =0;
	spin_lock_init(&ptl_conn_p->task_list_lock);

    spin_lock(&iser_ptl_global.conn_list_lock);
	// add the connection to the global connection list.
	list_add_tail(&ptl_conn_p->conn_list,
		      &iser_ptl_global.conn_list_head);
	iser_ptl_global.conn_list_size ++;
    ITRACE(TRACE_ISER_PTL_GEN,
           "%s: Allocated conn:0x%p, remains %u connections\n",
           __func__, ptl_conn_p, iser_ptl_global.conn_list_size);
    spin_unlock(&iser_ptl_global.conn_list_lock);

	if (bAcceptNewConnection((ptl_conn_handle_t) ptl_conn_p,      //IN
				 &ptl_conn_p->iscsi_conn_h, //OUT
				 ISER_CONN,
				 &iser_ptl_global.iscsi_cb) == FALSE) {
		VD_LOG(VDLOG_ERROR, "%s() iSCSI target rejected the new connection\n",__func__);
		ptl_conn_p->conn_state = ISER_PTL_FAILED;
		iser_ret = ISER_FAILURE;
		goto exit_iser_ptl_connection_request_notify;
	}

	// accept the connection. iser_ptl_connection_establish_notify() is due
	iser_ret = iser_ptl_global.iser_ext_api.connection_accept(ptl_conn_p->iser_conn_req_h,
								  ptl_conn_p, 1);
	if (iser_ret != ISER_SUCCESS)
		VD_LOG(VDLOG_ERROR,"%s() Failed connection_accept() %u\n",__func__, iser_ret);

	ITRACE(TRACE_ISER_PTL_GEN,
	       "%s: Accepted iser_conn:0x%p iscsi_conn:0x%p\n",
	       __func__, ptl_conn_p, ptl_conn_p->iscsi_conn_h);

 exit_iser_ptl_connection_request_notify:
	EXIT_LOG;
	return iser_ret;
}

int iser_ptl_notify_condition(struct iser_ptl_conn_t *ptl_conn_p,
			      struct iser_recv_pdu_t *p_ctrl_pdu)
{
	iser_status_t iser_ret=ISER_SUCCESS;
	int ret = 0;

	if (ptl_conn_p->conn_state == ISER_PTL_DISCONNECT ||
	    ptl_conn_p->conn_state == ISER_PTL_FAILED) {
		// the connection is closing or failed -> release pdu and exit
		VD_LOG(VDLOG_WARNING,
		       "%s() Received pdu=0x%p on a closing conn=0x%p\n",
		       __func__, p_ctrl_pdu, ptl_conn_p);

		iser_ret = iser_ptl_global.iser_api.release_control(ptl_conn_p,
								    p_ctrl_pdu);
		if (iser_ret != ISER_SUCCESS) {
			VD_LOG(VDLOG_ERROR,
			       "%s() Failed release_control for iser_pdu=0x%p (%u)\n",
			       __func__, p_ctrl_pdu, iser_ret);
		}
		ret = -1;
	}
	else if (ptl_conn_p->conn_state == ISER_PTL_NEW) {
		ptl_conn_p->delayed_pdu = (void *)p_ctrl_pdu;
		VD_LOG(VDLOG_WARNING,
		       "%s: Received pdu:0x%p before conn:0x%p was established\n",
		       __func__, p_ctrl_pdu, ptl_conn_p);
		ret = -1;
	}
	return ret;
}

void check_pdu_sanity(struct iser_recv_pdu_t  *p_ctrl_pdu,
		      DWORD *received_data_size,
		      DWORD *itt,
		      BYTE  *flags)

{
	ScsiCmdPduHdr *iscsi_bhs_p = (ScsiCmdPduHdr *)p_ctrl_pdu->p_bhs;

	*received_data_size = ntohl(iscsi_bhs_p->ulDataLength);
	*itt = ntohl(iscsi_bhs_p->itt);
	*flags = iscsi_bhs_p->byFlags;

	if (*received_data_size > 0 &&
	    (p_ctrl_pdu->rx_data.p_buf == NULL ||
	     p_ctrl_pdu->rx_data.size == 0)) {
		// ToDo: expand print-outs
		VD_LOG(VDLOG_ERROR,
		       "%s() Empty data buffer while non-empty DSL ITT:0x%X\n",
		       __func__, *itt);
		BUG();
	}
}

STATIC void iser_ptl_cmd_notify(iser_conn_handle_t            conn_h,
				struct iser_recv_pdu_t        *p_ctrl_pdu,
				void  *iser_task_h,       /* in */
				void **iscsi_task_h)      /* out */
{
	struct iser_ptl_conn_t  *ptl_conn_p = (struct iser_ptl_conn_t*)conn_h;
	struct iser_ptl_task_t  *ptl_task_p = NULL;
	DWORD                   received_data_size;
	DWORD                   itt;
	PDUInfo                 *iscsi_pdu;
	SG_Entry                *pSG_Entry;
	iser_status_t           iser_ret;
	int                     err;
	BYTE flags;

	if (iser_ptl_notify_condition(ptl_conn_p,p_ctrl_pdu) != 0) {
		goto exit_no_release;
	}
	// create iscsi pdu
	if (!iser_to_iscsi_pdu(p_ctrl_pdu,ptl_conn_p,&iscsi_pdu)) {
		goto exit_with_release;
	}
	check_pdu_sanity(p_ctrl_pdu, &received_data_size, &itt, &flags);
        ptl_task_p = kmem_cache_alloc(iser_ptl_global.task_slab,GFP_KERNEL);
        if (ptl_task_p == NULL) {
		VD_LOG(VDLOG_ERROR,"%s() Failed to allocate task memory\n",__func__);
		goto exit_with_release;
        }
	ptl_task_p->iser_task_h = iser_task_h;
        //itarget_stats_simple_event(p_kstamp_group, STAT_DEBUG5_EVT);
        //memset(ptl_task_p,0,sizeof(struct iser_ptl_task_t));
        ptl_task_p->itt = itt;
        spin_lock_init(&ptl_task_p->task_lock);
        ptl_task_p->conn_h = ptl_conn_p;
        ptl_task_p->rsp_rel_state = RSP_REL_INIT;

        if (flags & READ_BIT_FLAG) {
		ITRACE(TRACE_ISER_PTL_RX_PRINT, "%s() Got READ command, ITT:0x%X\n",__func__,itt);
		ptl_task_p->cmd_dir = ISER_DIR_IN;
		// ToDo : what about bi-directional commands ?
		if (flags & WRITE_BIT_FLAG) {
			VD_LOG(VDLOG_PANIC, "%s() Got BIDIR command, ITT:0x%X\n",__func__,itt);
			ptl_task_p->cmd_dir = ISER_DIR_BIDIR;
			BUG();
		}
        }
        else if (flags & WRITE_BIT_FLAG) {
		ITRACE(TRACE_ISER_PTL_RX_PRINT, "%s() Got WRITE command, ITT:0x%X\n",__func__,itt);
		ptl_task_p->cmd_dir = ISER_DIR_OUT;
        }
        else {
		ITRACE(TRACE_ISER_PTL_RX_PRINT, "%s() Got NO-DIR command, ITT:0x%X\n",__func__,itt);
		ptl_task_p->cmd_dir = ISER_DIR_NONE;
        }
        ptl_task_p->data_in_pdu = NULL;
        ptl_task_p->resp_pdu = NULL;
        INIT_LIST_HEAD(&ptl_task_p->release_list_head);

        // add the task to connection's task list.
        spin_lock(&ptl_conn_p->task_list_lock);
        list_add_tail(&ptl_task_p->task_list,
                      &ptl_conn_p->task_list_head);
        ptl_conn_p->task_list_size ++;
        spin_unlock(&ptl_conn_p->task_list_lock);

        // itarget_stats_simple_event(p_kstamp_group, STAT_DEBUG6_EVT);

        ITRACE(TRACE_ISER_PTL_TASK,
               "%s() Added Task ITT:0x%X desc=0x%p To Conn=0x%p\n",
               __func__, itt, ptl_task_p, ptl_conn_p);

        ptl_task_p->pTask = pCommandPduHeaderReceivedHandler(
					ptl_conn_p->iscsi_conn_h,
					iscsi_pdu, SG_ONLY_ALLOC,
					ptl_task_p, &err);
        if (err) {
		VD_LOG(VDLOG_ERROR,
		       "%s() Failed vISER_PDUHeaderReceivedHandler() ITT:0x%X pdu=0x%p \n",
		       __func__, itt, iscsi_pdu);
		goto exit_with_release;
        }

        if (received_data_size == 0 ) {
		ITRACE(TRACE_ISER_PTL_RX_PRINT,
		       "%s() Received PDU has NO immidiate data\n",__func__);
		// Notify ISER to release the pdu since its been already been copied.
		iser_ret = iser_ptl_global.iser_api.release_control(ptl_conn_p,
								    p_ctrl_pdu);
		if (iser_ret != ISER_SUCCESS) {
			VD_LOG(VDLOG_ERROR,
			       "%s() Failed release_control for iser_pdu=0x%p (%u)\n",
			       __func__, p_ctrl_pdu, iser_ret);
		}
        }
        else { // received immediate data
		if (p_ctrl_pdu->rx_data.p_buf == NULL || p_ctrl_pdu->rx_data.size == 0 ) {
			VD_LOG(VDLOG_ERROR,
			       "%s() received PDU with dsl=%u but p_buf:0x%p or sz:0x%u\n",
			       __func__,
			       received_data_size,
			       p_ctrl_pdu->rx_data.p_buf,
			       p_ctrl_pdu->rx_data.size);
			BUG();
		}

		// save iser pdu on pertaining task.
		if (!save_iser_pdu_to_task(ptl_task_p, p_ctrl_pdu) ) {
			goto exit_with_release;
		}

		pSG_Entry = pAllocateSGListEntry();
		bAddEntryToSGList(iscsi_pdu->pDataPtr, pSG_Entry,
				  p_ctrl_pdu->rx_data.p_buf,
				  p_ctrl_pdu->rx_data.size);
        }
	err = vPDUReceivedHandler(ptl_conn_p->iscsi_conn_h, iscsi_pdu);
	if (err != 0) {
		ITRACE(TRACE_ISCSI_TASK_FREE, "%s(): Releasing task (ITT = 0x%x) "
		       "which could not be received\n",
		       __func__, ptl_task_p->pTask->itt);
		vFree_iSCSITask(ptl_task_p->pTask);
		goto exit_with_release;
	}

	*iscsi_task_h = ptl_task_p;
	EXIT_LOG;
	return;

 exit_with_release:
	iser_ret = iser_ptl_global.iser_api.release_control(ptl_conn_p,
							    p_ctrl_pdu);
 exit_no_release:
	if (ptl_task_p != NULL)
		kmem_cache_free(iser_ptl_global.task_slab,ptl_task_p);

	EXIT_LOG;
}

STATIC void iser_ptl_dout_notify(void                   *iscsi_task_h, /* in */
				 struct iser_recv_pdu_t *p_ctrl_pdu)
{
	struct iser_ptl_task_t  *ptl_task_p = iscsi_task_h;
	struct iser_ptl_conn_t  *ptl_conn_p = ptl_task_p->conn_h;
	DWORD                   received_data_size;
	DWORD                   itt;
	BYTE                    flags;
	PDUInfo                 *iscsi_pdu;
	SG_Entry                *pSG_Entry;
	iser_status_t           iser_ret;
	int                     err;

	if (iser_ptl_notify_condition(ptl_conn_p,p_ctrl_pdu) != 0) {
		goto exit_no_release;
	}
	// create iscsi pdu
	if (!iser_to_iscsi_pdu(p_ctrl_pdu,ptl_conn_p,&iscsi_pdu)) {
		goto exit_with_release;
	}
	check_pdu_sanity(p_ctrl_pdu, &received_data_size, &itt, &flags);

	// VD_LOG(VDLOG_INFO,"%s() data out itt=0x%X\n", __func__,itt);
        vDataOutPduHeaderReceivedHandler(ptl_conn_p->iscsi_conn_h,
                                         ptl_task_p->pTask,
                                         iscsi_pdu,
                                         SG_ONLY_ALLOC,
                                         &err);
        if (err) {
		VD_LOG(VDLOG_ERROR,
		       "%s() Failed notifing Data-OUT header, ITT:0x%X, iscsi_pdu=0x%p)\n",
		       __func__, itt, iscsi_pdu);
		goto exit_with_release;
        }

        // Store the PDU in task descriptor
        if (!save_iser_pdu_to_task(ptl_task_p,p_ctrl_pdu)) {
		goto exit_with_release;
        }

        // reference data, if DSL==0, let iTarget bother
        if (received_data_size > 0) {
		pSG_Entry = pAllocateSGListEntry();
		bAddEntryToSGList(iscsi_pdu->pDataPtr, pSG_Entry,
				  p_ctrl_pdu->rx_data.p_buf,
				  p_ctrl_pdu->rx_data.size);
        }

 	err = vPDUReceivedHandler(ptl_conn_p->iscsi_conn_h, iscsi_pdu);
	if (err != 0) {
		VD_LOG(VDLOG_ERROR,
		       "%s() Failed notifing Data-OUT pdu, ITT:0x%X, iscsi_pdu=0x%p)\n",
		       __func__, itt, iscsi_pdu);
		goto exit_with_release;
	}
	EXIT_LOG;
	return;

 exit_with_release:
	iser_ret = iser_ptl_global.iser_api.release_control(ptl_conn_p,
							    p_ctrl_pdu);
 exit_no_release:
	EXIT_LOG;
	return;
}


STATIC void iser_ptl_ctrl_notify(void                   *iscsi_conn_h, /* in */
				 struct iser_recv_pdu_t *p_ctrl_pdu)
{
	struct iser_ptl_conn_t  *ptl_conn_p = iscsi_conn_h;
	DWORD                   received_data_size;
	DWORD                   itt;
	BYTE                    flags;
	PDUInfo                 *iscsi_pdu;
	iser_status_t           iser_ret;
	int                     err;

	if (iser_ptl_notify_condition(ptl_conn_p,p_ctrl_pdu) != 0) {
		goto  exit_no_release;
	}
	// create iscsi pdu
	if (!iser_to_iscsi_pdu(p_ctrl_pdu,ptl_conn_p,&iscsi_pdu)) {
		goto  exit_with_release;
	}
	check_pdu_sanity(p_ctrl_pdu, &received_data_size, &itt, &flags);
        vOtherPduHeaderReceivedHandler(ptl_conn_p->iscsi_conn_h,
                                       iscsi_pdu,
                                       REQ_ALLOC,
                                       &err);
        if (err != 0) {
		VD_LOG(VDLOG_ERROR,
		       "%s() Failed vOtherPduHeaderReceivedHandler() "
		       "for pdu=0x%p, p_conn=0x%p\n",
		       __func__,
		       iscsi_pdu,
		       ptl_conn_p->iscsi_conn_h);

		goto  exit_with_release;
        }

        // print the structure of the allocated SG_List
        // vPrintListInfo(iscsi_pdu->pDataPtr);

        if (received_data_size > 0) {
		ITRACE(TRACE_ISER_PTL_RX_PRINT,
		       "%s() copying from 0x%p (%u) to 0x%p ValidSize=%u (size=%u)\n",
		       __func__,
		       p_ctrl_pdu->rx_data.p_buf,
		       p_ctrl_pdu->rx_data.size,
		       iscsi_pdu->pDataPtr->pListHead->pBuff,
		       iscsi_pdu->pDataPtr->pListHead->ulValidDataSize,
		       iscsi_pdu->pDataPtr->pListHead->ulBuffSize);

		err = bCopyBufftoSGList(iscsi_pdu, 0,
					p_ctrl_pdu->rx_data.p_buf,
					received_data_size);
		if (err == 0) {
			VD_LOG(VDLOG_ERROR,
			       "%s() failed bCopyBufftoSGList() for iscsi_pdu=0x%p\n",
			       __func__, iscsi_pdu);
			BUG();
		}
        }

	// Notify about the entire PDU,
	err = vPDUReceivedHandler(ptl_conn_p->iscsi_conn_h, iscsi_pdu);
	if (err != 0) {
		VD_LOG(VDLOG_ERROR,
		       "%s() Failed notifying ctrl pdu for pdu=0x%p, p_conn=0x%p\n",
		       __func__,
		       iscsi_pdu,
		       ptl_conn_p->iscsi_conn_h);
		goto  exit_with_release;
	}

 exit_with_release:
        // Notify ISER to release the pdu since its been already been copied.
        iser_ret = iser_ptl_global.iser_api.release_control(ptl_conn_p,
                                                            p_ctrl_pdu);
        if (iser_ret != ISER_SUCCESS) {
		VD_LOG(VDLOG_ERROR,"%s() Failed release_control (%u)\n",
		       __func__, iser_ret);
        }

 exit_no_release:
	EXIT_LOG;
	return;
}

//---------------------------------------------------------------------------
/*!
  @description
  called from ISER to notify a completion of put_data() or get_data()
  if previously requested when the call to put or get data was made.
  (via the notify_enable parameter)

  if (the task was created for a read command) then
    the notification is for a successfull put_data().
    iTarget is notified of a successfull data-in pdu transsmission.

  if (the task was created for a write command) then
    the notification is for a successfull get_data() .
    a fake pdu is created and passed to iTarget.

  @returns
*/
//---------------------------------------------------------------------------
STATIC void
iser_ptl_data_completion_notify(void *iscsi_task_h,
				int   sn )
{
	struct iser_ptl_task_t* ptl_task_p = iscsi_task_h;
	struct iser_ptl_conn_t* ptl_conn_p = ptl_task_p->conn_h;
	PDUInfo* iscsi_pdu;
	iSCSI_Sequence *seq;
	TaskInfo *pTask;
	int itt;
	ENTER_LOG;

	pTask = ptl_task_p->pTask;
	itt = pTask->itt;
	// (2) switch case for get_data() or put_data() completions
	switch (ptl_task_p->cmd_dir) {

	case ISER_DIR_IN: // put_data() completed
		ITRACE(TRACE_ISER_PTL_TX_PRINT,
		       "%s() put_data() completed for PDU=0x%p "
		       "conn: 0x%p, itt: 0x%X, sn: %d\n",
		       __func__, ptl_task_p->data_in_pdu,
		       ptl_conn_p, itt, sn);

		if (ptl_task_p->data_in_pdu != NULL) {
			iscsi_pdu = ptl_task_p->data_in_pdu;
			ptl_task_p->data_in_pdu = NULL;

			if (iscsi_pdu->scatterlist != NULL) {
				kfree(iscsi_pdu->scatterlist);
				iscsi_pdu->scatterlist = NULL;
			}

			vSentPDUHandler(ptl_conn_p->iscsi_conn_h,
					iscsi_pdu);
		}

		spin_lock(&ptl_task_p->task_lock);
		ITRACE(TRACE_ISER_PTL_TASK, "%s() rsp_rel_state = %d for ITT 0x%x\n",
		       __func__,
		       ptl_task_p->rsp_rel_state,
		       itt);

		switch (ptl_task_p->rsp_rel_state) {
		case RSP_REL_INIT: // The response wasn't sent yet. Wait for it
			ptl_task_p->rsp_rel_state = RSP_REL_WAIT_RSP;
			break;

		case RSP_REL_WAIT_DATA_CMPL: // The response was already sent. Release its PDU.
			break;

		default: // Unexpected
			VD_LOG(VDLOG_ERROR, "%s() unexpected rsp_rel_state (%d), ITT = 0x%x\n",
			       __func__, ptl_task_p->rsp_rel_state, itt);
			spin_unlock(&ptl_task_p->task_lock);
			goto exit_iser_ptl_data_completion_notify;
		}
		spin_unlock(&ptl_task_p->task_lock);

		// The task and rsp PDU should be released here (don't wait for send_pdu)
		if (ptl_task_p->rsp_rel_state == RSP_REL_WAIT_DATA_CMPL) {
			// since the response was sent already there is no point
			// in saving the task anymore.
			if (!ptl_task_p->resp_pdu) {
				VD_LOG(VDLOG_PANIC,
				       "ptl_task_p->resp_pdu is NULL (enDriverStatus = 0x%x)\n",
				       pTask->enDriverStatus);
				BUG();
			}
			vSentPDUHandler(ptl_conn_p->iscsi_conn_h,
					ptl_task_p->resp_pdu);
			ptl_task_p->resp_pdu = NULL;

			spin_lock(&ptl_conn_p->task_list_lock);
			iser_ptl_delete_task(ptl_task_p);
			spin_unlock(&ptl_conn_p->task_list_lock);
		}
		break;

	case ISER_DIR_OUT: // get_data() finsihed
		ITRACE(TRACE_ISER_PTL_TX_PRINT,
		       "%s() get_data() completed for conn: 0x%p, itt=0x%X, sn: %d\n",
		       __func__,ptl_conn_p, itt, sn);

		seq = &pTask->SolicitedArr[sn];
		if(sn != seq->ulR2TSN) {
			VD_LOG(VDLOG_PANIC,"%s(): sequence != sn\n",__func__);
			BUG();
		}

		panic_on((void *)seq->pdu < (void *)4096);
		iscsi_pdu = seq->pdu;
		seq->pdu = NULL;

		panic_on((void *)seq->scatterlist < (void *)4096);
		kfree(seq->scatterlist);
		seq->scatterlist = NULL;

		vPDUReceivedHandler(ptl_conn_p->iscsi_conn_h,
				    iscsi_pdu);
		break;

	default:
		VD_LOG(VDLOG_ERROR,"%s: illegal cmd dir:%d in task itt:0x%x\n",
		       __func__,ptl_task_p->cmd_dir,itt);
		break;

	} //switch

 exit_iser_ptl_data_completion_notify:
	EXIT_LOG;
}

//---------------------------------------------------------------------------
/*!
  @description
  called from ISER to notify an unsolicited termination or failure of
  the specified connection.
  iSCSI considers the connection handle to be invalid upon being so notified.
  iSER deallocates the connection and task resources associated with the
  terminated connection before notifying iSCSI of the termination.

  @returns
*/
//---------------------------------------------------------------------------
STATIC void
iser_ptl_conn_term_notify(iser_conn_handle_t conn_h ) //!< IN - the terminated connection
{
    struct iser_ptl_conn_t* ptl_conn_p = (struct iser_ptl_conn_t*)conn_h;

    ENTER_LOG;

    ptl_conn_p->conn_state = ISER_PTL_DISCONNECT;

    ITRACE(TRACE_ISER_PTL_GEN,
           "%s() changed conn=0x%p to ISER_PTL_DISCONNECT\n",
           __func__, ptl_conn_p);

    // will call iser_ptl_remove_conn() which deletes the connection
    vConnectionClosedHandler(ptl_conn_p->iscsi_conn_h,
                             CLOSE_CONN_GRACEFUL);
    EXIT_LOG;
}

//---------------------------------------------------------------------------
/*!
  @description
  called from ISER to notify the arrival of a data acknowledgement.
  SCSI Read data PDU is the only example of invoking this function.

  @returns
*/
//---------------------------------------------------------------------------
STATIC void
iser_ptl_data_ack_notify(void *iscsi_task_h,
                        int    data_sn)
{
    ENTER_LOG;
    VD_LOG(VDLOG_WARNING,"%s() T.B.D\n",__func__);
    EXIT_LOG;
}



//---------------------------------------------------------------------------
/*!
  @description
  called from ISER to change connection state to established.
  if the iser connection was not established (i.e. established=1)
  then close_conn_cb() will be called otherwise do nothing.

  @returns
  ISER_SUCCESS or ISER_FAILURE
*/
//---------------------------------------------------------------------------
STATIC iser_status_t
iser_ptl_connection_establish_notify(iser_conn_handle_t  iscsi_conn_h, //!< IN - the connection whoes state will be changed.
                                     int                 established)  //!< IN - true if connection established
{
    iser_status_t iser_ret = ISER_SUCCESS;
    struct iser_ptl_conn_t* ptl_conn_p = (struct iser_ptl_conn_t*)iscsi_conn_h;
    struct iser_recv_pdu_t *delayed_pdu = NULL;

    ENTER_LOG;

    if (ptl_conn_p->delayed_pdu != NULL) {
        delayed_pdu = ptl_conn_p->delayed_pdu;
        ptl_conn_p->delayed_pdu = NULL;
    }

    if (!established) {
        VD_LOG(VDLOG_ERROR,
               "%s: Failed to establish conn:0x%p, changing to FAILED\n",
               __func__, ptl_conn_p);
        goto connection_establish_failed;
    }

    /* connection established, check proper state transition */
    if (ptl_conn_p->conn_state != ISER_PTL_NEW ) {
        VD_LOG(VDLOG_ERROR,
               "%s() conn:0x%p, state supposed to be NEW, changing to FAILED\n",
               __func__, ptl_conn_p);
        iser_ret = ISER_FAILURE;
        goto connection_establish_failed;
    }

    /* declare connection established */
    ITRACE(TRACE_ISER_PTL_GEN,
           "%s: Changing conn:0x%p state from NEW to ESTABLISHED\n",
           __func__, ptl_conn_p);
    ptl_conn_p->conn_state = ISER_PTL_ESTABLISHED;

    if (delayed_pdu != NULL) {
        ITRACE(TRACE_ISER_PTL_GEN, "%s: Notify delayed ctrl pdu:0x%p on conn:0x%p\n",
               __func__, delayed_pdu, ptl_conn_p);
        iser_ptl_ctrl_notify((iser_conn_handle_t)ptl_conn_p, delayed_pdu);
    }
    EXIT_LOG;
    return iser_ret;

connection_establish_failed:
    ptl_conn_p->conn_state = ISER_PTL_FAILED;

    if (delayed_pdu != NULL) {
        ITRACE(TRACE_ISER_PTL_GEN, "%s: Release delayed ctrl pdu:0x%p on conn:0x%p\n",
               __func__, delayed_pdu, ptl_conn_p);
        iser_ret = iser_ptl_global.iser_api.release_control(ptl_conn_p,
                                                            delayed_pdu);
        if (iser_ret != ISER_SUCCESS) {
            VD_LOG(VDLOG_ERROR,
                   "%s: Failed release_control for delayed pdu:0x%p (%u)\n",
                   __func__, delayed_pdu, iser_ret);
        }
    }
    iser_ptl_remove_conn(ptl_conn_p,CLOSE_CONN_ABORTIVE);
    EXIT_LOG;
    return iser_ret;
} /* iser_ptl_connection_establish_notify */


/*
  called from iTarget to initialize the ISER PTL layer.
  PTL allocates its data structures and registers with the ISER module
  to be able to receive the initial Connection Requests.

  returns TRUE on successes
*/
int bISERInitPTLLayer()
{
    int ret = TRUE;

    ENTER_LOG;

    init_debug_str();

    iser_ptl_global.iscsi_cb.removePTLConnection = iser_ptl_remove_conn;
    iser_ptl_global.iscsi_cb.sendPDU = iser_ptl_send_pdu;
    iser_ptl_global.iscsi_cb.setPTLDataDigest = iser_ptl_set_data_digest;
    iser_ptl_global.iscsi_cb.setPTLHeaderDigest = iser_ptl_set_header_digest;
    iser_ptl_global.iscsi_cb.bGetDataInBuffer = iser_ptl_get_data_in_buffer;

    iser_ptl_global.iser_cb.command_notify = iser_ptl_cmd_notify;
    iser_ptl_global.iser_cb.data_out_notify = iser_ptl_dout_notify;
    iser_ptl_global.iser_cb.control_notify = iser_ptl_ctrl_notify;

    iser_ptl_global.iser_cb.data_completion_notify = iser_ptl_data_completion_notify;
    iser_ptl_global.iser_cb.data_ack_notify = iser_ptl_data_ack_notify;
    iser_ptl_global.iser_cb.conn_terminate_notify = iser_ptl_conn_term_notify;

    iser_ptl_global.iser_ext_cb.connection_establish_notify = iser_ptl_connection_establish_notify;
    iser_ptl_global.iser_ext_cb.connection_request_notify = iser_ptl_connection_request_notify;
    iser_ptl_global.iser_ptl_state = ISER_PTL_STOPPED;

    INIT_LIST_HEAD(&iser_ptl_global.conn_list_head);
    iser_ptl_global.conn_list_size =0;
    spin_lock_init(&iser_ptl_global.conn_list_lock);

    //======================================================
    // Initialize cache memory for iser_ptl_conn_t structures
    //======================================================
    iser_ptl_global.conn_slab = kmem_cache_create("itarget_iserconn",
                                                  sizeof(struct iser_ptl_conn_t),
                                                  0,
                                                  SLAB_HWCACHE_ALIGN,
                                                  NULL,NULL );
    if (iser_ptl_global.conn_slab == NULL) {
        VD_LOG(VDLOG_ERROR,"%s() Failed to allocate conn_slab\n",__func__);
        ret = FALSE;
        goto exit_iser_init_ptl_layer;
    }

    //======================================================
    // Initialize cache memory for iser_ptl_task_t structures
    //======================================================
    iser_ptl_global.task_slab = kmem_cache_create("itarget_isertask",
                                                  sizeof(struct iser_ptl_task_t),
                                                  0,
                                                  SLAB_HWCACHE_ALIGN,
                                                  NULL,NULL );
    if (iser_ptl_global.task_slab == NULL) {
        VD_LOG(VDLOG_ERROR,"%s() Failed to allocate task_slab\n",__func__);
        ret = FALSE;
        goto exit_iser_init_ptl_layer;
    }

    exit_iser_init_ptl_layer:
    EXIT_LOG;
    return ret;
} /* bISERInitPTLLayer */

//---------------------------------------------------------------------------
/*!
  @description
  called from iTarget to let PTL know that iTarget module is being
  removed.
  PTL deallocate all its data structures and unregisters from the ISER module.

  @returns
*/
//---------------------------------------------------------------------------
void
vISERReleasePTLLayer(void)
{
    ENTER_LOG;

    if (iser_ptl_global.iser_ptl_state != ISER_PTL_STOPPED) {
        vISERStopPTLLayer();
    }
    if (iser_ptl_global.conn_slab != NULL) {
        kmem_cache_destroy(iser_ptl_global.conn_slab);
        iser_ptl_global.conn_slab = NULL;
    }
    if (iser_ptl_global.task_slab != NULL) {
        kmem_cache_destroy(iser_ptl_global.task_slab);
        iser_ptl_global.task_slab = NULL;
    }

    ITRACE(TRACE_ISER_PTL_GEN,"%s() iSER datamover removed\n",__func__);

    EXIT_LOG;
} /* vISERReleasePTLLayer */

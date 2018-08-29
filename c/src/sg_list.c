#include <stdlib.h>

//==================================================================================
//                                  Definitions
//==================================================================================
#define SG_LIST_SIZE 60
#define SG_ENTRY_SIZE 20

            
//==================================================================================
//                                      Types
//==================================================================================
typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef int            BOOL;
typedef unsigned int  UINT;
typedef unsigned long ULONG;
typedef unsigned short USHORT;
typedef long LONG;

typedef struct SG_Entry
{
    ULONG ulValidDataSize;  /* The size of valid data in the buffer  */
    ULONG ulBuffSize;       /* The size of the mem buffer that the pBuff points to*/
    BYTE *pBuff;            /* A pointer to a buffer of sequential mem */
    struct SG_Entry *pNext; /* A pointer to the next basic block in the list */
}SG_Entry;

/* A container of SG basic block */
typedef struct SG_ListInfo
{
    UINT uiListStatus;
//    AllocTypes enAllocType;
    ULONG ulReqDataLength; /* The amount of memory that was requested when pGetMem() was activated */
    ULONG SG_EntriesNum;   /* The number of basic blocks (SG_Entry) that were allocated */
    SG_Entry *pListHead;   /* A pointer to the first SG_Entry in the List (1 or more) of SG_Entries */
    SG_Entry *pListTail;   /* A pointer to the last SG_Entry in the List (1 or more) of SG_Entries */
    struct SG_ListInfo *pNext; /* A pointer to the next SG container (for Data-out PDU's accumulation) */
}SG_ListInfo;

void vPrintListInfo(struct SG_ListInfo * pListInfo);
void build_sg_list(ULONG size);

//==================================================================================
//                                  Functions
//==================================================================================
void vPrintListInfo(struct SG_ListInfo * pListInfo)
{
    UINT i;
    UINT j = 1;
    UINT uiTotalListDataLen = 0;
    SG_Entry *pScanList;

    while(pListInfo != NULL)
    {
        uiTotalListDataLen += pListInfo->ulReqDataLength;
        pScanList = pListInfo->pListHead;

        printf("\t List %d size is %ld devided into %ld Mem blocks:\n", 
               j, 
               pListInfo->ulReqDataLength, 
               pListInfo->SG_EntriesNum);

        for(i = 0 ; i < pListInfo->SG_EntriesNum; i++)
        {
            if(pScanList != NULL)
            {
                printf("\t\t Block %d size is %ld/%ld bytes \n",
                       i,
                       pScanList->ulValidDataSize,
                       pScanList->ulBuffSize);
            }
            else
            {
                printf("Chaining Error!!! in list 0x%08X\n", (unsigned long)(pListInfo));
                return;
            }

            pScanList = pScanList->pNext;
        }

        if(pScanList != NULL)
        {
            printf("Error!!! Last SG_Entry in list 0x%08X pNext is not NULL\n", (unsigned long)(pListInfo));
            return;
        }

        pListInfo = pListInfo->pNext;
        j++;
    }
    
    if(uiTotalListDataLen > 0)
    {
        printf("\t TOTL DATA SIZE IS %d \n",uiTotalListDataLen);
    }
    else
    {
        printf( "\t Error an Empty list\n");
    }
}

//======================================================================
// build_sg_list 
// assuming that one sg_entry reresents a buffer of 20 Bytes.
// and one sg_list can reresents a buffer of up to 60 Bytes.
// build a suitable to accommodate the memory requested.
//======================================================================
void
build_sg_list(ULONG size)
{
    ULONG alloced_size =0 ;
    SG_ListInfo* psg_list;
    SG_Entry*    psg_entry;
    ULONG        num_of_sg_list;
    ULONG        num_of_sg_entry;
    ULONG        index;

    num_of_sg_list = (size / SG_LIST_SIZE) + (size % SG_LIST_SIZE);

    for (index=0; index < num_of_sg_list; index++) {

        if (size > SG_LIST_SIZE) {
            num_of_sg_entry = (SG_LIST_SIZE / SG_ENTRY_SIZE);
            size -= SG_LIST_SIZE;
            alloced_size = SG_LIST_SIZE;
        }
        else {
            num_of_sg_entry = (size / SG_ENTRY_SIZE) + (size % SG_ENTRY_SIZE);
            alloced_size = 
        }

        psg_list = malloc(sizeof(SG_Entry));
        psg_list->pListHead = NULL;
        psg_list->pListTail = NULL;
        psg_list->pNext     = NULL;
        psg_list->SG_EntriesNum = num_of_sg_entries;
        psg_list->ulReqDataLength = 


    }//for (...
    
}




int 
main (int argc, char *argv[])
{

}



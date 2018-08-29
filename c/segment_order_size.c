#include  <stdio.h>

#define PAGE_SIZE 512
unsigned long uHashSegmentOrder =0;
unsigned long uHashSegmentMask  =0;

///////////////////////////////////////////////////////////////
#define DEF_BINARYTREE_COUNT			2
typedef struct _sBTreeHead_
{
    // the offset where the key of the item in the tree
    // resides. all the items in the tree hold this value in the same offset
	I32			iIndexOffset;

    // the number of items in the tree
	UI32		uBTreeSize;

    // the root of the tree
	struct _sBTreeItem_
				*psFirstItem;

    // true - recalc the value of the items so as make sure that the tree
    // is balanced.
    // look at the macro _kbase_item_index()
	BOOLEAN		bIndexBreak;
	BOOLEAN		bReserved[3];
} SBTREEHEAD,	*PSBTREEHEAD;

typedef struct _sHashBTree_
{
	SBTREEHEAD	sBTreeHead;
	SRWLOCKHANDLE
				sBTreeRWLock;

	// iTreeOffset if the offset from a
	// substracting this from a tree item will
	// get you the hash item
	I32			iTreeOffset;
} SHASHBTREE,	*PSHASHBTREE;

typedef struct _sHashEntry_
{
	SHASHBTREE	sHashTrees[DEF_BINARYTREE_COUNT];
	PSHASHBTREE	psCurrentWrite;
	PSHASHBTREE	psCurrentRead;
	SSPINLOCKHANDLE
				sHashEntryLock;
} SHASHENTRY,	*PSHASHENTRY;


///////////////////////////////////////////////////////////////

int main(void)
{
	unsigned int uHashSegmentOrigSize = 40;
	unsigned int uHashSegmentSize = 40;


	//
	// Increase the entry counter
	//   by order until PAGE_SIZE
	//   is reached.
	//
	while ( 1 )
	{
		// Increase by order.
		uHashSegmentSize <<= 1;

		// Over page size ?
		if (uHashSegmentSize > PAGE_SIZE)
		{
			// Undo order increase.
			uHashSegmentSize >>= 1;

			// Done.
			break;
		}

		// Increase by order.
		uHashSegmentOrder ++;
	}

	// Create the segment mask.
	uHashSegmentMask = (1 << uHashSegmentOrder) - 1;

   printf("uHashSegmentOrigSize: %d,  PAGE_SIZE: %d, uHashSegmentSize: %d, uHashSegmentOrder: %lu, uHashSegmentMask: 0x%lx\n" 
          ,uHashSegmentOrigSize,  PAGE_SIZE, uHashSegmentSize, uHashSegmentOrder, uHashSegmentMask); 

	// OK!
	return 0;
}


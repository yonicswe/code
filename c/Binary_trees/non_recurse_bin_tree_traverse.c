#include <stdlib.h>
#include <stdio.h>

//
// this approach requires 2 more fields in the tree node structure 
// a visited boolean and a parent pointer.
//



typedef struct _TreeNode { 
    int Value; 
    struct TreeNode Left; 
    struct TreeNode Right; 
    struct TreeNode Parent; 
    int Visited; 
}TreeNode; 


void NonRecursive(void) 
{ 
    TreeNode currNode = root; 
    while (true) 
    { 
        if (currNode == null) 
            break; 

        if (currNode.Left != null && currNode.Left.Visited != 1) { 
            // if left sub-tree exist and was not yet visited
            // then do so now.
            currNode = currNode.Left; 
        }
        else if (currNode.Visited == 0) { 
            // in-order traversal : if there is no left sub-tree then print 
            printf("%d ",currNode.Value); 
            currNode.Visited = 1; 
        } 
        else if (currNode.Right != null && currNode.Right.Visited != 1) {
            // if right sub-tree exist and was not yet visited 
            // then do so now
            currNode = currNode.Right; 
        }
        else {
            // if there were no left or right sub-trees or if they were both 
            // already been visited then its time to back to parent.
            currNode = currNode.Parent;
        }
    }
}




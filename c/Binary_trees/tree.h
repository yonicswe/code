struct TreeNode { 
    int Value; 
    TreeNode Left; 
    TreeNode Right; 
    TreeNode Parent; 
    byte Visited; 

    public TreeNode(int value) 
    { 
        Value = value; 
    } 
}

void NonRecursive(void) 
{ 
    TreeNode currNode = root; 
    while (true) 
    { 
        if (currNode == null) 
            break; 

        if (currNode.Left != null && currNode.Left.Visited != 1) 
            currNode = currNode.Left; 
        else if (currNode.Right != null && currNode.Right.Visited != 1) 
            currNode = currNode.Right; 
        else if (currNode.Visited == 0) 
        { 
            Console.Write(currNode.Value + " "); 
            currNode.Visited = 1; 
        } else
        currNode = currNode.Parent;
    }
}

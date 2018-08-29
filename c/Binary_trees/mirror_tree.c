typedef struct block
{
  char data;
  struct block *left;
  struct block *right;
}node;

void mirror(node *start)
{
  if(start == NULL) return;
  node *temp;
  temp = start->left;
  start->left = start->right;
  start->right = temp;
  mirror(start->left);
  mirror(start->right);
}

void MirrorBinaryTreeIterative(node *start)
{
  node *stack[50] = {0};
  int top = 0;

  // adding root to stack
  stack[top++] = start;

  // while stack is not empty
  while(top != 0)
  {
    top = top-1;
    if(stack[top] != NULL)
    {
      node *curNode = stack[top];

      // node swaping
      node *temp;
      temp = curNode->left;
      curNode->left = curNode->right;
      curNode->right = temp;

      // adding left and right nodes to the stack
      stack[top++] = curNode->left;
      stack[top++] = curNode->right;
    }
  }
}

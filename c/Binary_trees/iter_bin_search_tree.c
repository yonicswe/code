#include <stdio.h>
#include <stdlib.h>

struct btree_node_t{
    // for iterative traverse
    struct btree_node_t *parent;
    int visited;

    // left and right sub-trees.
    struct btree_node_t *left;
    struct btree_node_t *right;

    // the data
    int data; 
};

struct btree_t {
   struct btree_node_t *head;
};


struct btree_node_t *btree_node_alloc(int data);
void btree_insert(struct btree_t *t, struct btree_node_t *new);
void btree_print(struct btree_t t);
void btree_traverse(struct btree_t t);

int raw_data[] = {80,25,50,75,35,10,47,32,12,11,8,95,97};
// int raw_data[] = {80,25,50,75,35,10,47,32,12,8};
// int raw_data[] = {80,25,50,50,75,35,10,47,32,12,8};
// int raw_data[] = {8,10,12,25,32,35,47,50,50,75,80};
// int raw_data[] = {80,75,50,47,35,32,25,12,10,8};
int raw_data_sz = sizeof(raw_data)/sizeof(int);


int
main()
{  
   int i;
   struct btree_node_t *new;
   struct btree_t t; 
   
   t.head = NULL;

   for (i=0; i < raw_data_sz ; i++){
      new = btree_node_alloc(raw_data[i]);
      printf("%d\t",raw_data[i]);
      btree_insert(&t, new);
   } 

   printf("\n");
//    btree_print(t); 
   btree_traverse(t);
   printf("\n");

   return 0;
}


struct btree_node_t *
btree_node_alloc(int data)
{
    struct btree_node_t *pt;

    pt = malloc(sizeof(struct btree_node_t));

    if ( pt == NULL ) 
        return NULL;

    pt->parent = NULL;
    pt->right  = NULL;
    pt->left   = NULL;
    pt->visited   = 0;
    pt-> data  = data;

    return pt;
} 

void
btree_insert(struct btree_t *t, struct btree_node_t *new)
{
   struct btree_node_t *pt = t->head; 
   int data = new->data;

   while (1)
   {
        if (pt == NULL) 
        { // empty tree;
            t->head = new;
            return;
        }

        if (data < pt->data ) 
        {
            if (pt->left == NULL ) 
            {
               pt->left = new; 
               new->parent = pt;
               return; 
            }
   
            pt = pt->left; 
        }            
        else
        {
            if (pt->right == NULL)
            {
               pt->right = new;
               new->parent = pt;
               return;
            }
            
            pt = pt->right; 
        } 
   } 
}


void 
btree_traverse(struct btree_t t)
{
    struct btree_node_t *pt = t.head; 

    while (1) 
    { 
        if (pt== NULL) 
            break; 

        if (pt->left != NULL && pt->left->visited  == 0) { 
            // if left sub-tree exist and was not yet visited
            // then do so now.
            pt = pt->left; 
        }
        else if ( pt->visited == 0) { 
            // in-order traversal : if there is no left sub-tree then print 
            printf("%d\t", pt->data); 
            pt->visited = 1; 
        } 
        else if ( pt->right != NULL && pt->right->visited == 0) {
            // if right sub-tree exist and was not yet visited 
            // then do so now
            pt = pt->right; 
        }
        else {
            // if there were no left and right sub-trees or if they were both 
            // already visited then its time to go back to parent.
            pt = pt->parent;
        }
    }
}


void
back_to_parent( 
    struct btree_node_t **pt,
    struct btree_node_t **last)
{

    *pt = (*pt)->parent;

    // if we just stepped up from left sub-tree then we need to print.
    if ( (*pt)->data > (*last)->data ) {

        printf("%d\t", (*pt)->data);

        *last = *pt; 
    } 
}




//
// iterative traversal of a binary tree.
// behaves the same as its recursive counter part by printing the 
// node when backing from left side.
// but it needs to identify the 2 cases where it backed from right 
// 1) backing from right when there is no right sub-tree
// 2) backing from right sub-tree.
void 
btree_print(struct btree_t t)
{
   struct btree_node_t *pt;
   struct btree_node_t *proot = t.head;
   struct btree_node_t *last = NULL;

   pt = proot;

   while (1) 
   {

        if (last) {
            // if last is set then we already started printing.
            // i.e were already backing from nodes to their parents.
            
            if (pt->data < last->data) {
                // if were in a node whoes value is smaller from the last printed 
                // value then we just returned from right sub-tree 

                if ( pt == proot ) 
                    break;

                // we just returned from right sub-tree, nothing more to do 
                // lets return to parent.
                back_to_parent(&pt, &last);

                continue;
            } 
        }
 
        // check left subtree
        if (pt->left) {
            if (last) {
                // have we already visited the left side ? ?? 
                if (pt->left->data > last->data ) { 
                    // no we didnt lets do it now 
                    pt = pt->left;
                    continue; 
                } 
            }
            else {
                // lets traverse the left sub-tree.
                pt = pt->left;
                continue;
            } 
        }
        else { 
            // no left son means coming back from left side (i.e print data)
            printf("%d\t", pt->data);
            last = pt;
        }

        // check right subtree
        if (pt->right){
            pt = pt->right; 
            continue;
        }
        else {
            if ( pt == proot )
                break;

            // no right sub-tree, back to parent
            back_to_parent(&pt, &last);
        }

   } // of while (1) 
}











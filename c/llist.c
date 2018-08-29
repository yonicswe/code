

#include <stdlib.h>

struct node{

	int data;
	struct node* next;
};

struct list{
	struct node* head;
	int size;
};

init_list(struct list* l)
{
	l->head = NULL;
	l->size=0;

}


struct node* 
alloc_node(int data)
{
	struct node* n;
	
	n = (struct node*) malloc(sizeof(struct node));
	n->next= NULL;
	n->data = data;
	return n;
}

void
free_node(struct node* n)
{
	printf("%s: data: %d\n",__func__, n->data);
	free(n);
}

void
free_list(struct list* l)
{

	struct node* n;
	struct node* tmp;
	n = l->head;
	while (n->next != NULL) {
		tmp = n->next;
		free_node(n);
		n = tmp; 
	}
};

void 
print_list(struct list* l)
{

	struct node* n;
	n = l->head;

	while (n != NULL ){
		printf("|%d|->",n->data);
		n = n->next;
	}

	printf("NULL\n");

}


void 
add_node_sorted(struct list* l, struct node* n)
{
	if (l->head == NULL ) {
		l->head = n;	
		l->size=1;
	}
	else {
		struct node* tmp;
		tmp = l->head;
		while (n->data > tmp->data && tmp->next != NULL ) 
			tmp = tmp->next;

		if (tmp == l->head) {
			// before head 
			n->next = l->head;
			l->head = n; 
		}
		else if (tmp->next == NULL) {
			// tail
			tmp->next = n;
		}
		else{
			// other cases inside list.
			struct node* t = tmp->next;
			tmp->next = n;
			n->next = t; 
		}
	}
		
		
}

void
populate_list(struct list* l, int* a, int size_a)
{

	int i;

	init_list(l);
	
	for (i=0; i<size_a; i++){
		add_node_sorted(l, alloc_node(a[i]));	
	}

}

void 
rev_list(struct list* l) 
{

	struct node* prv;
	struct node* cur;
	struct node* nxt;
	
	prv = NULL;
	cur = l->head;
	nxt = l->head;

	while (nxt != NULL) {
		nxt = nxt->next; 
		cur->next = prv;
		prv = cur; 
		cur = nxt;
	}

	l->head = prv;

}

int 
main(int argc, char* argv[]) 
{

	int a[] = {10, 12, 31, 45, 100, 2, 12, 1};
	int size_a= sizeof(a)/sizeof(int);
	struct list l;

	populate_list(&l, a, size_a);
	
	print_list(&l);
	rev_list(&l);
	print_list(&l);

	free_list(&l);
	
	return 0;
}

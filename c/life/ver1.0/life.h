
#define CONF_MAX_ROW_SIZE 120

struct node{
	int *cell;
	int col;
	int row;
};

struct matrix{
	int cols;
	int rows;
	int* board;
	struct node cur_node;
};



struct matrix* alloc_mattix(char* conf_file_name);
void free_matrix(struct matrix*);
void print_matrix(struct matrix*);
int count_neighs(struct matrix*, struct node*);
struct node* get_next_node(struct matrix*);
int live_or_die(int neighs, struct node*);
void iterate_matrix(struct matrix*, int);

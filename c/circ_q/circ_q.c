
#define MAXQUEUE 10

struct queue {
	int count;
	int front;
	int rear;
	struct queue_entry entry[MAXQUEUE];
}

/*
 * Append: append an entry to the queue
 * Pre:    The queue q has been created and is not full
 * Post:   The entry x has been stored  in the queue as its last entry
 */
void Append(


/* queue operations
 * -------------------
 *  void create_queue(queue *q)
 *  int  queue_empty(queue *q)
 *  int queue_full(queue* q)
 *  void append(queue_entry x, queue *q)
 *  void serve(queue_entry *x, queue *q)
 *  int queue_size(queue *q)
 *  void clear_queue(queue *q)
 *  void queue_front(queue_entry *x, queue *q)
 *  void traverse_queue(queue *q, void (*visit)(queue_entry x))
 */

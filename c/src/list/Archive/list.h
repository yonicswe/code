
struct list_hook {
	struct list_hook* next;
	struct list_hook* prev;
	void* ent;
};

#define INIT_LIST_HOOK(l, d) \
	(l)->next = (l)->prev = (l); \
	(l)->ent = (void*)(d)

#define list_empty(h) \
	((h)->next == (h))

#define list_add_tail(h, l) \
	(l)->next = (h); \
	(l)->prev = (h)->prev; \
	(h)->prev->next = (l); \
	(h)->prev = (l)

#define list_del_init(l) \
	(l)->next->prev = (l)->prev; \
	(l)->prev->next = (l)->next; \
	INIT_LIST_HOOK((l), NULL)

#define list_for_each_safe(h, l, t) \
	for ((l) = (h)->next, (t)=(l)->next; (l) != (h); (l)=(t), (t)=(t)->next )
	
	

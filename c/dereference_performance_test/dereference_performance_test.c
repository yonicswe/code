
struct b_t {
	int x;
};

struct c_t {
	struct b_t *b;
	int x;
};

struct d_t {
	struct c_t *c;
	int x;
};


struct b_t gb;
struct c_t gc;
struct d_t gd;

int main()
{
	int x;
	struct d_t *d = &gd;

	d->c = &gc;
	d->c->b = &gb;

	x = d->x;
	x = d->c->x;
	x = d->c->b->x;

	return 0;
}



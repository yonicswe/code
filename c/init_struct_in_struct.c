

struct dad_t {
	int x;
	int y;
};

struct child_t {
	struct dad_t *d;
	int x;
};

int main()
{

	struct child_t c = {};

	return 0;
}

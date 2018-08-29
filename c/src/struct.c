typedef struct yoni yoni;

struct yoni{
	int x;
	int y;
	yoni* next;
};

int main(void)
{
	yoni a;
	int m;

	a.x = 1;
	a.y = 2;

	m = a.x + a.y;

	
	return 0;
}

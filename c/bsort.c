
void
print_a(int* a, int size_a)
{
	int i;

	for (i=0; i<size_a; i++){
		printf("%d\t",a[i]);
	}
	printf("\n");

}

void
swap_a_b(int* a, int* b)
{

	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void
b_sort(int* a, int size_a)
{

	int i,j;

	for (i=size_a-1; i>0 ; i--)
		for (j=i-1; j>=0 ; j--) {
			if (a[i] < a[j]) 
				swap_a_b(&a[i], &a[j]);
		}
			
}

int
main(int argc, char* argv[]) 
{
	int a[] = {10, 12, 31, 45, 100, 1, 12};
	int size_a= sizeof(a)/sizeof(int);
	
	print_a(a, size_a);
	b_sort(a,size_a);
	print_a(a, size_a);

	return 0;
}

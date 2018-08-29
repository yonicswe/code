

void
swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;	
//	*a = *a + *b ;
//	*b = *a - *b ;
//	*a = *a - *b ;
}


int
partit(int* a, int low, int high)
{
	int left = low;
	int right = high;
	int p = a[low];

	while (left < right) {
		while ( a[left] <= p && left < high ) left++;
		while ( a[right] > p && right > low  ) right--;
		if (left < right)
			swap(&a[left], &a[right]);
	}

	a[low] = a[right];
	a[right] = p;
	return right;
}



void
qs(int* a, int low, int high)
{
	int p;

	if (low >= high) 
		return;

	p = partit(a, low, high);
	qs(a,low,p-1);
	qs(a,p+1, high);
}

void
prnt_data(int* a, int size)
{
	char *buf;
	int buf_size = (sizeof(int)+1) * size;
	int n=0;
	int i=0;
	buf = (char*)malloc(buf_size);

	do {
		n += sprintf(buf + n, "%d ",a[i]);
		i++;
	}while (i<size);


	printf("%s\n",buf);
	

	free(buf);

}



int
main(int argc, char* argv[]) 
{

	int a[] = {45,38,12,62,42,34,8,24,76,48};
	int size = sizeof(a)/sizeof(int);

	prnt_data(a,size);
	qs(a,0,size-1);
	prnt_data(a,size);
	
	return 0;

}

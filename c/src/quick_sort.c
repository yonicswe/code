#include <stdlib.h>

void
swap(int* a, int one, int other)
{
	int tmp;
	tmp = a[one];
	a[one] = a[other];
	a[other] = tmp;
}

//45,38,12,62,42,34,8,24,76,48
//          +          +
//45,38,12,24,42,34,8,62,76,48

int
partition(int* a, int low, int high)
{
	int pivot = a[low];
	int left = low;
	int right = high;

	while (left < right) {
		while (a[left] <= pivot && left < high)
			left++;

		while (a[right]> pivot && right > low )
			right--;

		if (left < right)
			swap(a,left,right);
	}

	a[low] = a[right];
	a[right] = pivot;
	return right;
}


void 
quick_sort(int *a, int low, int high)
{
	int pivot;

	if (low >= high) {
		return;
	}

	pivot = partition(a,low,high);
	quick_sort(a,low,pivot-1);
	quick_sort(a,pivot+1, high);
}

print_list(int* a, int size)
{
	char buffer[1024]={0};
	int index;
	int len=0;

	for (index =0; index<size; index++){
		sprintf((char*)(buffer+len),"[%4d] ",a[index]);
		len += 7;
	}

	printf("%s\n",buffer);
}

#define SIZE 10 

int 
main (int argc, char *argv[])
{
	//              0   1  2  3  4  5 6  7  8  9
	int data[] = {45,38,12,62,42,34,8,24,76,48};

	print_list(data,SIZE);
	quick_sort(data,0,SIZE-1);
	print_list(data,SIZE);
}

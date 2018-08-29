

void
swap(int *x1, int *x2)
{
        int tmp;
        tmp = *x1;
        *x1 = *x2;
        *x2 = tmp;
}

void
bub_sort(int* arr, int size)
{
        int i,j;

        for (i=size-1; i>0 ; i--) {
                for (j=i-1 ; j>=0 ; j--) {
                        if (arr[i] < arr[j]) {
                                swap(&arr[j], &arr[i]);
                        }

                }
        }


}

int 
main (int argc, 
	 char *argv[])
{
	 int arr[6] = {10,12, 34,2,8,27};
        int size = 6;

	 
	 bub_sort(arr,size);

	 return 0;
	 

}

#include <stdio.h>
#include <stdlib.h>

#define MAX 5


int insert(int queue[], int *writer_index, int reader_index, int value)
{
   if(((*writer_index)+1)%MAX == reader_index)
   {
      printf("The queue is full can not insert value: %d\n", value);
      return 1;
   }
	//write
   queue[*writer_index] = value;
	//increment index
	*writer_index= (*writer_index +1) % MAX;
	return 0;
}

int delete(int queue[], int *reader_index, int writer_index, int * value)
{
   if(((*reader_index)+1)%MAX == writer_index)
   {
      printf("The queue is empty\n");
      return 1;
   }

   //read
   *reader_index = (*reader_index + 1) % MAX;
   //increment index
   *value = queue[*reader_index];
	return 0;
}

int main()
{
	int ret=0;
	int queue[MAX];
	int reader_index,writer_index;
	int n,value;
	reader_index=0; writer_index=1;

	insert(queue,&writer_index,reader_index,1);
	insert(queue,&writer_index,reader_index,2);
	insert(queue,&writer_index,reader_index,3);
	insert(queue,&writer_index,reader_index,4);
  
	if (!(ret = delete(queue,&reader_index,writer_index,&value))) 
	   printf("The value deleted is %d\n",value);
	if (!(ret = delete(queue,&reader_index,writer_index,&value))) 
	   printf("The value deleted is %d\n",value);
	if (!(ret = delete(queue,&reader_index,writer_index,&value))) 
	   printf("The value deleted is %d\n",value);
	if (!(ret = delete(queue,&reader_index,writer_index,&value))) 
	   printf("The value deleted is %d\n",value);
}

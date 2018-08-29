
#define MAX_NAMES 3 
#define MAX_LISTS 3

struct name_list{
	 int size;
	 char *name[MAX_NAMES];
};


struct name_list name_list_arr[MAX_LISTS] = {
	 {0},
	 {2,{"dave","moshe"}},
	 {3,{"yair","haim","oren"}}
};
	 
int main (int argc, char *argv[])
{
	 int i,j;
	 for (i=0; i<MAX_LISTS; i++){
		 for (j=0; j<name_list_arr[i].size; j++)
			 printf("%s ",name_list_arr[i].name[j]);
		 printf("\n");
	 }

       return 0;
}

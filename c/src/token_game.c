#include <string.h>
#include <stdio.h>



char a[] = "yoni ,cohen ,and, dvora";
char *str =(char*) &a;
	
int main(void){

	char *token;

    printf("%d %d\n",4096/4096, 4096%4096);


    while ((token=strtok(str,","))!=NULL){
		printf("%s",token);
	//	strncpy(tc,token,MAX_WRITE_BUFFER-1);
		str = NULL;	
	}

	return 0;
}

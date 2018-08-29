#include <stdlib.h>
int main (int argc, char *argv[])
{
	int i,j,tmp ;
	int trace_mask=0;//=0xaa;
	char trace_mask_str[100];//="abcdef";
	char num_str[4]="0x";
	int trace_mask_len;
	int hex_num;

	memset(trace_mask_str,0,100);

	printf("input=[%s]\n",argv[1]);

	strncpy(trace_mask_str, argv[1], 100);

	trace_mask_len = strlen(trace_mask_str);

	for (i=trace_mask_len-1; i>1; i--) {
		num_str[2] = trace_mask_str[i];
		hex_num = strtod(num_str, NULL);
		for (j=0;j<4;j++) {
			tmp= 1 & (hex_num>>j);
			printf("%1d ",tmp);
		}
	}

	printf("\n");

	return 0;

}

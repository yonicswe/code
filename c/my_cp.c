#include <stdio.h>
#include <errno.h>

void
usage(void)
{

	printf("my_cp <src.file> <dst.file>\n");
	exit(1);
}

int
main(int argc, char* argv[])
{

	FILE* src_fp;
	FILE* dst_fp;
	char* src_file_name;
	char* dst_file_name;
	char str_2_cp[120] = {0};
	char* eof=NULL;


	if (argc != 3) 
		usage();

	src_file_name = argv[1];
	dst_file_name = argv[2];
	
	src_fp = fopen(src_file_name, "r");
	if (src_fp == NULL) {
		printf("failed to open %s err: %s",src_file_name, strerror(errno));
		goto exit_open_src_failed;
	}
		
	dst_fp = fopen(dst_file_name, "w");
	if (src_fp == NULL) {
		printf("failed to open %s err: %s",dst_file_name, strerror(errno));
		goto exit_open_dst_failed;
	}
		

	/* start to copy */
	while ((eof = fgets(str_2_cp, 120, src_fp)) != NULL){
		fputs(str_2_cp, dst_fp);
	}

	fclose(src_fp);
	fclose(dst_fp);
	
	return 0;

exit_open_dst_failed:
	fclose(src_fp);
exit_open_src_failed:
	return 1;
}

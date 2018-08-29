
#include <string.h>
#include <iconv.h>
#include <errno.h>
#include <stdio.h>

#define SRC_NAME_SIZE 100
#define DST_NAME_SIZE 100

char* str = "yoni cohen";

void
conv(iconv_t ic, 
     char *src_name, 
     size_t *src_name_len, 
     char *dst_name, 
     size_t *dst_name_len)
{
    iconv(ic, &src_name, src_name_len, &dst_name, dst_name_len);
}

int
main()
{

    char src_name[SRC_NAME_SIZE];
    char dst_name[DST_NAME_SIZE];
    size_t src_name_len = SRC_NAME_SIZE;
    size_t dst_name_len = DST_NAME_SIZE;


    memset(src_name, 0x5a, src_name_len);
    memset(dst_name, 0x5a, dst_name_len);

    strncpy(src_name, str, strlen(str));
//     strncpy(src_name, str, SRC_NAME_SIZE);

    iconv_t ic = (iconv_t)-1;

    ic = iconv_open("UTF8","UNICODE"); 


    src_name_len = 1000;
    conv(ic, src_name, &src_name_len, dst_name, &dst_name_len);

    printf("errno - (%d)%s\n", errno, strerror(errno));

    iconv_close(ic);

    return 0;
}

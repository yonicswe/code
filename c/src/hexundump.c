#include <stdio.h>
#include <strings.h>

main(int ac,char **av)
{
    char c1,c2;
    int i1,i2;

 read:
    if((c1=getchar()) == EOF) {
        goto done;
    }
    if(!isxdigit(c1)){
        // putchar(c1);
        //        printf("c1=%d(%c) !=xdigit going to read\n",c1,c1,c2,c2);
        goto read;
    }
    if((c2=getchar()) == EOF) {
        //        putchar(c1);
        goto done;
    }
    if(!isxdigit(c2)){
        //        putchar(c1);
        //        putchar(c2);
        //        printf("c1=%d(%c) c2=%d(%c)!=xdigit going to read\n",c1,c1,c2,c2);
        goto read;
    }
    i1=(isdigit(c1) ? c1-'0' : tolower(c1) -'a' +10);
    i2=(isdigit(c2) ? c2-'0' : tolower(c2) -'a' +10);
    //    printf("c1=%d(%c) c2=%d(%c), result=%d(%c)\n",i1,c1,i2,c2,i1*16+i2,i1*16+i2);
    putchar(i1*16+i2);
    i1=0;i2=0;c1=0;c2=0;
    goto read;

 done:
    exit(0);
}

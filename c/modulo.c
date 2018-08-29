#include <stdio.h>
#include <string.h>
/*
 * example of how can num & (num -1)
 * can replace modulo.
 * notice that this can only work when num is a power of 2
 * otherwise it wont work
 */

int main(int argc, char *argv[])
{
    int i;
    int x1;
    int x2;
    int mod_with;

    mod_with = strtol(argv[1], NULL, 10) ;

    printf("              x1, x2\n");
    for (i=0; i<40; i++){

        x1 = i % mod_with;
        x2 = i & (mod_with - 1);

        printf("%3d mod %3d = %3d, %3d\t%3s\n",i,mod_with, x1, x2, (x1==x2)?"":" <-- differ");
    }



	return 0;
}

#include <stdio.h>

#define ONE 1
#define TWO 2
#define THREE 3


// #define DEF_PATH_TWO(x) x.DEF_PATH_ONE(ONE)
// #define DEF_PATH_THREE(x) x.DEF_PATH_TWO(TWO)

// #define PASTE(x,y) x##y
// #define DEF_PATH PASTE(/etc/nice/ips,/)
// 
// #define DEF_PATH_VERSION DEF_PATH

// #define VERSION(ONE,TWO,THREE) ONE ## TWO

// wrap x with quotation marks.
#define wrapme(x) #x

int
main()
{

//     printf ("path : %s\n", DEF_PATH_VERSION);

    printf(wrapme(yoni_cohen));

    return 0;


}

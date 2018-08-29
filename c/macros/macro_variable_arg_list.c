#include <stdio.h>

// wrap x with quotation marks.
#define wrapme(x) #x

#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(__VA_ARGS__, 5,4,3,2,1)
#define VA_NUM_ARGS_IMPL(_1,_2,_3,_4,_5,N,...) N

#define LAST_ARG(...) do {     \
    printf("%s %d\n", __VA_ARGS__, VA_NUM_ARGS(__VA_ARGS__)); \
}while(0)


int
main()
{ 

//     LAST_ARG(yoni, dvori, maya, daniel, david, michal, elinor);
    LAST_ARG(yoni, dvori, maya, daniel);
    return 0;
}

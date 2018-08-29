
#include <stdio.h>
#include <string.h>

#define ALIGN_MASK(bit)	    ((1 << bit) - 1)
#define ALIGN_TO_BIT(x,bit) ((x + ALIGN_MASK(bit)) & ~ALIGN_MASK(bit))


int str_2_enum(char *op);

int main()
{
//	int buf=0xc8a8a7ee, size=8193;
//	int aligned_buf, aligned_size;
//
//
//	aligned_buf = ALIGN_TO_BIT(buf, 5);
//
//	aligned_size =ALIGN_TO_BIT(size, 5);
//
//	printf("a_buf =0x%X, a_size=%d\n",aligned_buf, aligned_size);
	
	str_2_enum("invalidate");
	str_2_enum("flush");
	str_2_enum("stam");
}

int str_2_enum(char *op)
{
    enum ops_t{CACHE_INV, CACHE_FLUSH, CACHE_NONE};

	enum ops_t ops;
	

    if (strcmp(op, "invalidate") == 0){
        ops = CACHE_INV; 
    }
    else if (strcmp(op, "flush") == 0) {
        ops = CACHE_FLUSH;
    }
	else
		ops = CACHE_NONE;

	switch(ops){
		case CACHE_INV: 
			printf("ops = CACHE_INV\n"); 
			break;
        case CACHE_FLUSH:
			printf("ops = CACHE_FLUSH\n");
            break;
        default:
            printf("no such option %s\n",op);
            return -1;
	}

	return 0;
}


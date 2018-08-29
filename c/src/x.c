struct x_t{

    char a;
    char b;
    int c;

};// __attribute__((packed));

struct bits{
	unsigned char b0:1;
	unsigned char b1:1;
	unsigned char b2:1;
	unsigned char b3:1;
	unsigned char b4:1;
	unsigned char b5:1;
	unsigned char b6:1;
	unsigned char b7:1;
};


struct x_t  t;
struct bits b;

int
main (int argc, char *argv[])
{

	int* hex_num;
	
	b.b0 = 0;    
	b.b1 = 1;    
	b.b2 = 0;    
	b.b3 = 1;    
	b.b4 = 0;    
	b.b5 = 0;    
	b.b6 = 0;    
	b.b7 = 0;    

	hex_num = (int*)&b;
	
	printf("hex_num = %x\n",*hex_num);
	   
    printf("sizeof(t): %d, offset(b): %d, offset(c): %d\n",
	sizeof(t),
	&((struct x_t*)0)->b, &((struct x_t*)0)->c );

    return 0;
}

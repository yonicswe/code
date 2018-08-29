
#define __builtin_expect(x, expected_value) (x)
#define unlikely(x)     __builtin_expect(!!(x), 0)

int 
main (int argc, char *argv[])
{

    if (unlikely(1)) {
        printf("\nhello\n");
    }

    return 0;
}

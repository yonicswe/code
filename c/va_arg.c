#include <stdarg.h>
#include <stdio.h>

void
my_va_arg_print_func(char* f, ...)
{
    va_list val;
    va_start(val, f);
    vprintf(f, val);
    va_end(val); 
}


int 
main(void)
{
    my_va_arg_print_func("yoni %d %d\n", 1, 2);
    my_va_arg_print_func("yoni %d %d %d\n", 1, 2, 3);

    return 0; 
}

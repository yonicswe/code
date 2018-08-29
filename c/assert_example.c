
#include <assert.h>

void func2()
{
    assert(0);
}

void func1()
{
    func2();
}

int
main()
{
    func1();

    return 0;
}

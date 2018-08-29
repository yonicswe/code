void 
f(void)
{
    printf("hello\n");
}

int main (int argc, char *argv[])
{
    void (*funp)(void);

    funp=&f;

    funp();

    return 0;
}

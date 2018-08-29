

char global_buffer[] = "yoni cohen";


void f(char* b, char** p, int* r)
{
   *p = &b[3];
   *r = 2;

}

typedef void (fun_type)(char* , char** , int* );

fun_type* func_arr[] = 
{
   f
};


int
main(void)
{

   char *b;
   char *p;
   int r =3;

   b = global_buffer;


   //f(b,&p, &r);
   func_arr[0](b,&p, &r);

   return 0;
   
}

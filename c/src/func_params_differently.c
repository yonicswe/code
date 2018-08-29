
void
func_test (name,number),char *,int 
{
	printf("name(\"%s\")\nnumber(%d)\n",name,number);
}

int
main(void)
{
	char *yoni_name = "yoni cohen";
	int  yoni_number = 12;
	func_test(yoni_name,yoni_number);
}

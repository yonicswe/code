#include <stdio.h>


#define YONI_LOG(fmt,args...) \
	printf(fmt, ##args);


int
main(int argc,char* argv[])
{
	unsigned long ul1 = 122;
	YONI_LOG("%s():got %u\n",__FUNCTION__,12);
	YONI_LOG("got nothing\n");
	YONI_LOG("got nothing\n");
	YONI_LOG("got n\\a \n",ul1);
	return 0;
}

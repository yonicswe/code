#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum rxe_counter {
	RXE_COUNTER_1,
	RXE_COUNTER_2,
	RXE_NUM_OF_COUNTERS
};

char* rxe_counter_name[RXE_NUM_OF_COUNTERS] = {
	"RXE_COUNTER_1",
	"RXE_COUNTER_2", 
};

size_t rxe_statistics_counters[RXE_NUM_OF_COUNTERS] = {0};

#define RXE_COUNTER_INC(cnt) \
	do {\
		rxe_statistics_counters[cnt]++;	\
	}while(0)



#define RXE_COUNTER_FORMAT_SIZE 80
#define RXE_COUNTER_FORMAT(cnt) \
	"%s = %zd", rxe_counter_name[cnt], rxe_statistics_counters[cnt]
#define RXE_COUNTER_FORMAT_TO_BUFFER(cnt, buf, buf_size) \
	do { snprintf(buf, RXE_COUNTER_FORMAT_SIZE, RXE_COUNTER_FORMAT(cnt)); \
	} while (0)

	

void rxe_dump_statistics_counters()
{
	int i;
	char buf[80];	

	memset(buf, 0, 80);
	
	for (i=0; i<RXE_NUM_OF_COUNTERS; i++)
	{
		RXE_COUNTER_FORMAT_TO_BUFFER(i, buf, 80);
		printf("%s\n", buf);
	}
}


int main()
{
	RXE_COUNTER_INC(RXE_COUNTER_1);
	RXE_COUNTER_INC(RXE_COUNTER_1);
	RXE_COUNTER_INC(RXE_COUNTER_1);
	RXE_COUNTER_INC(RXE_COUNTER_1);
	RXE_COUNTER_INC(RXE_COUNTER_1);
	RXE_COUNTER_INC(RXE_COUNTER_2);
	RXE_COUNTER_INC(RXE_COUNTER_2);
	RXE_COUNTER_INC(RXE_COUNTER_2);
	RXE_COUNTER_INC(RXE_COUNTER_2);
	RXE_COUNTER_INC(RXE_COUNTER_2);
	RXE_COUNTER_INC(RXE_COUNTER_2);
	RXE_COUNTER_INC(RXE_COUNTER_2);
	RXE_COUNTER_INC(RXE_COUNTER_2);
	RXE_COUNTER_INC(RXE_COUNTER_2);
	RXE_COUNTER_INC(RXE_COUNTER_2);

	rxe_dump_statistics_counters();
	
	return 0;
}

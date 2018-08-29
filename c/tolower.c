
#include <stdio.h>
#include <ctype.h>

#define counter_stringify(c) #c

enum counters{
	CNT_RECEIVED_PACKETS,
	CNT_SENT_PACKETS,
	CNT_COMPLETED_PACKETS,
	CNT_NUM_OF_COUNTERS,
};

char *counter_name[CNT_NUM_OF_COUNTERS] = {
	counter_stringify(CNT_RECEIVED_PACKETS),
	counter_stringify(CNT_SENT_PACKETS),
	counter_stringify(CNT_COMPLETED_PACKETS),
};

int main()
{
	char *c;
	int i;
	for (i=0; i<CNT_NUM_OF_COUNTERS; i++)	
	{
		c = counter_name[i];
		for (; *c; c++ ) *c = tolower(*c);
		printf("%s\n", counter_name[i]);
	}

	return 0;
}

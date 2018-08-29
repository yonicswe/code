#include <stdio.h>
#include <string.h>

#define MOSHE 3
#define MOSHE 3

struct node_t {
	int x;
};

struct my_st{
	int x;
	int y;
	struct node_t a[];
};

struct my_st a = {
	12,
	15
};


struct msg{
	union {
		struct {

			struct fields{
				int application;
				int channel;
			}fields;

			char data[sizeof (struct fields) ];

		}log;

		struct {
			int number;
		}event;
	}as;
};


void
fill_structure(struct my_st* m)
{
	int i;
	char* src;
	char* dst;
	struct my_st* p=&a;


	struct msg msg_t = {};

	msg_t.as.log.fields.application = 1;


	src = (char*)p;
	dst = (char*)m;

	printf("copy : ");
	for (i=0; i<sizeof(struct my_st); i++){
		printf("[%d]=%02x ", i, src[i]);
		dst[i] = src[i];
	}
	printf("\n");

	//memcpy(m, &a, sizeof(struct my_st));
}

void
f1(int i)
{
	if (i == 1)
		goto exit_f;

	printf("got !=1\n");
	return;
exit_f:
	printf("%s: got 1\n", __func__);
}

void
f2(int i)
{
	if (i == 1)
		goto exit_f;

	printf("got !=1\n");
	return;
exit_f:
	printf("%s: got 1\n", __func__);
}



int
main(void)
{

	struct my_st y = {

	.a = (struct node_t a []){.x =1, .y=2};
	};

#if 1
	struct my_st m;

	fill_structure(&m);

	printf("x = %d, y = %d\n", m.x, m.y);
#endif
	f1(1);
	f2(1);

	return 0;
}

int globalAfterMain;

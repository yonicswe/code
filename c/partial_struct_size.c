#include <stdio.h>

struct HalMsgHeader{
	int source;
	int type;
	int seqId;
};

#define HAL_MSG_MAX_SIZE 256
#define HAL_MSG_HEADER_SIZE (sizeof(struct HalMsgHeader))
#define HALMSG_DATA_SIZE (HAL_MSG_MAX_SIZE - HAL_MSG_HEADER_SIZE)
#define HALMSG_DATA_LOG_BUFFER_SIZE HALMSG_DATA_SIZE - sizeof(struct LogFields)

struct LogFields{
	int application;
	int channel;
	int severity;
	int size;
}LogFields;

struct HalMsgData{
	union {
		union {

			struct {
				struct LogFields fields;
				char buffer[HALMSG_DATA_LOG_BUFFER_SIZE];
			}log;

			struct event{
				int eventType;
				int arg;
			}event;

		}type;

		char buffer[HALMSG_DATA_SIZE];

	}as;
}HalMsgData;

int
main(void)
{
	printf("fields: %d\n", sizeof(struct LogFields));
	printf("header: %d\n", sizeof(struct HalMsgHeader));
	printf("data: %d\n", sizeof(struct HalMsgData));
	return 0;
}

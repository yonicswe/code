#include <stdlib.h>
#include <string.h>
#include <stdio.h>


struct buffer_t{
    int size;
    char data[0];
};

#define MAX_DATA_SIZE 30
#define MAX_BUFFER_SIZE (sizeof(struct buffer_t) + MAX_DATA_SIZE)

// char data[] = "the name of the game is playing by the rules";
// char *other_data  = "the name of the game is playing by the rules";

int
main(void)
{
    int data_size;
//     int buffer_size = MAX_BUFFER_SIZE;
    char *data = malloc(200);


    struct buffer_t *b1 = (struct buffer_t*)malloc(MAX_BUFFER_SIZE);

    data_size = strlen(data);

    b1->size = (data_size < MAX_BUFFER_SIZE)? data_size: MAX_BUFFER_SIZE;

//      memcpy(b1->data, data, b1->size);
     memcpy(b1->data, data, 200);

    free(b1);

    return 0;
    

}

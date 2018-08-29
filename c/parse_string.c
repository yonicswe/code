
#define CMD_STR_LEN 20
#define MAX_DISPATCH_TABLE_LEN
#define MAX_MSG_SIZE 50

struct dispatch_table {
    char cmd[CMD_STR_LEN];
    void (*handler)(char* cmd, char* body); 
};

char msg[MAX_MSG_SIZE];

void
msg_parse(struct dispatch_table* t, int table_len)
{
    char *cmd, *body;
    char* ch;
    int len=0;

    while ((ch = getchar() ) != EOF  && len<MAX_MSG_SIZE){


    }



}


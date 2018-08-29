
struct handler_table_t{
   char* command;
   void (*handler)(char* cmd, char* body);
};

void
yoni(char*, char*);
void
dvori(char*, char*);
void
mayush(char*, char*);

struct handler_table_t ht[] = {
   {"yoni" , yoni},
   {"dvori" , dvori},
   {"mayush" , mayush}
};

void
yoni(char* cmd, char* body)
{
   printf("%s: cmd: %s, body: %s\n", __func__, cmd, body); 
}
void
dvori(char* cmd, char* body)
{
   printf("%s: cmd: %s, body: %s\n", __func__, cmd, body); 
}

void
mayush(char* cmd, char* body)
{
   printf("%s: cmd: %s, body: %s\n", __func__, cmd, body); 
}

void
parse_input(struct handler_table_t *ht)
{


}

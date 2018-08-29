


enum iser_conn_state {
	SLEEPING,
	WAKING,
	AWAKE,
	NUM_OF_STATES
};


char *iser_conn_state_name[NUM_OF_STATES+1] = {
	"SLEEPING",
	"WAKING",
	"AWAKE",
	"ILLEAGEL"
};

char*
get_conn_state (enum iser_conn_state conn_s)
{
	return iser_conn_state_name[(conn_s>NUM_OF_STATES || conn_s < 0) ? NUM_OF_STATES : conn_s];
}

//==================================================================================

int
main(int argc, char* argv)
{

	enum iser_conn_state conn_s;
	conn_s = SLEEPING;
	printf("conn_state = %s\n",get_conn_state(conn_s) );
	conn_s = WAKING;
	printf("conn_state = %s\n",get_conn_state(conn_s) );
	conn_s = AWAKE;
	printf("conn_state = %s\n",get_conn_state(conn_s) );
	conn_s = 34;
	printf("conn_state = %s\n",get_conn_state(conn_s) );
	conn_s = -1;
	printf("conn_state = %s\n",get_conn_state(conn_s) );

	return 0;

	
}

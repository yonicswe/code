union wait {
	int w_status;
	struct {
		unsigned int:16; //spare
		unsigned int __w_retcode:8;
		unsigned int __w_coredump:1;
		unsigned int __w_termsig:7;
	} __wait_terminated;

	 struct {
		unsigned int:16;
		unsigned int __w_stopsig:8; /* Stopping signal.	*/
		unsigned int __w_stopval:8; /* W_STOPPED if stopped.	*/
	} __wait_stopped;
};

int
main(void)
{

	union wait w1;

	w1.__wait_terminated.__w_retcode =1;

	return 0;

}

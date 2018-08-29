#include <syslog.h>
#include <stdio.h>

/*
       void openlog(const char *ident, int option, int facility);
       void syslog(int priority, const char *format, ...);
       void closelog(void);
*/

int
main(int argc, char* argv[])
{
	openlog("rc.local", LOG_NOWAIT, LOG_USER);

	printf("logging : %s", argv[1]);
	syslog(LOG_INFO, "%s", argv[1]);

	closelog();

	return 0;
}

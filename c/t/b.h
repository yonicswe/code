
char level_str[] = "FATAL";

#define DBGI(__level, __fmt, __args...) \
	do  { printf("[%s]: (%s): " __fmt, level_str, __FUNCTION__, ##__args); \
	} while (0)

#define DBGI_ERR(__fmt, __args...) \
	do  { DBGI(DBG_ERROR, __fmt, ##__args);	}while(0)


#define _DBGI_ASSERT(__fmt, __args...) \
   do  { DBGI(DBG_FATAL, "ASSERT, " __fmt, ##__args); }while(0)


#define DBGI_ASSERT(e, rc) \
    if (!(e)) { \
        _DBGI_ASSERT("line: %d", __LINE__ ); \
        return rc; \
    }

#define DBGI_ASSERT_VOID(e) \
    if (!(e)) { \
        _DBGI_ASSERT("(expression %s)", #e); \
        return; \
    }

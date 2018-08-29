
#ifndef _PARSE_SRI_H_
#define _PARSE_SRI_H_

#include <string>
using namespace std;

#define LINE_MAX_SIZE 1024

enum protocol_name{
	FRAME=0,
	SCTP,
	SCCP,
	TCAP,
	GSM_MAP,
	PROTO_UNKNOWN 
};

enum key_name{
	NAME =0,
	SHOW,
	VALUE	
};


struct key_val{
	enum key_name key;
	string val;
};

#endif // _PARSE_SRI_H_

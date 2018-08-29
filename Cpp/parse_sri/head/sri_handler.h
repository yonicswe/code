 
#ifndef _SRI_HANDLER_H_
#define _SRI_HANDLER_H_

// forward declaration
class sccp_t;
class tcap_t;
class gsm_map_t;
class sri_t;
class Hash;


class sccp_t{
	public:
		unsigned long long sccp_oa;		
		unsigned long long sccp_da;		

		// 0: sccp section not complete
		// 1: sccp has sccp_da only
		// 2: sccp has sccp_oa and sccp_da and is compete.
		int complete;

		sccp_t():
			sccp_oa(0),
			sccp_da(0),
			complete(0){}; 

		void reset(void);
};

class tcap_t{
	public:
		unsigned long long src_tid;
		unsigned long long dst_tid; 

		//  1: request 
		//  0: response.
		// -1: not set.
		int begin_not_end; 

		// 0: tcap section not complete
		// 1: tcap section has resolved request or response.
		// 2: tcap section has tcap.tid and complete
		int complete;

		tcap_t():
			src_tid(0),
			dst_tid(0),
			begin_not_end(-1),
			complete(0) {}; 

		void reset();
};

class gsm_map_t{
	public:
		unsigned long type;
		unsigned long long msisdn;
		unsigned long long imsi;

		// 0: gsm section has no data yet
		// 1: gsm section has type 
		// 2: gsm section has msisdn / or imsi ( and is completed ) 
		int complete;

		// constructor
		gsm_map_t():
			type(0),
			msisdn(0),
			imsi(0),
			complete(0){};

		void reset(void);
};

class sri_t
{
	public:
		unsigned long frame_number;
		unsigned long response_frame_number;
		sccp_t	  sccp;
		tcap_t	  tcap;
		gsm_map_t gsm_map; 

		sri_t(void):
			frame_number(0),
			response_frame_number(0),
			gsm_map(),
			tcap(),
			sccp() {};

		sri_t(unsigned long fn):
			frame_number(fn),
			response_frame_number(0),
			gsm_map(),
			tcap(),
			sccp() {};

		void reset(void);
		void handle_sri_request(Hash* sri_hash);
		void handle_sri_response(Hash* sri_hash); 
		void show(void);
};

#endif // _SRI_HANDLER_H_

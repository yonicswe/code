

class sccp_t{
	public:
		unsigned long long sccp_oa;		
		unsigned long long sccp_da;		

		sccp_t():sccp_oa(0),sccp_da(0){}; 
};

class tcap_t{
	public:
		unsigned long long src_tid;
		unsigned long long dst_tid; 

		int begin_not_end; 

		tcap_t():src_tid(0),dst_tid(0),begin_not_end(-1){}; 
};

class gsm_map_t{
	public:
		unsigned long type;
		unsigned long msisdn;
		unsigned long imsi;

		gsm_map_t():type(0),msisdn(0),imsi(0){};
};

class sri_t
{
	public:
		unsigned long frame_number;
		sccp_t	  sccp;
		tcap_t	  tcap;
		gsm_map_t gsm; 

		sri_t(unsigned long fn):
			frame_number(fn),
			gsm(),
			tcap(),
			sccp() {};

};


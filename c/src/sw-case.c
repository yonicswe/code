

enum {
			VAPI_ATOMIC_CAP_NONE,
			VAPI_ATOMIC_CAP_HCA,
			VAPI_ATOMIC_CAP_GLOB
};

#define CASE_SETSTR(e)  case e: s = #e; break;

int 
main(int argc, char* argv[])
{
	  const char*  s = UnKnown;
	    switch (e) {
			CASE_SETSTR(VAPI_ATOMIC_CAP_NONE)
			CASE_SETSTR(VAPI_ATOMIC_CAP_HCA)
			CASE_SETSTR(VAPI_ATOMIC_CAP_GLOB)
			default: ;
		}
		return s;
}


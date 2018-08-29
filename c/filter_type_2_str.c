#include <stdio.h>
#include <stdlib.h>

#define FILTERTYPE_MACFILTER			0x00000100
#define FILTERTYPE_IPFILTER			0x00000200
#define FILTERTYPE_IPV6FILTER			0x00000300
#define FILTERTYPE_RADUSERFILTER		0x00000400
#define FILTERTYPE_RADCSIDFILTER		0x00000500
#define FILTERTYPE_DHCPHOSTFILTER	0x00000600
#define FILTERTYPE_DHCPMACFILTER		0x00000700
#define FILTERTYPE_DHCPATMFILTER		0x00000800
#define FILTERTYPE_PPPUSERFILTER		0x00000900

#define filter_type_to_str(filtertype, buffer) \
	do {                                        \
		switch (filtertype)                      \
      {                                        \
         case FILTERTYPE_MACFILTER:            \
            buffer="Mac";                      \
            break;                             \
         case FILTERTYPE_IPFILTER:             \
            buffer="IPv4";                     \
            break;                             \
         case FILTERTYPE_IPV6FILTER:           \
            buffer="IPv6";                     \
            break;                             \
         case FILTERTYPE_RADUSERFILTER:        \
            buffer="Radius";                   \
            break;                             \
         default:                              \
            buffer="Uknown";                   \
		}                                        \
	} while (0)



int
main(int c, char* v[])
{
   char *p;

   unsigned long type;
   
   type = strtoul(v[1], NULL, 16);

   printf("type : %x : ", type);

   filter_type_to_str(type, p);

   printf("%s\n", p);


   return 0;
}

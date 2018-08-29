
#include <stdlib.h>

/***********************************************************************
 * Purpose: Service routines to convert hex string to binary.
 ***********************************************************************/
// b is assumed to be 0-9 a-f A-F
int hex_val_of(char b)
{
	if (b > 0x60)	     // upper case
		b -= 0x50;   // reduce to 0-f range
	else		     // lower case
		b -= 0x30;   // reduce to 0-f range

	if (b>9)	     // complete reduction to value
		b-=7;

	return b;

}

unsigned int
ConvertHexStringToBinary(char *hex,char *str)
{
	int i,len;
	char msb,lsb;

	len = strlen(hex);

	for (i = 1; i<len/2; i++) {
		msb = hex_val_of(hex[i*2]);
		lsb = hex_val_of(hex[i*2+1]);

		str[i-1]= msb*16 + lsb;
	}
	str[i-1] = '\0';

	return(i-1);
}


unsigned int
ConvertHexOR64BaseStringToBinary(char* ReceivedValue,char* c_r)
{
	if (strncmp("0x",ReceivedValue,2)==0 || strncmp("0X",ReceivedValue,2)==0) {
		return ConvertHexStringToBinary(ReceivedValue,c_r);
	}
//        else if (strncmp("0b",ReceivedValue,2)==0 || strncmp("0B",ReceivedValue,2)==0) {
//                return Convert64BaseStringToBinary(ReceivedValue,c_r);
//        }
	else {
		// do nothing
		return 0;
	}
}

/*!
  @description
	convert from iscsi key type hex constant to a string.
	e.g. hexconst_to_str("0x796f6e69")  => str="yoni" 
  @returns
	len of str
*/
unsigned long
hexconst_to_str(char* hexconst,//!< IN - the value of a hex constant key type.
		 char** str)	//!< OUT - converted to string.
{      
	long len;
	long i;
	long j;
	char* p;
	char* p_str;
	char hex_num[3]={0};
	int str_len;
	
	if (hexconst == NULL) {
		//VD_LOG(VDLOG_ERROR,"%s: NULL buffer\n",__func__);
		return 0;
	}

	if (strncmp("0x",hexconst,2)!=0 && strncmp("0X",hexconst,2)!=0){
		//VD_LOG(VDLOG_ERROR,"%s: not a hex constant\n",__func__);
		return 0;
	}

	if (len < 4) {
		//VD_LOG(VDLOG_ERROR,"%s: not a hex constant\n",__func__);
		return 0;
	}
	
	len=strlen(hexconst);
	str_len = ((len - 2)/2)+1;

	p_str = malloc(str_len * sizeof(char));
	memset(p_str, 0, str_len);

	p=&hexconst[2];
	for (i=2,j=0; i<len && j<str_len; i+=2, j++, p+=2) {
		memcpy(hex_num, p, 2);
		p_str[j] = strtol(hex_num, NULL, 16);
	}

	*str = p_str;
	return str_len-1;
}


/*!
  @description
	convert a string to value of a hex constant key type.
	e.g. str_to_hexconst("yoni") => hexconst="0x796f6e69" 
  @returns
	len of hexconst
*/
unsigned long
str_to_hexconst(char* str,      //!< IN - the value of a hex constant key type.
		char* hexconst)	 //!< OUT - converted to string.
{
	long n=0;
	long i;
	long len;

	if (hexconst == NULL || str == NULL) {
		//VD_LOG(VDLOG_ERROR,"%s: NULL buffer\n",__func__);
		return 0;
	}
	
	len = strlen(str);
	
	n += sprintf(hexconst, "0x");
       for (i=0; i<len ; i++) {
		n += sprintf(hexconst + n, "%x",str[i]);
	}

	return n;
}

int 
main (int argc, char *argv[])
{
	static char str[100]={0};
	char* new_str;
	static char username1[100]="0x796f6e6963";
	static char username2[100]="yonic";
	static char username3[100]="0x64766f7261";
	int len;

	len = hexconst_to_str(username1, &new_str);
       printf("\"%s\"(%d) = hexconst_to_str(\"%s\")\n",new_str, len, username1);
	free(new_str);

//        memset(str, 0, sizeof(str));
//        str_to_hexconst(username2, str);
//        printf("\"%s\" =str_to_hexconst(\"%s\")\n",str, username2);
	return 0;
}

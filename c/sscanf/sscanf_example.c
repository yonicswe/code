
// sscanf reads a string from user argv[1]
// and parses it according to the format surrounded with apostrophes
// sscanf return value is the number of items parsed
// in this case 3 
// 

#include <string.h>
#include <errno.h>
#include<stdio.h>
int main(int argc, char* argv[])
{
    int r;
    int reasonPos;
    unsigned int httpVersionMajor;
    unsigned int httpVersionMinor;
    unsigned int httpResponseCode;
    r = sscanf(argv[1], "HTTP/%d.%d %u %u%n", &httpVersionMajor, &httpVersionMinor, &httpResponseCode, &reasonPos);
    if (r != 3)
        printf("read only %d items %s\n", r, strerror(errno));

    return 0;
}

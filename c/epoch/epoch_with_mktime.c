#include <stdio.h>
#include <time.h>

extern long timezone;
extern int daylight;
extern char *tzname[2];
 
void
convert_to_epoch (void) 
{
    struct tm t;
    time_t t_of_day;
     
    t.tm_year = 2013 - 1900;
    t.tm_mon = 4; // Month, 0 - jan
    t.tm_mday = 14; // Day of the month
    t.tm_hour = 7;
    t.tm_min = 39;
    t.tm_sec = 22;
    t.tm_isdst = -1; // Is DST on? 1 = yes, 0 = no, -1 = unknown
//     t.tm_gmtoff = 8*3600; // i dont know why this is not working
    t_of_day = mktime(&t);

    // decrease the GMT
    t_of_day -= 8*3600;
     
    printf("seconds since the Epoch: %ld\n", (long) t_of_day);

    t_of_day = timegm(&t);
    t_of_day -= 8*3600;
    printf("seconds since the Epoch: %ld\n", (long) t_of_day);

}

void 
show_time_zone (void)
{

    tzset();
    printf("time zone: %u\n", timezone);


}

int 
main(void)
{
    convert_to_epoch();
    show_time_zone();
    return 0;
}

// int main(void)
// {
//     time_t now;
//     struct tm ts;
//     char buf[80];
//      
//     // Get current time
//     time(&now);
//      
//     // Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
//     ts = *localtime(&now);
//     strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
//     printf("%s\n", buf);
//     return 0;
// }

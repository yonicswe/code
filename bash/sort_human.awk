#!/bin/awk -f

BEGIN{
    k=1; m=1 ; g=1; 
}

{
    if (match($1,".*K"))
    {  
        # print "got "$0;
        # m = sprintf (m " %s", $0);
        kk[k]=$0; 
        k++;
    }
    else if (match($1,".*M"))
    {
        mm[m]=$0; 
        m++;
    } 
    else if (match($1,".*G"))
    {
        gg[g]=$0; 
        g++;
    }
} 

END{
    for (i=1; i<k ; i++) 
        print kk[i];
    for (i=1; i<m ; i++) 
        print mm[i];
    for (i=1; i<g ; i++) 
        print gg[i];
}

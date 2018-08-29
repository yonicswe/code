#!/bin/bash

foo2 () 
{
    caller 3
    echo "Entered $FUNCNAME";
}

foo () 
{
    caller 2
    echo "Entered $FUNCNAME";

    foo2        
}



main () 
{
    caller 1
    echo "Entered $FUNCNAME";
    foo
}

main "$@"

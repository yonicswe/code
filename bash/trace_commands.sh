#!/bin/bash

trace_command () 
{
    echo $1
    shift 1
    eval $*
}

trace_command "LS" ls -l

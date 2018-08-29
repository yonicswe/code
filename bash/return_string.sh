#!/bin/bash

# The "correct" way to return a string from a function 
# is with command substitution. In the event that the function also needs to 
# output to console, create a temporary fd 
# in the beginning of the function and redirect to console. 
# Close the temporary fd before returning your string.

returnString() {

    # create a temporary fd (3) and redirect it to console 
    exec 3>&1 >/dev/tty
    local s=$1
    s=${s:="some default string"}
    echo "writing directly to console"

    # close temporary fd (3)         
    exec >&3-

    # use echo to return the string 
    echo "$s"
}

my_string=$(returnString "$*")
echo "my_string:  [$my_string]"

# executing script with no params produces...  
# ./func_return_test.sh
# writing directly to console
# my_string:  [some default string]

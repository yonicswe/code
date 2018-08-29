#!/bin/bash

#
# the data file from which this function reads the fields 
# should looks like so: 
#  #<field_1>:<value>
#  #<field_2>:<value>
#
#  #<field_n>:<value>
#

function getfield() {
	declare field=$1
	declare file=$2

	grep -i '^.*#.*'"${field}:" ${file} | sed 's;^.*:[  ]*;;'
}


# main

getfield $1 $2

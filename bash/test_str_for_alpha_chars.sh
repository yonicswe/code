#
# there are several ways to do this 
#

#
# Method 1 
#
# replace all non-alpha characters with nothing
echo 1234  | sed 's/[^[:alpha:]]//g'

# now check if the returned string is empty, if so then there were only numbers 
# the result string is empty since sed replaced all alpha digits with nothing,
# if there were other characters other than alpha they would not be replaced, hence the 
# result string would not be empty.


#
# Method 2 
#
# grep for the chars a-z and A-Z
echo 1234 | grep [a-z,A-Z]

# again here, if the string is empty then there were only numbers.
# the result string is empty since grep did not find any of the matching a-z or A-Z

# this will check if user input comprised only from numbers.
if ! [[ "$a" =~ ^[0-9]+$ ]] ; then echo "$a - not numeric" ; else echo "$a numeric" ; fi

#!/bin/bash


im_a_global=



f () 
{

   im_a_global="yonicohen"
   echo yes
}

#
# Main
#
x=$(f)

#  since u called f in a sub shell the setting of the global will not affect 
#  this shell so here $im_a_global will have no value:
echo "im_a_global = $im_a_global, x=$x"

# but if you run f () in this shell then the setting of the global will have effect 
# and thus in the follownig print im_a_global will have the value "yonicohen"
#
f
echo "im_a_global = $im_a_global, x=$x"



deref_var_name () { 
   if [ -n "$1" ] ; then 
      echo "value of [${1}] is [${!1}]"
   else
      echo "NUll param"
   fi
}


yoni=cohen
deref_var_name yoni cohen

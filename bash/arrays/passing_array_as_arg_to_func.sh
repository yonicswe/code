
foo ()
{ 
    declare -a x=("${!1}") ; 
    echo ${x[*]} ; 
}

a=(1 2 3 4)
foo a[@]    

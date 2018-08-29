#!/bin/bash

g_proj_dir=${HOME}/share/tasks

_yoni()
{
    local cmd=$1 cur=$2 pre=$3;
    local _cur compreply

    _cur=$g_proj_dir/$cur
    compreply=( $( compgen -d "$_cur" ) )
    COMPREPLY=( ${compreply[@]#$g_proj_dir/} )
    if [[ ${#COMPREPLY[@]} -eq 1 ]]; then
        COMPREPLY[0]=${COMPREPLY[0]}/
    fi
}

yoni()
{
    cd $g_proj_dir/$1
}

complete -F _yoni -o nospace yoni

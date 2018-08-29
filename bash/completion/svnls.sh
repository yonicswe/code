_SvnLs ()   #  By convention, the function name
{                 #+ starts with an underscore.
#     set -x
    local cur
    # Pointer to current completion word.
    # By convention, it's named "cur" but this isn't strictly necessary.

    COMPREPLY=()   # Array variable storing the possible completions.
    cur=${COMP_WORDS[COMP_CWORD]};

#     if [ -z "$cur" ] ; then 
#         cur=zz;
#     fi

    case "$cur" in
        -*)
            COMPREPLY=$( $(svn ls svn://snt.nice.com/NiceTrackMC) );;
    COMPREPLY=( $( compgen -W '-a -d -f -l -t -h --aoption --debug \
#                     --file --log --test --help --' -- $cur ) );;
    #   Generate the completion matches and load them into $COMPREPLY array.
    #   xx) May add more cases here.
    #   yy)
#         zz)
#             COMPREPLY=$( $( svn ls svn://snt.nice.com/NiceTrackMC ) );;

    esac
#         set +x
        return 0
}

complete -F _SvnLs -o filenames svnls

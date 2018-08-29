#!/bin/bash





# trap handle_SIGHUP          SIGHUP        
# trap handle_SIGTRAP         SIGTRAP    
# trap handle_SIGKILL         SIGKILL 
# trap handle_SIGPIPE         SIGPIPE    
# trap handle_SIGCONT         SIGCONT    
# trap handle_SIGTTOU         SIGTTOU    
# trap handle_SIGVTALRM       SIGVTALRM  
# trap handle_SIGPWR          SIGPWR     
# trap handle_SIGRTMIN+2      SIGRTMIN+2 
# trap handle_SIGRTMIN+6      SIGRTMIN+6 
# trap handle_SIGRTMIN+10     SIGRTMIN+10
# trap handle_SIGRTMIN+14     SIGRTMIN+14
# trap handle_SIGRTMAX-12     SIGRTMAX-12
# trap handle_SIGRTMAX-8      SIGRTMAX-8 
# trap handle_SIGRTMAX-4      SIGRTMAX-4 
# trap handle_SIGRTMAX        SIGRTMAX
trap handle_SIGINT          SIGINT     
# trap handle_SIGABRT         SIGABRT    
# trap handle_SIGUSR1         SIGUSR1    
# trap handle_SIGALRM         SIGALRM    
# trap handle_SIGSTOP         SIGSTOP    
# trap handle_SIGURG          SIGURG     
# trap handle_SIGPROF         SIGPROF    
# trap handle_SIGSYS          SIGSYS     
# trap handle_SIGRTMIN+3      SIGRTMIN+3 
# trap handle_SIGRTMIN+7      SIGRTMIN+7 
# trap handle_SIGRTMIN+11     SIGRTMIN+11
# trap handle_SIGRTMIN+15     SIGRTMIN+15
# trap handle_SIGRTMAX-11     SIGRTMAX-11
# trap handle_SIGRTMAX-7      SIGRTMAX-7 
# trap handle_SIGRTMAX-3      SIGRTMAX-3 
# trap handle_SIGQUIT         SIGQUIT    
# trap handle_SIGBUS          SIGBUS     
# trap handle_SIGSEGV         SIGSEGV    
# trap handle_SIGTERM         SIGTERM    
# trap handle_SIGTSTP         SIGTSTP    
# trap handle_SIGXCPU         SIGXCPU    
# trap handle_SIGWINCH        SIGWINCH   
# trap handle_SIGRTMIN        SIGRTMIN   
# trap handle_SIGRTMIN+4      SIGRTMIN+4 
# trap handle_SIGRTMIN+8      SIGRTMIN+8 
# trap handle_SIGRTMIN+12     SIGRTMIN+12
# trap handle_SIGRTMAX-14     SIGRTMAX-14
# trap handle_SIGRTMAX-10     SIGRTMAX-10
# trap handle_SIGRTMAX-6      SIGRTMAX-6 
# trap handle_SIGRTMAX-2      SIGRTMAX-2 
# trap handle_SIGILL          SIGILL
# trap handle_SIGFPE          SIGFPE
# trap handle_SIGUSR2         SIGUSR2
# trap handle_SIGCHLD         SIGCHLD
# trap handle_SIGTTIN         SIGTTIN
# trap handle_SIGXFSZ         SIGXFSZ
# trap handle_SIGIO           SIGIO
# trap handle_SIGRTMIN+1      SIGRTMIN+1
# trap handle_SIGRTMIN+5      SIGRTMIN+5
# trap handle_SIGRTMIN+9      SIGRTMIN+9
# trap handle_SIGRTMIN+13     SIGRTMIN+13
# trap handle_SIGRTMAX-13     SIGRTMAX-13
# trap handle_SIGRTMAX-9      SIGRTMAX-9
# trap handle_SIGRTMAX-5      SIGRTMAX-5
# trap handle_SIGRTMAX-1      SIGRTMAX-1


# function handle_SIGHUP       () { echo SIGHUP      ; exit ; }
# function handle_SIGTRAP      () { echo SIGTRAP     ; exit ; }
# function handle_SIGKILL      () { echo SIGKILL     ; exit ; }
# function handle_SIGPIPE      () { echo SIGPIPE     ; exit ; }
# function handle_SIGCONT      () { echo SIGCONT     ; exit ; }
# function handle_SIGTTOU      () { echo SIGTTOU     ; exit ; }
# function handle_SIGVTALRM    () { echo SIGVTALRM   ; exit ; }
# function handle_SIGPWR       () { echo SIGPWR      ; exit ; }
# function handle_SIGRTMIN+2   () { echo SIGRTMIN+2  ; exit ; }
# function handle_SIGRTMIN+6   () { echo SIGRTMIN+6  ; exit ; }
# function handle_SIGRTMIN+10  () { echo SIGRTMIN+10 ; exit ; }
# function handle_SIGRTMIN+14  () { echo SIGRTMIN+14 ; exit ; }
# function handle_SIGRTMAX-12  () { echo SIGRTMAX-12 ; exit ; }
# function handle_SIGRTMAX-8   () { echo SIGRTMAX-8  ; exit ; }
# function handle_SIGRTMAX-4   () { echo SIGRTMAX-4  ; exit ; }
# function handle_SIGRTMAX     () { echo SIGRTMAX    ; exit ; }
function handle_SIGINT       () { echo -e "\nSIGINT ($1)" ; exit ; }
# function handle_SIGABRT      () { echo SIGABRT     ; exit ; }
# function handle_SIGUSR1      () { echo SIGUSR1     ; exit ; }
# function handle_SIGALRM      () { echo SIGALRM     ; exit ; }
# function handle_SIGSTOP      () { echo SIGSTOP     ; exit ; }
# function handle_SIGURG       () { echo SIGURG      ; exit ; }
# function handle_SIGPROF      () { echo SIGPROF     ; exit ; }
# function handle_SIGSYS       () { echo SIGSYS      ; exit ; }
# function handle_SIGRTMIN+3   () { echo SIGRTMIN+3  ; exit ; }
# function handle_SIGRTMIN+7   () { echo SIGRTMIN+7  ; exit ; }
# function handle_SIGRTMIN+11  () { echo SIGRTMIN+11 ; exit ; }
# function handle_SIGRTMIN+15  () { echo SIGRTMIN+15 ; exit ; }
# function handle_SIGRTMAX-11  () { echo SIGRTMAX-11 ; exit ; }
# function handle_SIGRTMAX-7   () { echo SIGRTMAX-7  ; exit ; }
# function handle_SIGRTMAX-3   () { echo SIGRTMAX-3  ; exit ; }
# function handle_SIGQUIT      () { echo SIGQUIT     ; exit ; }
# function handle_SIGBUS       () { echo SIGBUS      ; exit ; }
# function handle_SIGSEGV      () { echo SIGSEGV     ; exit ; }
# function handle_SIGTERM      () { echo SIGTERM     ; exit ; }
# function handle_SIGTSTP      () { echo SIGTSTP     ; exit ; }
# function handle_SIGXCPU      () { echo SIGXCPU     ; exit ; }
# function handle_SIGWINCH     () { echo SIGWINCH    ; exit ; }
# function handle_SIGRTMIN     () { echo SIGRTMIN    ; exit ; }
# function handle_SIGRTMIN+4   () { echo SIGRTMIN+4  ; exit ; }
# function handle_SIGRTMIN+8   () { echo SIGRTMIN+8  ; exit ; }
# function handle_SIGRTMIN+12  () { echo SIGRTMIN+12 ; exit ; }
# function handle_SIGRTMAX-14  () { echo SIGRTMAX-14 ; exit ; }
# function handle_SIGRTMAX-10  () { echo SIGRTMAX-10 ; exit ; }
# function handle_SIGRTMAX-6   () { echo SIGRTMAX-6  ; exit ; }
# function handle_SIGRTMAX-2   () { echo SIGRTMAX-2  ; exit ; }
# function handle_SIGILL       () { echo SIGILL      ; exit ; }
# function handle_SIGFPE       () { echo SIGFPE      ; exit ; }
# function handle_SIGUSR2      () { echo SIGUSR2     ; exit ; }
# function handle_SIGCHLD      () { echo SIGCHLD     ; exit ; }
# function handle_SIGTTIN      () { echo SIGTTIN     ; exit ; }
# function handle_SIGXFSZ      () { echo SIGXFSZ     ; exit ; }
# function handle_SIGIO        () { echo SIGIO       ; exit ; }
# function handle_SIGRTMIN+1   () { echo SIGRTMIN+1  ; exit ; }
# function handle_SIGRTMIN+5   () { echo SIGRTMIN+5  ; exit ; }
# function handle_SIGRTMIN+9   () { echo SIGRTMIN+9  ; exit ; }
# function handle_SIGRTMIN+13  () { echo SIGRTMIN+13 ; exit ; }
# function handle_SIGRTMAX-13  () { echo SIGRTMAX-13 ; exit ; }
# function handle_SIGRTMAX-9   () { echo SIGRTMAX-9  ; exit ; }
# function handle_SIGRTMAX-5   () { echo SIGRTMAX-5  ; exit ; }
# function handle_SIGRTMAX-1   () { echo SIGRTMAX-1  ; exit ; }



while true ; do 
	sleep 1 ; 
done

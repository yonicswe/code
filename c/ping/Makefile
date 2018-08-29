# Revised to compile under SunOS 4.1.x (no longer necessary to install
# kernel mods).  08/07/92 RJRJr  This makefile is based on the original
# makefiles supplied with tcpdump and traceroute.

# Set DESTDIR to the directory in which the traceroute executable will be
# installed.  /usr/etc is a good place to put a network debugging tool such
# as this.

DESTDIR= /usr/brl/sbin
MANDIR= /usr/brl/man/man1

# You shouldn't need to change anything below this line.

CC= cc
CFLAGS = -O

# At the moment, the INCL variable isn't really needed for anything.
INCL = -I.
LIBS = 

# Script (or program) that returns the machine and os types,
# or just edit in the name yourself.
MD=`mdtype`
OS=`ostype`

# Explicitly define compiliation rule since SunOS 4's make doesn't like gcc.
# Also, gcc does not remove the .o before forking 'as', which can be a
# problem if you don't own the file but can write to the directory.
.c.o:
	rm -f $@; $(CC) $(CFLAGS) -c $*.c

all: submake

ping: ping.o
	$(CC) $(CFLAGS) $(INCL) -o ping ping.o $(LIBS)

submake:
	-@dir=$(MD)-$(OS); set -x; \
	if [ ! -d $$dir ]; then ${MAKE} ${MFLAGS} config; fi; \
	if [ -n "`find Makefile -newer $$dir/Makefile -print`" ]; \
	  then ${MAKE} ${MFLAGS} config; fi; \
	cd $$dir; ${MAKE} ${MFLAGS} ping

# N.B.- symbolic links are used in the subdirectory rather than VPATH
# because at least one Sun cc compiler puts the .o in the wrong place
# when using VPATH and it's almost impossible to get "make depend" to
# do the right thing.

config: 
	-@dir=$(MD)-$(OS); set -x; \
	mkdir $$dir; chmod ug+w $$dir; ln -s ../ping.c $$dir; \
	sed -e "/^all:/d" Makefile >$$dir/Makefile; \
	chmod ug+w $$dir/Makefile; \
	cd $$dir; ${MAKE} ${MFLAGS} depend

install: submake FRC
	-@dir=$(MD)-$(OS); set -x; \
	install -c -o root -g bin -m 4755 $$dir/ping ${DESTDIR}; \
	install -c -o root -g staff -m 664 ping.1 ${MANDIR}

lint:
	lint -hbxn $(INCL) ping.c | \
	    grep -v 'possible pointer alignment problem'

clean:
	-@dir=$(MD)-$(OS); set -x; rm -rf $$dir

FRC:

depend:
	cc -M ping.c | sed 's/\.o//' | \
	awk ' { if ($$1 != prev) \
		{ if (rec != "") print rec; rec = $$0; prev = $$1; } \
		else { if (length(rec $$2) > 78) { print rec; rec = $$0; } \
		else rec = rec " " $$2 } } \
		END { print rec } ' >> makedep;
	echo '/^# DO NOT DELETE THIS LINE/+2,$$d' >eddep;
	echo '$$r makedep' >>eddep;
	echo 'w' >>eddep;
	cp Makefile Makefile.bak;
	ed - Makefile < eddep;
	rm eddep makedep;
	echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile;
	echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile;
	echo '# see make depend above' >> Makefile;

# DO NOT DELETE THIS LINE -- make depend uses it

ping: ping.c /usr/include/stdio.h /usr/include/features.h \
  /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
  /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
  /usr/lib/gcc/i386-redhat-linux/4.1.2/include/stddef.h \
  /usr/include/bits/types.h /usr/include/bits/typesizes.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  /usr/lib/gcc/i386-redhat-linux/4.1.2/include/stdarg.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
  /usr/include/errno.h /usr/include/bits/errno.h \
  /usr/include/linux/errno.h /usr/include/asm/errno.h \
  /usr/include/asm-generic/errno.h /usr/include/asm-generic/errno-base.h \
  /usr/include/sys/time.h /usr/include/time.h /usr/include/bits/time.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/bits/sigset.h /usr/include/sys/param.h \
  /usr/lib/gcc/i386-redhat-linux/4.1.2/include/limits.h \
  /usr/lib/gcc/i386-redhat-linux/4.1.2/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h /usr/include/linux/param.h \
  /usr/include/asm/param.h /usr/include/sys/types.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
  /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h \
  /usr/include/sys/socket.h /usr/include/sys/uio.h \
  /usr/include/bits/uio.h /usr/include/bits/socket.h \
  /usr/include/bits/sockaddr.h /usr/include/asm/socket.h \
  /usr/include/asm/sockios.h /usr/include/sys/file.h /usr/include/fcntl.h \
  /usr/include/bits/fcntl.h /usr/include/netinet/in_systm.h \
  /usr/include/netinet/in.h /usr/include/stdint.h \
  /usr/include/bits/wchar.h /usr/include/bits/in.h \
  /usr/include/netinet/ip.h /usr/include/netinet/ip_icmp.h \
  /usr/include/netdb.h /usr/include/rpc/netdb.h /usr/include/bits/netdb.h
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above

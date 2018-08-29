


all: libs_install	
	gcc -g -Wall -L/opt/lib prog.c -lctest1 -lctest2 -o prog

libs_install: libs
	mv libctest1.so.1.0 /opt/lib
	ln -sf /opt/lib/libctest1.so.1.0 /opt/lib/libctest1.so
	ln -sf /opt/lib/libctest1.so.1.0 /opt/lib/libctest1.so.1
	mv libctest2.so.1.0 /opt/lib
	ln -sf /opt/lib/libctest2.so.1.0 /opt/lib/libctest2.so
	ln -sf /opt/lib/libctest2.so.1.0 /opt/lib/libctest2.so.1
	

sources:
	gcc -g -Wall -fPIC -c *.c

libs: sources
	gcc -shared -Wl,-soname,libctest1.so.1 -o libctest1.so.1.0   ctest1.o
	gcc -shared -Wl,-soname,libctest2.so.1 -o libctest2.so.1.0   ctest2.o
	

clean:
	rm -f *.o *.so prog libctest


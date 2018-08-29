
KDIR = /usr/src/linux
#include $(KDIR)/.config

CFLAGS = -D__KERNEL -DMODULE -I$(KDIR)/include

all: hello.o
clean:
	rm hello.o

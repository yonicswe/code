
# explaing make where to find the kernel.
# KERNEL_PATH := /home/yonic/builds/fig_1.272/src/barak/kernel_secondary
# KERNEL_PATH := /home/yonic/builds/v3.5/rbuild-894/src/barak/kernel
KERNEL_PATH := /usr/src/linux

# define MODNAME
MODNAME := gen_mod.o

# define the source files list
SOURCES = hello_mod.c

CC=powerpc-linux-gcc
LD=powerpc-linux-ld
#ARCH=ppc
#FLAVOR=default
INCLUDES = -I$(KERNEL_PATH)/include

MODCFLAGS := -DMODULE -D__KERNEL__ 

OBJECTS = $(SOURCES:.c=.o)

#.PHONY: clean

CFLAGS = $(INCLUDES) $(MODCFLAGS) -O2 -Wall -Werror
CFLAGS += -msoft-float -DSW_CACHE_COHERENCY

LDFLAGS += -r

all: modules

modules: $(MODNAME)
$(MODNAME): $(OBJECTS)
	@echo -e "\n>>> Linking module [$(MODNAME)]"
	$(LD) $(LDFLAGS) -o $(MODNAME) $(OBJECTS)


.PHONY: gen clean


clean:
	rm -f *.o


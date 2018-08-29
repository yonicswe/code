#------------------------------------------------------------------------------

MAIN_SOURCE =  MemTrack.cpp
MAIN_SOURCE += override_new.cpp

MAIN=override_new

MAIN_LIBS = -lstdc++

CPPFLAGS=-g -O0

CC=g++


#------------------------------------------------------------------------------



all: $(MAIN)

$(MAIN): $(MAIN_SOURCE)
	@echo "Building $@"
	$(CC) -o$(MAIN) $(CPPFLAGS) $(MAIN_LIBS) $(INCLUDES) $(MAIN_SOURCE)

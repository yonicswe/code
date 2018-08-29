
PROG = newGenElem

CPPFILES := $(shell find -name '*.cpp')
OBJFILES := $(notdir $(CPPFILES:%.cpp=%.o))
$(warning $(OBJFILES))	
	
INCLUDE = -I/home/kuser/work/trunk/src/3d_party_4_5_8/UnitTest++/src/
DEPS = -L /home/kuser/work/trunk/src/3d_party_4_5_8/HTTPWbELibs/
LIBS = -l UnitTest++

FLAGS = $(INCLUDE) $(DEPS) $(LIBS)


.PHONY: all
all: $(PROG)

$(PROG): $(OBJFILES)
	$(CC) -o $@ $(FLAGS) $(OBJFILES)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

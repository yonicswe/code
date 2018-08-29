

OUTPUT=bin
PROGRAM=http2Fsm 

CPPFILES := $(shell find -name '*.cpp')
_OBJFILES := $(notdir $(CPPFILES:%.cpp=%.o))
OBJFILES := $(addprefix $(OUTPUT)/, $(_OBJFILES))
_DEPFILES := $(notdir $(CPPFILES:%.cpp=%.d))
DEPFILES := $(addprefix $(OUTPUT)/, $(_DEPFILES))

COMPILE_FLAGS  = -g
COMPILE_FLAGS += -D__POSIX_USER_MODE__ 
LINK_FLAGS =  -D__POSIX_USER_MODE__ 
INCLUDEDIRS=
LIBDIRS=
LIBS=-lstdc++

all: $(OUTPUT)/$(PROGRAM)

$(OUTPUT)/$(PROGRAM): $(DEPFILES) $(OBJFILES)
	$(CC) -o $@ $(OUTPUT)/*.o $(LINK_FLAGS) $(LIBDIRS) $(LIBS)

$(OUTPUT)/%.d: %.cpp
	$(CC) -M -MT '$(patsubst %.d,%.o,$@)' $(COMPILE_FLAGS) $(INCLUDEDIRS) $< > $@

$(OUTPUT)/%.o: %.cpp
	$(CC) $(COMPILE_FLAGS) $(INCLUDEDIRS) -c $< -o $@

clean:
	find $(OUTPUT)/ -type f -delete



OUTPUT=bin
PROGRAM=http2Fsm 

CPPFILES := $(shell find -name '*.cpp')
_OBJFILES := $(notdir $(CPPFILES:%.cpp=%.o))
OBJFILES := $(addprefix $(OUTPUT)/, $(_OBJFILES))
_DEPFILES := $(notdir $(CPPFILES:%.cpp=%.d))
DEPFILES := $(addprefix $(OUTPUT)/, $(_DEPFILES))

CFLAGSLIB=-g
INCLUDEDIRS=
LIBDIRS=
LIBS=-lstdc++

all: $(OUTPUT)/$(PROGRAM)

$(OUTPUT)/$(PROGRAM): $(DEPFILES) $(OBJFILES)
	$(CC) -o $@ $(OUTPUT)/*.o $(LFLAGSLIB) $(LIBDIRS) $(LIBS)

$(OUTPUT)/%.d: %.cpp
	$(CC) -M -MT '$(patsubst %.d,%.o,$@)' $(CFLAGSLIB) $(INCLUDEDIRS) $< > $@

$(OUTPUT)/%.o: %.cpp
	$(CC) $(CFLAGSLIB) $(INCLUDEDIRS) -c $< -o $@

clean:
	find $(OUTPUT)/ -type f -delete

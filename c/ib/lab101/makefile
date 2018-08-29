CC=gcc

OUTPUT=bin

TARGET=$(OUTPUT)/pingpong

OBJFILES  = $(OUTPUT)/main.o
OBJFILES += $(OUTPUT)/requester.o
OBJFILES += $(OUTPUT)/responder.o 

COMPILE_FLAGS  = -g
LINK_FLAGS     = 

INCLUDEDIRS=
LIBDIRS=

LIBS=-libverbs

.phony: all 
.phony: clean

all: $(OUTPUT) $(TARGET)

$(OUTPUT):
	mkdir $@	

$(TARGET): $(OBJFILES) 
	$(CC) -o $@ $(OUTPUT)/*.o $(LINK_FLAGS) $(LIBDIRS) $(LIBS)

$(OUTPUT)/%.o: %.c
	$(CC) $(COMPILE_FLAGS) $(INCLUDEDIRS) -c $< -o $@

clean:
	find $(OUTPUT)/ -type f -delete

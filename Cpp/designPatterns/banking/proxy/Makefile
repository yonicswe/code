
TARGET=client

CXX=g++

CPPFILES := $(shell find -name '*.cpp')
OBJFILES := $(notdir $(CPPFILES:%.cpp=%.o))

all:  $(OBJFILES) $(TARGET)

$(TARGET):
	$(CXX) -o $@ $(OBJFILES) $(LFLAGSLIB) $(LIBDIRS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CFLAGSLIB) $(INCLUDEDIRS) -c $< -o $@

clean:
	rm $(TARGET)
	rm *.o

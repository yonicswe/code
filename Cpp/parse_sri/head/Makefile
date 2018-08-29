#------------------------------------------------------------------------------

PARSER_SOURCE =  parse_sri.cpp
PARSER_SOURCE += sri_handler.cpp
PARSER_SOURCE += hash_table.cpp
PARSER_SOURCE += sri_db.cpp

TESTER_SOURCE =  test_sri_hash.cpp
TESTER_SOURCE += sri_handler.cpp
TESTER_SOURCE += hash_table.cpp
TESTER_SOURCE += sri_db.cpp

PARSER=parser
TESTER=tester


# INCLUDES=-I./

PARSER_LIBS = -lstdc++
PARSER_LIBS += -lsqlite3

TESTER_LIBS = -lstdc++
TESTER_LIBS += -lsqlite3

CPPFLAGS=-g -O0
ifdef DEBUG
CPPFLAGS += -DDEBUG
endif 

CC=g++


#------------------------------------------------------------------------------



all: $(PARSER)

$(PARSER): $(PARSER_SOURCE)
	@echo "Building $@"
	$(CC) -o$(PARSER) $(CPPFLAGS) $(PARSER_LIBS) $(INCLUDES) $(PARSER_SOURCE)

$(TESTER): $(TESTER_SOURCE)
	@echo "Building $@"			 	
	$(CC) -o$(TESTER) $(CPPFLAGS) $(TESTER_LIBS) $(INCLUDES) $(TESTER_SOURCE)

clean:
	rm -f $(PARSER)
	rm -f $(TESTER)


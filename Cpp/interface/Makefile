

SOURCES  = ProtocolBufferClient.o
SOURCES += ClientWrapper.o
SOURCES += RabbitMQSender.o
SOURCES += main.o

LIBS = -lrabbitmq
LIBS += -lstdc++

CFLAGS = -ggdb3

TARGET = pbc


all: $(SOURCES)
	$(CC) -o $(TARGET) $(LIBS) $(CFLAGS) $(SOURCES)

clean:
	find . -regex ".*.o" -exec rm {} \;
	rm -f $(TARGET)

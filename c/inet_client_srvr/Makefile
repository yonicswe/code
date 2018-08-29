

OBJECTS = client.o
OBJECTS += user_funcs.o


client: $(OBJECTS)
	@echo -e "\n>>> Linking client"
	$(CC) -o $@ $(OBJECTS)


clean:
	rm -f client
	rm -f *.o



LIFE_OBJS = life.o
LIFE_OBJS += conf.o


all: life

LIFE_DEPS=$(LIFE_OBJS:.o=.d)

%.d: %.c
	@echo -e "Creating dependency file:" $@
	@$(CC) -MM $(CFLAGS) $< > $@.tmp
	@echo -n "$(shell dirname $@)/" > $@
	@cat $@.tmp >> $@
	@rm $@.tmp

depend : $(LIFE_DEPS)

include $(LIFE_DEPS)

life : depend $(LIFE_OBJS)
	@echo -e "\nBulding life..."
	$(CC) -o $@ $(LIFE_OBJS)


clean:
	@echo "Cleaning life..."
	rm -rf *.o *.d life

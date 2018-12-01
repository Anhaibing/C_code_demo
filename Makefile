ifndef CC
	CC=gcc
endif

ifndef CFLAGS
	CFLAGS=-MMD -O2 -Wall -g
endif

TARGET = anbin
OBJECTS :=  $(patsubst %.c, %.o, $(wildcard *.c))
LIBS +=
LDFLAGS += -lpthread
CFLAGS += -I$(DIR_INC) -02 -g -DCONFIG_DEBUG_FILE -DUSER_FIFO_TEST

DIR_INC =
DIR_LIB =

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Start Building $@ ..."
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o *.d $(TARGET)

.PHONY: clean


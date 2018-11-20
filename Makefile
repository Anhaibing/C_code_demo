ifndef CC
	CC=gcc
endif

ifndef CFLAGS
	CFLAGS=-MMD -O2 -Wall -g
endif

TARGET = anbin
OBJECTS :=  $(patsubst %.c, %.o, $(wildcard *.c))
LIBS +=
LDFLAGS +=
CFLAGS += -I$(DIR_INC) -02 -g -DCONFIG_DEBUG_FILE

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


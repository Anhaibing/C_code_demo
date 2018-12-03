ifndef CC
	CC=gcc
endif

ifndef CFLAGS
	CFLAGS=-MMD -O2 -Wall -g
else
	CFLAGS += -I$(DIR_INC) -O2 -g -DCONFIG_DEBUG_FILE -DUSER_FIFO_TEST
endif

TARGET = anbin
FIFO_DIR = fifo/

SRC_DIR +=  $(wildcard *.c)
SRC_DIR +=  $(wildcard $(FIFO_DIR)*.c)

INC_DIR += $(wildcard *.h)
INC_DIR += $(wildcard $(FIFO_DIR)*.h)

OBJECTS :=  $(patsubst %.c, %.o, $(SRC_DIR))

LIBS +=
LDFLAGS += -lpthread


DIR_INC =
DIR_LIB =

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Start Building $@ ..."
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS) $(INC_DIR)

#$(OBJECTS)/%.o: $(OBJECTS)/%.c $(INC_DIR)
#	$(CC) -o $@ -c $<  $(CFLAGS) 

clean:
	rm -f *.o *.d $(TARGET) $(FIFO_DIR)*.o  $(FIFO_DIR)*.d

.PHONY: clean


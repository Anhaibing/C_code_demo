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
LOG_DIR = log/
COM_DIR = common/

SRC_DIR +=  $(wildcard *.c)
SRC_DIR +=  $(wildcard $(FIFO_DIR)*.c $(LOG_DIR)*.c $(COM_DIR)*.c)

INC_DIR += $(wildcard *.h)
INC_DIR += $(wildcard $(FIFO_DIR)*.h $(LOG_DIR)*.h $(COM_DIR)*.h)

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
	rm -f *.o *.d $(TARGET) $(FIFO_DIR)*.o  $(FIFO_DIR)*.d $(LOG_DIR)*.o  $(LOG_DIR)*.d $(COM_DIR)*.o $(COM_DIR).d

.PHONY: clean


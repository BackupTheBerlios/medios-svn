include ../../../Makefile.conf

ASFLAGS  += -I../../../include
GCCFLAGS += -I../../../include

SRC = $(wildcard *.c)
SRC2 = $(wildcard *.S)
OBJS = $(SRC:%.c=%.o) $(SRC2:%.S=%.o)

SUBDIRS = file_browser widgets

all: subdirs $(OBJS)
	@cp -f *.o ../../build

clean: clean-subdirs 
	@rm -f *.o *.bak *~ $(TARGET)

include ../../../default.rule
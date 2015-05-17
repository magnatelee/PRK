OFLAGS  := -O2 -qopenmp -Wall -xHOST
OFLAGS  := -opt-report=5

CC      := /opt/mpich/dev/intel/default/bin/mpicc
CFLAGS  := $(OFLAGS) -std=c99

FC      := mpifort
FFLAGS  := $(OFLAGS)

LD      := $(CC)
LDFLAGS := $(OFLAGS)

HEADERS = prk-alloc.h prk-util.h prk-transpose.h

.PHONY: all clean

all: serial.x

%.x: %.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f *.o
	-rm -f *.x


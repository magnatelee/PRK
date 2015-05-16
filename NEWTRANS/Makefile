OFLAGS  := -O3 -qopenmp

CC      := mpicc
CFLAGS  := $(OFLAGS) -std=c99

FC      := mpifort
FFLAGS  := $(OFLAGS)

LD      := $(CC)
LDFLAGS := $(OFLAGS)

.PHONY: all clean

all:

%.x: %.o
	$(LD) $< -o $@

%.o: %.c
	$(CC) $< -o $@

clean:
	-rm -f *.o
	-rm -f *.x


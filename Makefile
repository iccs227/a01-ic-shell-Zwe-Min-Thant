CC=gcc
CFLAGS=-Wall -g 
BINARY=icsh

all: icsh MileStone

icsh: icsh.c
	$(CC) -o $(BINARY) $(CFLAGS) $<
MileStone: MileStone1.c
	$(CC) -o MileStone $(CFLAGS) $<
.PHONY: clean

clean:
	rm -f $(BINARY)

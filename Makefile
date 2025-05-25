CC=gcc
CFLAGS=-Wall -g 
BINARY=icsh

all: $(BINARY) 

$(BINARY): ./icsh.c ./Toknizer.c ./MileStone1.c ./MileStone2.c
	$(CC) -o $(BINARY) $(CFLAGS) ./icsh.c ./Toknizer.c ./MileStone1.c ./MileStone2.c

.PHONY: clean

clean:
	rm -f sourceCodes/*.o $(BINARY)
   
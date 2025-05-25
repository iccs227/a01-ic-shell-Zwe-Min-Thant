CC=gcc
CFLAGS=-Wall -g 
BINARY=icsh

all: $(BINARY) 

$(BINARY): ./sourceCodes/icsh.c ./sourceCodes/Toknizer.c ./sourceCodes/MileStone1.c ./sourceCodes/MileStone2.c
	$(CC) -o $(BINARY) $(CFLAGS) ./sourceCodes/icsh.c ./sourceCodes/Toknizer.c ./sourceCodes/MileStone1.c ./sourceCodes/MileStone2.c

.PHONY: clean

clean:
	rm -f sourceCodes/*.o $(BINARY)
   
.PHONY: all clean

CC := gcc
CFLAGS := -I.

all:
	$(CC) -o client idgram-cl.c $(CFLAGS) idgram_sck.h 
	$(CC) -o server idgram-sv.c $(CFLAGS) idgram_sck.h

clean:
	rm -rf client server

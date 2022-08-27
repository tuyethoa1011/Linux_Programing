.PHONY: clean all

CC := gcc
CFLAGS := -I.

INC_FILES := ustream_sck.h

all:
	$(CC) -o client stream-cl.c $(CFLAGS) $(INC_FILES)
	$(CC) -o server stream-sv.c $(CFLAGS) $(INC_FILES)
clean:
	rm -rf client server


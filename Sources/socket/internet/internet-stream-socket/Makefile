.PHONY: all clean

CC := gcc
C_FLAGS := -I.
INCLUDE := istream_sck.h

all:
	$(CC) -o server istream-sv.c $(C_FLAGS) $(INCLUDE)
	$(CC) -o client istream-cl.c $(C_FLAGS) $(INCLUDE)
clean:
	rm -rf client server


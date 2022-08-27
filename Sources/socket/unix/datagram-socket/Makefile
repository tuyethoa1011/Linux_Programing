.PHONY: clean all

all:
	gcc -o client client-dgram.c -I. ud_sck.h
	gcc -o server server-dgram.c -I. ud_sck.h

rm:
	rm -rf client server


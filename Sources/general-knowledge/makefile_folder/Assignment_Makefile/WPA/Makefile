.PHONY: wpamake wpa 

CC := gcc
CFLAGS := -I.
CFILES := CE.c hello.c file1.c file2.c
CPPFILES := wpa.cpp

INC_CFILES := CE.h hello.h file1.h file2.h
INC_CPPFILES := wpa.h

%.o: %.c $(INC_CFILES)
	$(CC) $(CFLAGS) -c -o $@ $<
%.o: %.cpp $(INC_CPPFILES)
	g++ $(CFLAGS) -c -o  $@ $<

wpamake: main.o CE.o hello.o file1.o file2.o wpa.o
	g++ -o $@ $^ $(CFLAGS)
clean:
	rm -rf wpamake *.o
	

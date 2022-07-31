
shared:
	gcc -shared obj/quote.o -o lib/shared/libquote.so
static:
	ar rcs lib/static/libhello.a obj/helloworld.o obj/helloHoa.o 
link:
	gcc obj/main.o -L lib/static -lhello -L lib/shared -lquote -o bin/hi
use_shr_lib:
	LD_LIBRARY_PATH=$(pwd)/lib/shared bin/hi
move_shr_lib:
	sudo mv lib/shared/libquote.so /usr/lib
	sudo chmod 755 /usr/lib/libquote.so
all:
	gcc -c src/helloworld.c -o obj/helloworld.o -I./inc
	gcc -c src/helloHoa.c -o obj/helloHoa.o -I./inc
	gcc -c main.c -o obj/main.o -I./inc
	gcc -c -fPIC src/quote.c -o obj/quote.o -I./inc
clean:
	rm -rf obj/* bin/* lib/shared/*.so lib/static/*.a

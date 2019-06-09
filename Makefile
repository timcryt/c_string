all: libcstring.a

clean:
	rm *.o *.a

install: libcstring.a
	sudo cp libcstring.a /usr/lib/
	sudo cp c_string.h /usr/include/

test: libcstring_debug.a test.c c_string.h
	gcc -Wall -g test.c -o test -L. -lcstring_debug
	valgrind ./test
	rm test libcstring_debug.a c_string_debug.o

libcstring_debug.a: c_string_debug.o
	ar cr libcstring_debug.a c_string_debug.o

libcstring.a: c_string.o
	ar cr libcstring.a c_string.o

c_string_debug.o: main.c c_string.h
	gcc -Wall -g -c main.c -o c_string_debug.o

c_string.o: main.c c_string.h
	gcc -Wall -O2 -c main.c -o c_string.o



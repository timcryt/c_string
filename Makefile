all: libcstring.a

clean:
	rm *.o *.a

install: libcstring.a
	sudo cp libcstring.a /usr/lib/

test: libcstring.a test.c
	gcc -O2 -s test.c -o test -L. -lcstring
	valgrind ./test
	rm test

libcstring.a: c_string.o
	ar cr libcstring.a c_string.o

c_string.o: main.c
	gcc -O2 -c main.c -o c_string.o



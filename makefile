sources.so: sources.o
	gcc -shared -o src/fd1d/sources.so sources.o

sources.o: src/fd1d/sources.c
	gcc -O3 -c -Wall -Werror -fpic -lm src/fd1d/sources.c

clean:
	rm -f sources.o

simulation.so: simulation.o sources.o
	gcc -shared -o src/fd1d/simulation.so simulation.o sources.o

simulation.o: src/fd1d/simulation.c
	gcc -O3 -c -Wall -Werror -fpic -lm src/fd1d/simulation.c

sources.o: src/fd1d/sources.c
	gcc -O3 -c -Wall -Werror -fpic -lm src/fd1d/sources.c

clean:
	rm -f simulation.o sources.o

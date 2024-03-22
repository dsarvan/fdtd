simulation.so: simulation.o sources.o
	gcc -shared -o src/fdtd/simulation.so simulation.o sources.o

simulation.o: src/fdtd/simulation.c
	gcc -O3 -c -Wall -Werror -fpic -lm src/fdtd/simulation.c

sources.o: src/fdtd/sources.c
	gcc -O3 -c -Wall -Werror -fpic -lm src/fdtd/sources.c

clean:
	rm -f simulation.o sources.o

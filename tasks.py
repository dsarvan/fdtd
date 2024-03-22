#!/usr/bin/env python
import invoke

@invoke.task
def simulation(ctx, path=None):
	ctx.run("gcc -O3 -c -Wall -Werror -fpic -lm src/fdtd/sources.c")
	ctx.run("gcc -O3 -c -Wall -Werror -fpic -lm src/fdtd/simulation.c")
	ctx.run("gcc -shared -o src/fdtd/simulation.so simulation.o sources.o")

@invoke.task
def clean(ctx, path=None):
	ctx.run("rm -f simulation.o sources.o")

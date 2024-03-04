#!/usr/bin/env python
import invoke

@invoke.task
def sources(ctx, path=None):
	ctx.run("gcc -O3 -c -Wall -Werror -fpic -lm src/fd1d/sources.c")
	ctx.run("gcc -shared -o src/fd1d/sources.so sources.o")

@invoke.task
def clean(ctx, path=None):
	ctx.run("rm -f sources.o")

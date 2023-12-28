all: seeds_1

debug: seeds_debug_1

seeds_1: seeds_1.c
	clang -o bin/seeds_1 seeds_1.c

seeds_debug_1: seeds_1.c
	clang -o bin/seeds_1 seeds_1.c -g -O0

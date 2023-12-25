all: gear_ratios gear_ratios_2

debug: debug_1 debug_2

gear_ratios: gear_ratios.c
	clang -o bin/gear_ratios -lm gear_ratios.c

gear_ratios_2: gear_ratios_2.c
	clang -o bin/gear_ratios_2 -lm gear_ratios_2.c

debug_1: gear_ratios.c
	clang -g -O0 -o bin/gear_ratios gear_ratios.c -lm

debug_2: gear_ratios_2.c
	clang -g -O0 -o bin/gear_ratios_2 gear_ratios_2.c -lm

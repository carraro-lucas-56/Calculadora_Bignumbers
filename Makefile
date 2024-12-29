all: main

main: main.o operations.o bignumber.o
	gcc main.o operations.o bignumber.o -lm -o main

main.o: main.c operations.h bignumber.h
	gcc -std=c99 -Wall -Werror -O3 -c main.c

bignumber.o: bignumber.c bignumber.h
	gcc -std=c99 -Wall -Werror -O3 -c bignumber.c -lm

operations.o: operations.c operations.h bignumber.h
	gcc -std=c99 -Wall -Werror -O3 -c operations.c
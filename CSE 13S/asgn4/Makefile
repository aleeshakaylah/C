CFLAGS = -Wall -Wextra -Werror -Wpedantic
CC = clang $(CFLAGS)

sequence : sequence.o sieve.o bv.o
	$(CC) -o sequence sequence.o sieve.o bv.o -lm

sequence.o : sequence.c
	$(CC) -c sequence.c

sieve.o : sieve.c
	$(CC) -c sieve.c

bv.o : bv.c
	$(CC) -c bv.c

all : sequence.c

clean :
       	rm -f sequence sequence.o sieve.o bv.o

memcheck : tower
        valgrind --leak-check=full sequence

infer :
       	make clean; infer-capture --make; infer-analyze --make

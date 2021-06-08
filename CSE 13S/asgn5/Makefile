CFLAGS = -Wall -Wextra -Werror -Wpedantic
CC = clang $(CFLAGS)

sorting : sorting.o binary.o bubble.o quick.o shell.o
	$(CC) -o sorting sorting.o binary.o bubble.o quick.o shell.o  -lm

sorting.o : sorting.c
	$(CC) -c sorting.c

binary.o : binary.c
	$(CC) -c binary.c

bubble.o : bubble.c
	$(CC) -c bubble.c

quick.o : quick.c
	$(CC) -c quick.c

shell.o : shell.c
	$(CC) -c shell.c

all : sorting.c

clean :
	rm -f sorting sorting.o binary.o bubble.o quick.o shell.o

valgrind : sorting
	valgrind --leak-check=full sorting

infer : 
	make clean; infer-capture -- make; infer-analyze -- make

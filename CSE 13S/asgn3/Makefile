CFLAGS = -Wall -Wextra -Werror -Wpedantic
CC = clang $(CFLAGS)

tower : tower.o stack.o
	$(CC) -o tower tower.o stack.o -lm

tower.o : tower.c
	$(CC) -c tower.c

stack.o : stack.c
	$(CC) -c stack.c

all : tower.c

clean :
	rm -f tower tower.o stack.o

memcheck : tower
	valgrind --leak-check=full tower

infer :
	make clean; infer-capture --make; infer-analyze --make

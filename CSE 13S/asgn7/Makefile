CFLAGS = -Wall -Wextra -Werror -Wpedantic
CC = clang $(CFLAGS)

all : encode decode

encode : encode.o io.o trie.o word.o
	$(CC) -o encode encode.o io.o trie.o word.o -lm

decode : decode.o io.o trie.o word.o
	$(CC) -o decode decode.o io.o trie.o word.o -lm

encode.o : encode.c
	$(CC) -c encode.c

decode.o : decode.c
	$(CC) -c decode.c

io.o : io.c
	$(CC) -c io.c

trie.o : trie.c
	$(CC) -c trie.c

word.o : word.c
	$(CC) -c word.c

clean :
	rm -f encode encode.o decode decode.o io.o trie.o word.o

valgrind : encode decode
	valgrind --leak-check=full encode decode

infer :
	make clean; infer-capture -- make; infer-analyze -- make


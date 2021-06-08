CFLAGS = -Wall -Wextra -Werror -Wpedantic
CC = clang $(CFLAGS)

hatterspeak : hatterspeak.o bf.o bv.o hash.o hs.o ll.o parser.o speck.o
	$(CC) -o hatterspeak hatterspeak.o bf.o bv.o hash.o hs.o ll.o parser.o speck.o  -lm -g

hatterspeak.o : hatterspeak.c
	$(CC) -c hatterspeak.c

bf.o : bf.c
	$(CC) -c bf.c

bv.o : bv.c
	$(CC) -c bv.c

hash.o : hash.c
	$(CC) -c hash.c

hs.o : hs.c
	$(CC) -c hs.c

ll.o : ll.c
	$(CC) -c ll.c

parser.o : parser.c
	$(CC) -c parser.c

speck.o : speck.c
	$(CC) -c speck.c

all : hatterspeak.c

clean :
	rm -f hatterspeak hatterspeak.o bf.o bv.o hash.o hs.o ll.o parser.o speck.o

valgrind : hatterspeak
	valgrind --leak-check=full hatterspeak

infer :
	make clean; infer-capture -- make; infer-analyze -- make

Aleesha Nageer
CSE 13S
Fall 2020

NOTE: There are some memory leaks in my code, tried to free up the memory but couldn't get all of the memory to free.
INFER ISSUES: 2 NULL Dereferences 

Assignment 4: This lab takes user input of -s, -h <value>, -f <value>, -m, and -b.
		-s: Prints statistics for the number of seeks, average seek length, average linked list length, the hash table load, and the bloom filter load
		-h <value>: Sets the hash table size
		-f <value>: Sets bloom filter size
		-m: Changes the move_to_front flag to true
		-b: Changes the move_to_front flag to false

Files:
hatterspeak.c: Contains main function that parses arguments, reads in files, reads in and parses user data, inserts file data into the bloom filter and hash table,
		initializes nodes, identifies key value pairs, and prints final message/statistics

bf.h: Header file containing helper function for building Bloom Filter

bf.c: Contains functions for creating the Bloom Filter, inserting hashed values as bits, and probing the Bloom Filter

bv.h: Header file containing helper functions for conveting numbers into bit vectors

bv.c: Contains functions for converting numbers into bit vectors

hash.h: Header file containing helper functions for building Hash Table

hash.c: Contains functions for building hash table, looking through to find the heads of linked lists, and inserting values into linked lists

hs.h: Header file containing helper functions for making HatterSpeak nodes

hs.c: Contains functions for building Hatterspeak nodes

ll.h: Header file containing helper functions for building linked lists

ll.c: Contains functions for building linked lists, looking for key-value pairs, and inserting nodes into the linked list

Makefile: Compiles program and makes executable

DESIGN.pdf: Contains pseudocode and design process for Assignment 6.

WRITEUP.pdf: Contains what I learned from this assignment, as well as my evaluation of whether the move to front flag is needed and if varying the hash 
		table and bloom filter sizes would effect the statistic results.

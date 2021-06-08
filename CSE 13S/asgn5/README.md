Aleesha Nageer
CSE 13S
Fall 2020

NOTE: There are some memory leaks in my code, tried to free up the memory but couldn't figure out how to make it work.

Assignment 4: This lab takes user input of -A, -b, -s, -q, -i, -p <value>, -r <value>, and -n <value>.
		-A : Prints out a sequence of values in an array in ascending order using all four sorting algorithms (Binary Insertion, Quick, Shell, and Bubble)
		-b : Prints out a sequence of values in an array in ascending order using the Bubble Sort algorithm
		-s : Prints out a sequence of values in an array in ascending order using the Shell Sort algorithm
		-q : Prints out a sequence of values in an array in ascending order using the Quick Sort algorithm
		-i : Prints out a sequence of values in an array in ascending order using the Binary Insertion Sort algorithm
		-p <value> : Provides a range for the amount of numbers to be printed after sorting
		-r <value> : Provides a seed value for initialization of random numbers
		-n <value> : Provides an array size (number of values)
Files:
sorting.c: Contains main function that parses arguments, initializes values to build a struct that contains statistics, and printing functions

sorting.h: Header file containing helper function for building Statistics struct

binary.h: Header file containing helper functions for Binary Insertion Sort algorithm

binary.c: Contains functions for performing Binary Insertion Sort algorithm

quick.h: Header file containing helper functions for Quick Sort algorithm

quick.c: Contains functions for performing Quick Sort algorithm

shell.h: Header file containing helper functions for Shell Sort algorithm

shell.c: Contains functions for performing Shell Sort algorithm

bubble.h: Header file that contains helper functions for Bubble Sort algorithm

bubble.c: Contains functions for performing Bubble Sort algorithm

Makefile: Compiles program and makes executable

DESIGN.pdf: Contains pseudocode and design process for Assignment 5.

WRITEUP.pdf: Contains time complexities and how they vary for each sorting algorithm, what I learned from this assignment, and how I experimented with the sorts.

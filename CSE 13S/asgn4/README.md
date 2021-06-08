Aleesha Nageer
CSE 13S
Fall 2020

NOTE: My make infer does not work, base 24 doesn't print the palindromes properly, and I think somethings wrong with my bv because I have
to add conditional statements to get all of the prime numbers. I had a rough week. Sorry grader in advance.

Assignment 4: This lab takes user input of -s, -p, and -n <value>. -s will print out a sequence of prime numbers based on the value given
by the user (if no value is given, it will sieve prime numbers up to 1000) and label them based on if they are a Fibonacci, Lucas, or Mersenne
prime number. -p will go through the prime values up to the value given by the user at different bases (base 2, base, 9, base 10, and base 24) 
and see if they are palindromic.

Files:
sequence.c: Contains fibonacci, lucas, mmersenne, base 2, 9, 10, and 24, and main functions for running this program

bv.h: Header file containing helper functions used in bv.c to help divide and separate particular bits

bv.c: Contains function definitions for bv.h

sieve.h: Header file that contains helper function for finding prime numbers

sieve.c: Contains function defenition for sieve.h

Makefile: Compiles program and makes executable

DESIGN.pdf: Contains pseudocode and design process for Assignment 4.


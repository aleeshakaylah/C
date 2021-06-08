#ifndef __SORTING_H__
#define __SORTING_H__

#include <stdio.h>
#include <stdlib.h>

// Defines struct components used in every file
typedef struct Statistics {
  long *vector;
  long seed;
  long array_size;
  long number_of_moves;
  long number_of_comparisons;
} Statistics;

#endif

#include "sorting.h"
#include "binary.h"
#include "bubble.h"
#include "quick.h"
#include "shell.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize_vector(Statistics *s, long size) {
  srand(s->seed);
  for (long i = 0; i < size; i++)
    s->vector[i] = rand() & 0x3FFFFFFF;
}

void display_vector(Statistics *s, long print_range) {
  for (long i = 0; i < print_range; i++)
    if (i == 0 || i % 7 != 0) {
      printf("\t%13ld", s->vector[i]);
    } else {
      printf("\n\t%13ld", s->vector[i]);
    }
  printf("\n");
}

void print_statistics(Statistics *s, long print_range) {
  printf("%ld elements, ", s->array_size);
  printf("%ld moves, ", s->number_of_moves);
  printf("%ld compares\n", s->number_of_comparisons);
  display_vector(s, print_range);
}

void copy_statistics(Statistics *from, Statistics *to) {

  to->seed = from->seed;

  to->array_size = from->array_size;
  to->number_of_moves = from->number_of_moves;
  to->number_of_comparisons = from->number_of_comparisons;

  for (int i = 0; i < from->array_size; i++) {
    to->vector[i] = from->vector[i];
  }
}

void delete_statistics(Statistics *s) {
  free(s->vector);
  s->vector = NULL;
  free(s);
}

int main(int argc, char **argv) {
  int c = 0, binary = 0, quick = 0, shell = 0, bubble = 0;
  long print_size = 100, seed = 8222022, array_size = 100;

  while ((c = getopt(argc, argv, "Absqip:r:n:")) != -1) {
    switch (c) {
    case 'A':
      binary = 1;
      quick = 1;
      shell = 1;
      bubble = 1;
      break;

    case 'b':
      bubble = 1;
      break;

    case 's':
      shell = 1;
      break;

    case 'q':
      quick = 1;
      break;

    case 'i':
      binary = 1;
      break;

    case 'p':
      print_size = atoi(optarg);
      break;

    case 'r':
      seed = atoi(optarg);
      break;

    case 'n':
      array_size = atoi(optarg);
      if (array_size < 2) {
        printf("ARRAY ALREADY SORTED\n");
        exit(0);
      }
      break;
    }
  }

  struct Statistics *sortStats = (Statistics *)malloc(sizeof(Statistics));
  if (sortStats == NULL) {
    printf("MALLOC FAILED");
    exit(0);
  }
  // each sort algorithm stores its own Statistics
  // make sure the array data is the same for each algorithm
  struct Statistics *sortStatsArray[4];

  // initilise the sortStats structure
  if (seed <= 0) {
    sortStats->seed = 8222022;
  } else {
    sortStats->seed = seed;
  }
  sortStats->array_size = array_size;
  sortStats->number_of_moves = 0;
  sortStats->number_of_comparisons = 0;
  sortStats->vector = (long *)(calloc(
      sortStats->array_size, sizeof(long) * sortStats->array_size));
  if (sortStats->vector == NULL) {
    printf("CALLOC FAILED\n");
    exit(0);
  }
  initialize_vector(sortStats, sortStats->array_size);

  // copy this structure into each sortStatsArray so it can be used for each sort algorithm
  for (int i = 0; i < sortStats->array_size; i++) {
    sortStatsArray[i] = (struct Statistics *)malloc(sizeof(struct Statistics));
    if (sortStatsArray[i] == NULL) {
      printf("MALLOC FAILED\n");
      exit(0);
    }
    sortStatsArray[i]->vector = (long *)(calloc(
        sortStats->array_size, sizeof(long) * sortStats->array_size));
    if (sortStatsArray[i]->vector == NULL) {
      printf("CALLOC FAILED\n");
      exit(0);
    }
    copy_statistics(sortStats, sortStatsArray[i]);
  }

  if (print_size < 0 || print_size > array_size) {
    print_size = array_size;
  }

  delete_statistics(sortStats);

  if (binary == 1) {
    binary_sort(sortStatsArray[0]);
    printf("Binary Insertion Sort\n");
    print_statistics(sortStatsArray[0], print_size);
  }

  if (quick == 1) {
    quick_sort(sortStatsArray[1]);
    printf("\nQuick Sort\n");
    print_statistics(sortStatsArray[1], print_size);
  }

  if (shell == 1) {
    shell_sort(sortStatsArray[2]);
    printf("\nShell Sort\n");
    print_statistics(sortStatsArray[2], print_size);
  }

  if (bubble == 1) {
    bubble_sort(sortStatsArray[3]);
    printf("\nBubble Sort\n");
    print_statistics(sortStatsArray[3], print_size);
  }

  // Release all memory before exit
  for (int i = 0; i < 4; i++) {
    delete_statistics(sortStatsArray[i]);
  }
}

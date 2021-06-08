#include "quick.h"

long partition(long num_array[], long left, long right, Statistics *s) {
  long temp, temp2;
  long pivot = num_array[left];
  long lo = left + 1;
  long hi = right;

  while (1) {
    while (lo <= hi && num_array[hi] >= pivot) {
      hi--;
      s->number_of_comparisons++;
    }
    while (lo <= hi && num_array[lo] <= pivot) {
      lo++;
      s->number_of_comparisons++;
    }
    if (lo <= hi) {
      temp = num_array[lo];
      num_array[lo] = num_array[hi];
      num_array[hi] = temp;

      s->number_of_comparisons++;
      s->number_of_moves += 3;
    } else {
      break;
    }
  }
  temp2 = num_array[left];
  num_array[left] = num_array[hi];
  num_array[hi] = temp2;
  s->number_of_moves += 3;

  return hi;
}

void quick_insertion(long num_array[], long left, long right, Statistics *s) {
  long index;
  if (left < right) {
    index = partition(num_array, left, right, s);
    quick_insertion(num_array, left, index - 1, s);
    quick_insertion(num_array, index + 1, right, s);
  }
}

void quick_sort(Statistics *s) {
  quick_insertion(s->vector, 0, (s->array_size - 1), s);
}

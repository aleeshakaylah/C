#include "binary.h"

void binary_sort(Statistics *s) {
  long temp;
  for (long i = 1; i <= s->array_size - 1; i++) {
    long value = s->vector[i];
    long left = 0;
    long right = i;

    while (left < right) {
      long mid = left + floor(((right - left) / 2));

      if (value >= s->vector[mid]) {
        left = mid + 1;
      } else {
        right = mid;
      }
      s->number_of_comparisons++;
    }

    for (long j = i; j > left; j--) {
      temp = s->vector[j - 1];
      s->vector[j - 1] = s->vector[j];
      s->vector[j] = temp;
      s->number_of_moves += 3;
    }
  }
}

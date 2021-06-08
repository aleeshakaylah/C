#include "shell.h"

/*long gap(long array_size){
	while (array_size > 1){
		printf("long gap function size: %ld\n", array_size);
		if (array_size <= 2){
			array_size = 1;
			printf("went into if: %ld\n", array_size);
		} else {
			array_size = floor((5 * array_size) / 11);
			printf("went into else: %ld\n", array_size);
		}
	}
}*/

void shell_sort(Statistics *s) {
  long temp;
  long gap = s->array_size;
  while (gap > 1) {
    if (gap <= 2) {
      gap = 1;
    } else {
      gap = floor((5 * gap) / 11);
    }

    // Source: The C Programming Language - Ch. 3.5
    for (long i = gap; i <= s->array_size - 1; i++) {
      for (long j = i - gap; j >= 0; j -= gap) {
        if (s->vector[j] > s->vector[j + gap]) {
          temp = s->vector[j];
          s->vector[j] = s->vector[j + gap];
          s->vector[j + gap] = temp;
          s->number_of_moves += 3;
        }
        s->number_of_comparisons++;
      }
    }
  }
}

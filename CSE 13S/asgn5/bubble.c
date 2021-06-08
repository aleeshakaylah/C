#include "bubble.h"

/*void bubble_sort(Statistics *s){
	long i, j, temp;
	long n = s->arraySize;
		for (i = 0; i <= (n - 1); i++){
			long j = n - 1;
			int temp = 0;
			while (j > i){
				//printf("j: %ld\n", j);
				//printf("i: %ld\n", i);
				//comparisons++;
				//printf("array value %ld", s->vector[j]);
				if (s->vector[j] > s->vector[j-1]){
					printf("array value j: %ld", s->vector[j]);
					printf("array value j - 1: %ld", s->vector[j - 1]);
					s->vector[j] = temp;
					s->vector[j - 1] = s->vector[j];
					temp = s->vector[j - 1];
					//moves++;
				}
				j--;
			}
		}
	//return num_array[array_size];
}*/

// A function to implement bubble sort
void bubble_sort(Statistics *s) {
  long i, j, temp;
  long n = s->array_size;
  for (i = 0; i < n - 1; i++)
    // Last i elements are already in place
    for (j = 0; j < n - i - 1; j++) {
      if (s->vector[j] > s->vector[j + 1]) {
        temp = s->vector[j];
        s->vector[j] = s->vector[j + 1];
        s->vector[j + 1] = temp;
        s->number_of_moves += 3;
      }
      s->number_of_comparisons++;
    }
}

#include "bv.h"
#include "sieve.h"
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Checks if number is a Fibonacci Prime Number
int fibonacci(uint32_t n, uint32_t p) {
  int i;
  uint32_t fib, n1, n2;
  n1 = 0;
  n2 = 1;
  for (i = 2; i < n; ++i) {
    fib = n1 + n2;
    n1 = n2;
    n2 = fib;
    if (fib == p)
      return 1;
    else if (fib > p)
      return 0;
  }
  return 0;
}

// Checks if number is a Lucas Prime Number
int lucas(uint32_t n, uint32_t p) {
  int i;
  uint32_t luc, n1, n2;
  n1 = 2;
  n2 = 1;
  for (i = 2; i < n; ++i) {
    luc = n1 + n2;
    n1 = n2;
    n2 = luc;
    if (luc == p)
      return 1;
    else if (luc > p)
      return 0;
  }
  return 0;
}

// Checks if number is a Mersenne Prime Number
int mersenne(BitVector *bv, uint32_t n, uint32_t p) {
  int i;
  uint32_t mer;
  for (uint32_t i = 2; i <= n; i++) {
    if (i == 2 || (bv_get_bit(bv, i) && i % 2 != 0)) {
      //printf("mer = %d i= %d",mer, i);
      mer = pow(2, i) - 1;
      if (mer == p) {
        return 1;
      } else if (mer > p) {
        return 0;
      }
    }
  }
  return 0;
}

// Converts Prime Number into Base 2 and checks to see if
// it's a Palindrome
bool base_two(uint32_t p) {
  int binary[200];
  int i = 0;
  int count = 0;

  // reverse binary number, no need to reverse since we are
  // looking for palindromes
  while (p != 0) {
    binary[i] = p % 2;
    p = p / 2;
    count++;
    i++;
  }

  bool flag = true;
  int j = 0;
  int h = count - 1;

  while (h > j) {
    if (binary[j++] != binary[h--]) {
      flag = false;
    }
  }

  /*for (j = 0; j <= (count/2); j++){
		if (binary[j] != (binary[j] - 1)){
			flag = false;
		}
	}*/

  return flag;
}

bool base_nine(uint32_t p) {
  int nine[200];
  int i = 0;
  int count = 0;

  // reverse base 9 number, no need to reverse since we are
  // looking for palindromes
  while (p != 0) {
    nine[i] = p % 9;
    p = p / 9;
    count++;
    i++;
  }

  bool flag = true;
  int j = 0;
  int h = count - 1;

  if (count == 1) {
    flag = true;
  } else {
    while (h > j) {
      if (nine[j++] != nine[h--]) {
        flag = false;
      }
    }
  }

  return flag;
}

bool base_ten(uint32_t p) {
  int remainder, reversed_num = 0;
  int original_num = p;
  bool flag = true;

  while (p != 0) {
    remainder = p % 10;
    reversed_num = reversed_num * 10 + remainder;
    p /= 10;
  }

  if (original_num != reversed_num) {
    flag = false;
  }
  return flag;
}

bool base_kobe(uint32_t p) {
  int twenty_four[200];
  int i = 0;
  int count = 0;
  char buffer[200];

  // reverse base 9 number, no need to reverse since we are
  // looking for palindromes
  while (p != 0) {
    twenty_four[i] = p % 24;
    if (twenty_four[i] >= 10) {

      twenty_four[i] = (twenty_four[i] - 10 + 'a');

      printf("%d", twenty_four[i]);
    } else {
      twenty_four[i] = (twenty_four[i]);
    }
    //printf("%d", twenty_four[i]);
    p = p / 24;
    count++;
    i++;
  }

  bool flag = true;
  int j = 0;
  int h = count - 1;

  if (count == 1) {
    flag = true;
  } else {
    while (h > j) {
      if (twenty_four[j++] != twenty_four[h--]) {
        flag = false;
      }
    }
  }

  return flag;
}

int main(int argc, char **argv) {
  int c = 0;
  uint32_t n = 1000;
  int sequence = 0, palindrome = 0;

  while ((c = getopt(argc, argv, "spn:")) != -1) {
    switch (c) {
    case 's':
      sequence = 1;
      break;

    case 'p':
      palindrome = 1;
      break;

    case 'n':
      n = atoi(optarg);
      break;
    }
  }

  if (sequence == 1) {
    BitVector *bv = bv_create(n);
    sieve(bv);

    for (uint32_t p = 1; p <= n; p++) {
      if ((p == 2) || (bv_get_bit(bv, p) && p % 2 != 0)) {
        printf("%d: prime", p);
        if (mersenne(bv, n, p))
          printf(", mersenne");
        if (lucas(n, p))
          printf(", lucas");
        if (fibonacci(n, p))
          printf(", fibonacci");
        printf("\n");
      }
    }
  }

  if (palindrome == 1) {
    BitVector *bv = bv_create(n);
    sieve(bv);
    int i = 0, j = 0, k = 0;
    int binary[200];
    int nine[200];
    int twenty_four[200];

    printf("Base  2");
    printf("---- --");

    for (uint32_t p = 1; p <= n; p++) {
      if ((p == 2) || (bv_get_bit(bv, p) && p % 2 != 0)) {
        if (base_two(p) == true) {
          printf("%d = ", p);

          while (p != 0) {
            binary[i] = p % 2;
            p = p / 2;
            printf("%d", p);
            i++;
          }
          printf("\n");
        }
      }
    }

    printf("Base  9");
    printf("---- --");
    for (uint32_t p = 1; p <= n; p++) {
      if ((p == 2) || (bv_get_bit(bv, p) && p % 2 != 0)) {
        if (base_nine(p) == true) {
          printf("%d = ", p);

          while (p != 0) {
            nine[j] = p % 9;
            p = p / 9;
            printf("%d", p);
            j++;
          }
          printf("\n");
        }
      }
    }

    printf("Base 10");
    printf("---- --");
    for (uint32_t p = 1; p <= n; p++) {
      if ((p == 2) || (bv_get_bit(bv, p) && p % 2 != 0)) {
        if (base_ten(p) == true) {
          printf("%d = %d\n", p, p);
        }
      }
    }

    printf("Base 24");
    printf("---- --");
    for (uint32_t p = 1; p <= n; p++) {
      if ((p == 2) || (bv_get_bit(bv, p) && p % 2 != 0)) {
        if (base_kobe(p) == true) {
          printf("%d = ", p);

          while (p != 0) {
            twenty_four[k] = p % 24;
            if (twenty_four[k] >= 10) {
              twenty_four[k] = (twenty_four[k] - 10 + 'a');
            } else {
              twenty_four[k] = (twenty_four[k]);
            }
            printf("%d", twenty_four[k]);
            //printf("%d", twenty_four[i]);
            p = p / 24;
            k++;
          }
          printf("\n");
        }
      }
    }
  }
  bv_delete(bv);
}

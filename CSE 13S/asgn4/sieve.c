
#include "sieve.h"
#include <math.h>

void sieve(BitVector *v) {

  bv_set_all_bits(v); // set all the bits in the vector
  bv_clr_bit(v, 0); // clear bit 0,1
  bv_clr_bit(v, 1);
  bv_set_bit(v, 2); // set bit 2 cos this will be 2 in base 10

  for (uint32_t i = 2; i < sqrtl(bv_get_len(v)); i += 1) {
    // Prime means bit is set
    if (bv_get_bit(v, i)) {

      for (uint32_t k = 0; (k + i) * i <= bv_get_len(v); k += 1) {
        bv_clr_bit(v, (k + i) * i); // clear the bit
      }
    }
  }
  return;
}

/* Sieve of Sundaram
    https://www.sanfoundry.com/c-program-generate-prime-numbers-between-given-range-using-sieve-sundaram/
*/

/* sieve of Atkin
    https://www.sanfoundry.com/c-program-implement-sieve-atkin-generate-prime-numbers-between-given-range/#:~:text=The%20sieve%20of%20Atkin%20is,multiples%20of%20the%20prime%20itself.
*/

/*
Ref: https://www.codesdope.com/blog/article/prime-numbers-using-sieve-algorithm-in-c/#:~:text=C%20Code%20for%20Sieve%20algorithm&text=%7D%20return%200%3B%20%7D-,for(i%20%3D%202%3B%20i%3C%3Dnumber%3B%20i,the%20number%20'i'%200.


algorithm Sieve of Eratosthenes is
    input: an integer n > 1.
    output: all prime numbers from 2 through n.

    let A be an array of Boolean values, indexed by integers 2 to n,
    initially all set to true.
    
    for i = 2, 3, 4, ..., not exceeding √n do
        if A[i] is true
            for j = i2, i2+i, i2+2i, i2+3i, ..., not exceeding n do
                A[j] := false

    return all i such that A[i] is true.
*/

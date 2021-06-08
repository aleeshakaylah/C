#include "bv.h"
#include <stdio.h>
#include <stdlib.h>

//
// Creates a new BitVector of specified length.
//
// bit_len : The length in bits of the BitVector.
//
BitVector *bv_create(uint32_t bit_len) {
  int rows = (bit_len + 7) / 8;

  BitVector *bv = (BitVector *)malloc(sizeof(BitVector));

  // error checking
  if (bv == NULL) {
    printf("Malloc Error");
    return 0;
  }

  bv->length = bit_len;
  bv->vector = (uint8_t *)calloc(rows, sizeof(uint8_t));

  if (bv->vector == NULL) {
    free(bv->vector);
    free(bv);
    printf("Calloc Error");
  }
  return bv;
}

//
// Frees memory allocated for a BitVector.
//
// v : The BitVector.
//
void bv_delete(BitVector *v) {
  free(v->vector);
  v->vector = NULL;
  free(v);
}

//
// Returns the length in bits of the BitVector.
//
// v : The BitVector.
//
uint32_t bv_get_len(BitVector *v) {
  return (v->length);
}

//
// Sets the bit at index in the BitVector.
//
// v : The BitVector.
// i : Index of the bit to set.
//
void bv_set_bit(BitVector *v, uint32_t i) {
  v->vector[i / 8] |= (0x1 << (i % 8));
  return;
}

//
// Clears the bit at index in the BitVector.
//
// v : The BitVector.
// i : Index of the bit to clear.
//
void bv_clr_bit(BitVector *v, uint32_t i) {
  v->vector[i / 8] &= ~(0x1 << (i % 8));
}

//
// Gets a bit from a BitVector.
//
// v : The BitVector.
// i : Index of the bit to get.
//
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  return (((v->vector[i / 8]) >> (i % 8)) & 0x1);
}

//
// Sets all bits in a BitVector.
//
// v : The BitVector.
//
void bv_set_all_bits(BitVector *v) {
  for (uint32_t i = 0; i < v->length; i++) {
    bv_set_bit(v, i);
  }
}

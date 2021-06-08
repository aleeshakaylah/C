#include "bv.h"
#include <stdio.h>
#include <stdlib.h>

//
// Creates a new BitVector of specified length.
//
// bit_len : The length in bits of the BitVector.
//
BitVector *bv_create(uint32_t bit_len) {

  BitVector *bv = (BitVector *)malloc(sizeof(BitVector));
  if (bit_len % 8 == 0) {
    byte_count = bit_len / 8;
    remaining_bits = 0;
  } else {
    byte_count = bit_len / 8 + 1;
    remaining_bits = bit_len % 8;
  }

  bv->vector = (uint8_t *)(malloc(sizeof(uint8_t) * byte_count));

  for (int i = 0; i < byte_count; i++) {
    bv->vector[i] = 0x0;
  };

  bv->length = bit_len;

  return bv;
}

//
// Frees memory allocated for a BitVector.
//
// v : The BitVector.
//
void bv_delete(BitVector *v) {
  free(v->vector);
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
  int num_bytes = i / 8;
  int num_bits = i % 8;
  uint8_t byte;
  //printf("%d %d\n",num_bytes, num_bits);

  if (i < v->length) {
    if (num_bits == 0) {
      byte = v->vector[num_bytes];
      byte = byte | 0x01;
      v->vector[num_bytes] = byte;
    } else {
      uint8_t mask = 0x01;
      mask = mask << num_bits;
      byte = v->vector[num_bytes];
      // printf("%d %d\n",byte, mask);

      byte = byte | mask;
      v->vector[num_bytes] = byte;
    }
  }
}

//
// Clears the bit at index in the BitVector.
//
// v : The BitVector.
// i : Index of the bit to clear.
//
void bv_clr_bit(BitVector *v, uint32_t i) {
  int num_bytes = i / 8;
  int num_bits = i % 8;
  uint8_t byte;
  //printf("%d %d\n",num_bytes, num_bits);
  if (i < v->length) {
    if (num_bits == 0) {
      byte = v->vector[num_bytes];
      byte = byte | 0x01;
      v->vector[num_bytes] = byte;
    } else {
      uint8_t mask = 0x01;
      mask = mask << num_bits;
      mask = ~mask;
      byte = v->vector[num_bytes];
      byte = byte & mask;
      v->vector[num_bytes] = byte;
    }
  }
}

//
// Gets a bit from a BitVector.
//
// v : The BitVector.
// i : Index of the bit to get.
//
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  int num_bytes = i / 8;
  int num_bits = i % 8;
  uint8_t byte;

  if (i < v->length) {
    if (num_bits == 0) {
      byte = v->vector[num_bytes];
      byte = byte | 0x01;
    } else {
      uint8_t mask = 0x01;
      mask = mask << num_bits;
      byte = v->vector[num_bytes];
      byte = byte & mask;
      //printf("%d 0x%02x 0x%02x\n",i, mask, byte);
    }
  }
  return byte;
}
//
// Sets all bits in a BitVector.
//
// v : The BitVector.
//
void bv_set_all_bits(BitVector *v) {
  int i;
  for (i = 0; i < byte_count; i++) {
    v->vector[i] = 0xFF;
  }

  uint8_t mask = 0x01;
  uint8_t result = 0x0;
  if (remaining_bits != 0) {
    for (i = 0; i < remaining_bits; i++) {
      result = result | mask;
      mask = mask << 1;
    }
    v->vector[byte_count - 1] = result;
  }
}

// Print out bit vector, useful for debug
void bv_print_bytes(BitVector *v) {

  printf("bv->length %d\n", v->length);

  for (int i = 0; i < byte_count; i++) {
    //uint8_t dstEndPt = v->vector[i];
    printf("vector[%d]  = 0x%02x \n", i, v->vector[i]);
    printf("vector[%d]  = %d \n", i, v->vector[i]);
  }
}

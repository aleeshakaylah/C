#include "bf.h"
#include "bv.h"
#include "hs.h"
#include "speck.h"
#include <stdlib.h>

extern double bf_num_set;
//
//  Constructor  for a BloomFilter.
//
// 	size:   The  number  of  entries  in the  BloomFilter.
//
BloomFilter *bf_create(uint32_t size) {
  BloomFilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter));
  if (bf) {
    bf->primary[0] = 0xfc28ca6885711cf7;
    bf->primary[1] = 0x2841af568222f773;
    bf->secondary[0] = 0x85ae998311115ae3;
    bf->secondary[1] = 0xb6fac2ae33a40089;
    bf->tertiary[0] = 0xd37b01df0ae8f8d0;
    bf->tertiary[1] = 0x911d454886ca7cf7;
    bf->filter = bv_create(size);
    return bf;
  }
  return (BloomFilter *)NIL;
}

//
//  Destructor for a BloomFilter.
//
//	bf:	The  BloomFilter.
//
void bf_delete(BloomFilter *bf) {
  bv_delete(bf->filter);
  free(bf);
}

//
//  Inserts a new key into the BloomFilter.
//  Indices to set bits are given by the hash functions.
//
// 	bf:     The  BloomFilter.
// 	key:    The  key to  insert  into  the  BloomFilter.
//
void bf_insert(BloomFilter *bf, char *key) {
  uint32_t index_one = hash(bf->primary, key) % bf->filter->length;
  uint32_t index_two = hash(bf->secondary, key) % bf->filter->length;
  uint32_t index_three = hash(bf->tertiary, key) % bf->filter->length;
  bv_set_bit(bf->filter, index_one);
  bv_set_bit(bf->filter, index_two);
  bv_set_bit(bf->filter, index_three);

  if (bv_get_bit(bf->filter, index_one) == 1) {
    bf_num_set++;
  }
  if (bv_get_bit(bf->filter, index_two) == 1) {
    bf_num_set++;
  }
  if (bv_get_bit(bf->filter, index_three) == 1) {
    bf_num_set++;
  }
}

//
//  Probes a BloomFilter to check if a key has been inserted.
//
// bf:     The BloomFilter.
// key:    The key in which to check membership.
//
bool bf_probe(BloomFilter *bf, char *key) {
  uint32_t index_one = hash(bf->primary, key) % bf->filter->length;
  uint32_t index_two = hash(bf->secondary, key) % bf->filter->length;
  uint32_t index_three = hash(bf->tertiary, key) % bf->filter->length;

  bool flag
      = (bv_get_bit(bf->filter, index_one) && bv_get_bit(bf->filter, index_two)
          && bv_get_bit(bf->filter, index_three));

  return flag;
}

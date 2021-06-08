#include "hash.h"

//  Constructor  for a HashTable.
//
//  length:   Length  of the  HashTable.
// 	salt:     Salt  for the  HashTable.
//
HashTable *ht_create(uint32_t length) {
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  if (ht) {
    ht->salt[0] = 0x85ae998311115ae3;
    ht->salt[1] = 0xb6fac2ae33a40089;
    ht->length = length;
    ht->heads = (ListNode **)calloc(length, sizeof(ListNode *));
    return ht;
  }
  return (HashTable *)NIL;
}

//
//  Destructor  for a HashTable.
//
// 	ht:   The  HashTable.
//
void ht_delete(HashTable *ht) {
  for (uint32_t i = 0; i <= ht->length; i++) {
    if (ht->heads[i] != NULL) {
      ll_delete(ht->heads[i]);
    }
  }
  free(ht->heads);
  free(ht);
}

//
//  Returns number of entries in hash table
//
// 	h: The HashTable.
//
uint32_t ht_count(HashTable *h) {
  uint32_t count = 0;

  for (uint32_t i = 0; i <= h->length; i++) {
    if (h->heads[i] != NULL) {
      count++;
    }
  }
  return count;
}

//
//  Searches a HashTable  for a key.
//  Returns  the  ListNode  if found  and  returns  NULL  otherwise.
// 	This  should  call  the  ll_lookup()  function.
//
// 	ht:    The  HashTable.
// 	key:   The key to  search  for.
//
ListNode *ht_lookup(HashTable *ht, char *key) {
  uint32_t index = hash(ht->salt, key) % ht->length;
  return ll_lookup(&ht->heads[index], key);
}

//
//	First  creates a new  ListNode  from  HatterSpeak.
// 	The  created  ListNode  is then  inserted  into a HashTable.
// 	This  should  call  the  ll_insert ()  function.
//
// 	ht:	The HashTable.
// 	gs:	The HatterSpeak to add to the HashTable.
//
void ht_insert(HashTable *ht, HatterSpeak *gs) {
  uint32_t index = hash(ht->salt, gs->oldspeak) % ht->length;
  if (ll_lookup(&ht->heads[index], gs->oldspeak)) {
    return;
  }
  ht->heads[index] = ll_insert(&ht->heads[index], gs);
}

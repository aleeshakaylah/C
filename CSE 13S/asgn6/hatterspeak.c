#include "bf.h"
#include "bv.h"
#include "hash.h"
#include "hs.h"
#include "ll.h"
#include "parser.h"
#include "speck.h"
#include <ctype.h>
#include <getopt.h>
#include <math.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

bool move_to_front = false;
double seeks, links, links_searched, bf_num_set;

int main(int argc, char **argv) {

  uint32_t ht_size = 10000, bf_size = pow(2, 20);
  int c = 0, statistics = 0;

  // 1. getopt
  while ((c = getopt(argc, argv, "sh:f:mb")) != -1) {
    switch (c) {
    case 's':
      statistics = 1;
      break;
    case 'h':
      ht_size = atoi(optarg);
      break;
    case 'f':
      bf_size = atoi(optarg);
      break;
    case 'm':
      move_to_front = true;
      break;
    case 'b':
      move_to_front = false;
      break;
    }
  }

  // 2. create bloomfilter and hash table
  BloomFilter *bf = bf_create(bf_size);
  HashTable *ht = ht_create(ht_size);

  // 3. populate bf and ht with .txts
  // for oldspeak.txt
  FILE *old;
  old = fopen("oldspeak.txt", "r");

  char oldspeak[100];

  while (fscanf(old, "%s\n", oldspeak) != EOF) {
    bf_insert(bf, oldspeak);
    // create hatterspeak using eachword and insert to ht
    HatterSpeak *hs = hs_create(oldspeak, NULL);
    ht_insert(ht, hs);
  }

  fclose(old);

  // for hatterspeak.txt
  FILE *hat;
  hat = fopen("hatterspeak.txt", "r");
  char hatterspeak[100];

  while (fscanf(hat, "%s %s\n", oldspeak, hatterspeak) != EOF) {
    bf_insert(bf, oldspeak);
    HatterSpeak *hs = hs_create(oldspeak, hatterspeak);
    ht_insert(ht, hs);
  }

  fclose(hat);

  // 4. Regular expression

  // REGULAR EXPRESSION STUFF FOR PARSER.C
  // REFERENCE: https://www.youtube.com/watch?v=sa-TUpSx1JA&ab_channel=CoreySchafer
  regex_t word_regex;

  if (regcomp(&word_regex, "[a-zA-Z0-9]+(('|-)?[a-zA-Z0-9_])?", REG_EXTENDED)) {
    printf("Expression was wrong.");
    return 0;
  }

  ListNode *nonsense = NULL; // forbidden
  ListNode *translated = NULL; // has translation

  char *my_word = NULL;

  while ((my_word = next_word(stdin, &word_regex)) != NULL) {

    for (uint32_t i = 0; i <= strlen(my_word); i++) {
      my_word[i] = tolower(my_word[i]);
    }

    if (bf_probe(bf, my_word) != 0) {
      ListNode *node = ht_lookup(ht, my_word);
      if (node == NULL) {
        continue;
      } else {
        HatterSpeak *hs = hs_create(node->gs->oldspeak, node->gs->hatterspeak);
        if (node->gs->hatterspeak != NULL) {
          ll_insert(&translated, hs);
        } else {
          ll_insert(&nonsense, hs);
        }
      }

    } else {
      continue;
    }
  }

  // 5. Printing Stage
  if (statistics == 1) {
    printf("Seeks: %.0f\n", seeks);
    printf("Average Seek Length: %f\n", (links_searched / seeks));
    printf("Average Linked List Length: %f\n", (links / ht->length));
    printf("Hash Table Load %f%%\n",
        (100 * ((double)(ht_count(ht)) / (double)(ht->length))));
    printf("Bloom Filter Load: %f%%\n", (100 * (bf_num_set / bf_size)));
  } else {
    if (translated && nonsense) {
      printf("\nDear Comrade,\nYou have chosen to use words that the queen has "
             "decreed oldspeak.\nDue to your infraction you will be sent to "
             "the dungeon where you will\n\tbe taught hatterspeak.\n");

      printf("\nYour errors:\n");

      printf("\n");

      ll_print(nonsense);

      printf("\nAppropriate hatterspeak translations.\n");

      printf("\n");

      ll_print(translated);

    } else if (translated) {
      printf("\nDear Wonderlander,\nThe decree for hatterspeak finds your "
             "message lacking. Some of the\n\twords that you used are not "
             "hatterspeak.\n");

      printf(
          "The list shows how to turn the oldspeak words into hatterspeak.\n");

      printf("\n");

      ll_print(translated);

    } else if (nonsense) {
      printf("\nDear Wonderlander,\nYou have chosen to use words that the "
             "queen has decreed oldspeak.\nDue to your infraction you will be "
             "sent to the dungeon where you will\n\tbe taught hatterspeak.\n");

      printf("\nYour errors:\n");

      printf("\n");

      ll_print(nonsense);
    }
  }

  // freeing memory
  bf_delete(bf);
  ht_delete(ht);
  ll_delete(nonsense);
  ll_delete(translated);
  regfree(&word_regex);

  return 0;
}

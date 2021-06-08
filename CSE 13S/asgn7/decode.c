#include "code.h"
#include "io.h"
#include "trie.h"
#include "word.h"

#include <fcntl.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Pseudocode from Eugene Chou & Oly Kebede

// global vars for stats
uint64_t total_syms, total_bits;

uint8_t bit_length(uint16_t value) {
  uint8_t length;
  length = log2(value) + 1;
  return length;
}

int main(int argc, char **argv) {
  int c = 0, statistics = 0, infile = STDIN_FILENO, outfile = STDOUT_FILENO;

  // 1. getopt
  while ((c = getopt(argc, argv, "vi:o:")) != -1) {
    switch (c) {
    case 'v':
      statistics = 1;
      break;
    case 'i':
      infile = open(optarg, O_RDONLY);
      if (infile < 0) {
        printf("File input error.\n");
        return 0;
      }
      break;
    case 'o':
      outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
      if (outfile < 0) {
        printf("File output error.\n");
        return 0;
      }
      break;
    }
  }

  if (statistics) {
    uint64_t ratio = 100 * (1 - (total_syms / total_bits));
    printf("Compressed file size: %ld bytes\n", total_syms);
    printf("Uncompressed file size: %ld bytes\n", total_bits);
    printf("Compression ratio: %.2ld bytes\n", ratio);
  }

  FileHeader fh;
  read_header(infile, &fh);

  if (fh.magic != 0x8badbeef) {
    printf("Magic number error.\n");
    return 0;
  }

  fchmod(outfile, fh.protection);

  // Use Deompression Algorithm Pseudocode
  WordTable *table;
  uint16_t curr_sym, curr_code, next_code;

  table = wt_create();
  curr_sym = 0;
  curr_code = 0;
  next_code = START_CODE;

  while (read_pair(infile, &curr_code, &curr_sym, bit_length(next_code))) {
    table[next_code] = word_append_sym(table[curr_code], curr_sym);
    buffer_word(outfile, table[next_code]);
    next_code = next_code + 1;
    if (next_code == MAX_CODE) {
      wt_reset(table);
      next_code = START_CODE;
    }
  }
  flush_words(outfile);

  wt_delete(table);
}

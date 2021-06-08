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
    uint64_t ratio = 100 * (1 - (total_bits / total_syms));
    printf("Compressed file size: %ld bytes\n", total_bits);
    printf("Uncompressed file size: %ld bytes\n", total_syms);
    printf("Compression ratio: %.2ld bytes\n", ratio);
  }

  // Create new FileHeader type
  FileHeader fh;
  fh.magic = 0x8badbeef;

  // struct for protection
  struct stat header_p;
  fstat(infile, &header_p);
  fh.protection = header_p.st_mode;

  fchmod(outfile, fh.protection);

  write_header(outfile, &fh);

  // Use Compression Algorithm Pseudocode
  TrieNode *root, *curr_node, *prev_node, *next_node;
  uint16_t curr_sym, prev_sym, next_code;

  root = trie_create();
  curr_node = root;
  prev_node = NULL;
  curr_sym = 0;
  prev_sym = 0;

  next_code = START_CODE;
  while (read_sym(infile, &curr_sym)) {
    next_node = trie_step(curr_node, curr_sym);
    if (next_node != NULL) {
      prev_node = curr_node;
      curr_node = next_node;
    } else {
      buffer_pair(outfile, curr_node->code, curr_sym, bit_length(next_code));
      curr_node->children[curr_sym] = trie_node_create(next_code);
      curr_node = root;
      next_code = next_code + 1;
    }
    if (next_code == MAX_CODE) {
      trie_reset(root);
      curr_node = root;
      next_code = START_CODE;
    }
    prev_sym = curr_sym;
  }
  if (curr_node != root) {
    buffer_pair(outfile, prev_node->code, prev_sym, bit_length(next_code));
    next_code = (next_code + 1) % MAX_CODE;
  }
  buffer_pair(outfile, STOP_CODE, 0, bit_length(next_code));
  flush_pairs(outfile);

  trie_delete(root);
}

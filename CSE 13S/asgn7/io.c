#include "io.h"

// Pseudocode from Eugene Chou & Oly Kebed

static uint8_t sym_buf[4096]; // 4096 was BLOCK
static uint8_t bit_buf[4096];
static int sym_index;
static int bit_index;

//
// Wrapper for the read() syscall.
// Loops to read the specified number of bytes, or until input is exhausted.
// Returns the number of bytes read.
//
// infile:  File descriptor of the input file to read from.
// buf:     Buffer to store read bytes into.
// to_read: Number of bytes to read.
// returns: Number of bytes read.
//
int read_bytes(int infile, uint8_t *buf, int to_read) {
  int r_bytes = 0;
  int total = 0;
  do {
    r_bytes = read(infile, buf + total, to_read - total);
    total += r_bytes;
    //total_bits++;
  } while (r_bytes > 0 && total != to_read);
  return total;
}

//
// Wrapper for the write() syscall.
// Loops to write the specified number of bytes, or until nothing is written.
// Returns the number of bytes written.
//
// outfile:   File descriptor of the output file to write to.
// buf:       Buffer that stores the bytes to write out.
// to_write:  Number of bytes to write.
// returns:   Number of bytes written.
//
int write_bytes(int outfile, uint8_t *buf, int to_write) {
  int w_bytes = 0;
  int total = 0;
  do {
    w_bytes = write(outfile, buf + total, to_write - total);
    total += w_bytes;
    //total_syms++;
  } while (w_bytes > 0 && total != to_write);
  return total;
}

//
// Reads in a FileHeader from the input file.
//
// infile:  File descriptor of input file to read header from.
// header:  Pointer to memory where the bytes of the read header should go.
// returns: Void.
//
void read_header(int infile, FileHeader *header) {
  // Error Checking
  // if(read(infile, header, sizeof(FileHeader)) < 0){
  //	printf("File read error.\n");
  //}

  total_syms += 1;

  read_bytes(infile, (uint8_t *)header, sizeof(FileHeader));
  return;
}

//
// Writes a FileHeader to the output file.
//
// outfile: File descriptor of output file to write header to.
// header:  Pointer to the header to write out.
// returns: Void.
//
void write_header(int outfile, FileHeader *header) {
  // Error Checking
  //if (write(outfile, header, sizeof(FileHeader)) < 0){
  //	printf("File write error");
  //}

  total_bits += (8 * sizeof(FileHeader)); // stats

  write_bytes(outfile, (uint8_t *)header, sizeof(FileHeader));
  return;
}

//
// "Reads" a symbol from the input file.
// The "read" symbol is placed into the pointer to sym (pass by reference).
// In reality, a block of symbols is read into a buffer.
// An index keeps track of the currently read symbol in the buffer.
// Once all symbols are processed, another block is read.
// If less than a block is read, the end of the buffer is updated.
// Returns true if there are symbols to be read, false otherwise.
//
// infile:  File descriptor of input file to read symbols from.
// sym:     Pointer to memory which stores the read symbol.
// returns: True if there are symbols to be read, false otherwise.
//

bool read_sym(int infile, uint16_t *byte) {
  total_syms += 1; // stats
  static int num_read = 0;
  static bool check;
  //uint16_t temp;

  if (sym_index == 0) {
    // number of bytes read
    num_read = read_bytes(infile, sym_buf, 4096);
  }
  // increment byte index
  *byte = sym_buf[sym_index++];

  // if the index reaches the end, we send it back to the beginning
  if (sym_index == 4096) {
    sym_index = 0;
  }

  // If 4096, bytes left to read so return true
  if (num_read == 4096) {
    check = true;
  } else {
    // If sym_index is num_read + 1, reached end
    if (sym_index == num_read + 1) {
      check = false;
    } else {
      check = true;
    }
  }
  return check;
}

//
// Buffers a pair. A pair is comprised of a symbol and an index.
// The bits of the symbol are buffered first, starting from the LSB.
// The bits of the index are buffered next, also starting from the LSB.
// bit_len bits of the index are buffered to provide a minimal representation.
// The buffer is written out whenever it is filled.
//
// outfile: File descriptor of the output file to write to.
// sym:     Symbol of the pair to buffer.
// index:   Index of the pair to buffer.
// bit_len: Number of bits of the index to buffer.
// returns: Void.
//
void buffer_pair(int outfile, uint16_t code, uint16_t sym, uint8_t bit_len) {
  total_bits += bit_len + 8; // stats

  // buffering the bits of the index
  for (int j = 0; j < bit_len; j++) {
    if ((code & 1) == 1) {
      // set bit (bit_buf, bit_index)
      bit_buf[bit_index / 8] |= (0x1 << (bit_index % 8));

      bit_buf[bit_index / 8] |= (1 << (bit_index % 8));
    } else {
      // clear bit (bit_buf, bit_index)
      bit_buf[bit_index / 8] &= ~(0x1 << (bit_index % 8));

      bit_buf[bit_index / 8] &= ~(1 << (bit_index % 8));
    }
    bit_index += 1;
    code >>= 1;

    if (bit_index == 4096 * 8) {
      write_bytes(outfile, bit_buf, 4096);
      bit_index = 0;
    }
  }

  // buffering the bits of the symbol
  for (int i = 0; i < 8; i++) {
    if ((sym & 1) == 1) {
      // set bit (bit_buf, bit_index)
      bit_buf[bit_index / 8] |= (0x1 << (bit_index % 8));

      bit_buf[bit_index / 8] |= (1 << (bit_index % 8));
    } else {
      // clear bit (bit_buf, bit_index)
      bit_buf[bit_index / 8] &= ~(0x1 << (bit_index % 8));

      bit_buf[bit_index / 8] &= ~(1 << (bit_index % 8));
    }

    bit_index += 1;
    sym >>= 1;

    if (bit_index == 4096 * 8) {
      write_bytes(outfile, bit_buf, 4096);
      bit_index = 0;
    }
  }
}

//
// Writes out any remaining pairs of symbols and indexes to the output file.
//
// outfile: File descriptor of the output file to write to.
// returns: Void.
//
void flush_pairs(int outfile) {
  int bytes;
  if (bit_index != 0) {
    if (bit_index % 8 == 0) {
      bytes = bit_index / 8;
    } else {
      bytes = (bit_index / 8) + 1;
    }
    write_bytes(outfile, bit_buf, bytes);
  }
}

//
// "Reads" a pair (symbol and index) from the input file.
// The "read" symbol is placed in the pointer to sym (pass by reference).
// The "read" index is placed in the pointer to index (pass by reference).
// In reality, a block of pairs is read into a buffer.
// An index keeps track of the current bit in the buffer.
// Once all bits have been processed, another block is read.
// The first 8 bits of the pair constitute the symbol, starting from the LSB.
// The next bit_len bits constitutes the index, starting from the the LSB.
// Returns true if there are pairs left to read in the buffer, else false.
// There are pairs left to read if the read index is not STOP_INDEX.
//
// infile:  File descriptor of the input file to read from.
// sym:     Pointer to memory which stores the read symbol.
// index:   Pointer to memory which stores the read index.
// bit_len: Length in bits of the index to read.
// returns: True if there are pairs left to read, false otherwise.
//

bool read_pair(int infile, uint16_t *code, uint16_t *sym, uint8_t bit_len) {
  // zero out code so leftover bits are removed
  *code = 0;

  // read index pairs
  for (uint32_t j = 0; j < bit_len; j++) {
    if (bit_index == 0) {
      read_bytes(infile, bit_buf, 4096);
    }
    // get bit and see if it equals 1
    if (bit_buf[bit_index / 8] >> (bit_index % 8) & (0x1)) {
      // set bit
      *code |= (0x1 << j);
    } else {
      // clear bit
      *code &= ~(0x1 << j);
    }
    bit_index += 1;

    if (bit_index == (4096 * 8)) {
      bit_index = 0;
    }
  }

  // read symbol pairs
  for (uint32_t i = 0; i < 8; i++) {

    if (bit_index == 0) {
      read_bytes(infile, bit_buf, 4096);
    }
    // get bit and see if it equals 1
    if (bit_buf[bit_index / 8] >> (bit_index % 8) & (0x1)) {
      // set bit
      *sym |= (0x1 << i);
    } else {
      // clear bit
      *sym &= ~(0x1 << i);
    }
    bit_index += 1;

    if (bit_index == (4096 * 8)) {
      bit_index = 0;
    }
  }

  // if code is not at the end
  if (*code != STOP_CODE) {
    return true;
  } else {
    return false;
  }
}

//
// Buffers a Word, or more specifically, the symbols of a Word.
// Each symbol of the Word is placed into a buffer.
// The buffer is written out when it is filled.
//
// outfile: File descriptor of the output file to write to.
// w:       Word to buffer.
// returns: Void.
//
void buffer_word(int outfile, Word *w) {
  int total_bits = 0;
  for (uint32_t i = 0; i < w->len; i++) {
    sym_buf[sym_index++] = w->syms[i];
    if (sym_index == 4096) {
      write_bytes(outfile, sym_buf, 4096);
      sym_index = 0;
    }
  }
  total_bits += 8 * w->len;
}

//
// Writes out any remaining symbols in the buffer.
//
// outfile: File descriptor of the output file to write to.
// returns: Void.
//
void flush_words(int outfile) {
  if (sym_index != 0) {
    write_bytes(outfile, sym_buf, sym_index);
    sym_index = 0;
  }
}

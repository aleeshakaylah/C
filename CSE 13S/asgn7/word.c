#include "word.h"

// Pseudocode from Eugene Chou & Oly Kebede
//
// Constructor for a word.
//
// syms:    Array of symbols a Word represents.
// len:     Length of the array of symbols.
// returns: Pointer to a Word that has been allocated memory.
//
Word *word_create(uint8_t *syms, uint32_t len) {
  // allocate memory for word
  Word *w = (Word *)malloc(sizeof(Word));

  // allocate enough memory for word->syms length * something
  w->syms = calloc(1, sizeof(uint8_t *) * len);

  // initialize length
  w->len = len;

  // fill syms
  for (uint32_t i = 0; i <= len; i++) {
    w->syms[i] = syms[i];
  }

  // or memcpy(word->syms, syms, len);

  return w;
}

//
// Constructs a new Word from the specified Word appended with a symbol.
// The Word specified to append to may be empty.
// If the above is the case, the new Word should contain only the symbol.
//
// w:       Word to append to.
// sym:     Symbol to append.
// returns: New Word which represents the result of appending.
//
Word *word_append_sym(Word *w, uint8_t sym) {
  // check if word exists
  if (w->len) {
    // allocate memory for new word
    Word *nw = (Word *)malloc(sizeof(Word));

    // allocate memory for new word->syms
    nw->syms = calloc(1, w->len + 1);

    // add symbols to new word
    for (uint32_t i = 0; i <= w->len; i++) {
      nw->syms[i] = w->syms[i];
    }

    // add appended sym to word
    nw->syms[w->len] = sym;

    // increase length of new word
    nw->len = w->len + 1;

    return nw;
  } else {
    return word_create(&sym, 1);
  }
}

//
// Destructor for a Word.
//
// w:       Word to free memory for.
// returns: Void.
//
void word_delete(Word *w) {
  free(w->syms);
  free(w);
}

//
// Creates a new WordTable, which is an array of Words.
// A WordTable has a pre-defined size of MAX_CODE (UINT16_MAX - 1).
// This is because codes are 16-bit integers.
// A WordTable is initialized with a single Word at index EMPTY_CODE.
// This Word represents the empty word, a string of length of zero.
//
// returns: Initialized WordTable.
//
WordTable *wt_create(void) {
  WordTable *wt = calloc(MAX_CODE, sizeof(WordTable));
  wt[EMPTY_CODE] = (Word *)calloc(1, sizeof(Word));

  return wt;
}

//
// Resets a WordTable to having just the empty Word.
//
// wt:      WordTable to reset.
// returns: Void.
//
void wt_reset(WordTable *wt) {
  // doesn't free root node
  for (int i = START_CODE; i < MAX_CODE; i++) {
    if (wt[i]) {
      word_delete(wt[i]);
    }
  }
  return;
}

//
// Deletes an entire WordTable.
// All Words in the WordTable must be deleted as well.
//
// wt:      WordTable to free memory for.
// returns: Void.
//
void wt_delete(WordTable *wt) {
  // frees everything, including root node
  for (uint32_t i = 0; i < MAX_CODE; i++) {
    if (wt[i] != NULL) {
      word_delete(wt[i]);
    }
  }
  return;
}

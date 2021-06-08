#include "trie.h"

// Pseudocode from Eugene Chou & Oly Kebede

//
// Constructor for a TrieNode.
//
// index:   Index of the constructed TrieNode.
// returns: Pointer to a TrieNode that has been allocated memory.
//
TrieNode *trie_node_create(uint16_t index) {
  TrieNode *n = (TrieNode *)calloc(1, sizeof(TrieNode));
  n->code = index;

  return n;
}

//
// Destructor for a TrieNode.
//
// n:		TrieNode to free allocated memory for.
// returns: Void.
//
void trie_node_delete(TrieNode *n) {
  free(n);
}

//
// Initializes a Trie: a root TrieNode with the index EMPTY_CODE.
//
// returns: Pointer to the root of a Trie.
//
TrieNode *trie_create(void) {
  return trie_node_create(EMPTY_CODE);
}

//
// Resets a Trie to just the root TrieNode.
//
// root:    Root of the Trie to reset.
// returns: Void.
//
void trie_reset(TrieNode *root) {
  // doesn't free root node
  for (uint32_t i = 0; i <= sizeof(root->children); i++)
    trie_delete(root->children[i]);
}

//
// Deletes a sub-Trie starting from the sub-Trie's root.
//
// n:       Root of the sub-Trie to delete.
// returns: Void.
//
void trie_delete(TrieNode *n) {
  // checks if there are children
  if (n == NULL) {
    return; // nothing to free
  }

  // else free children
  for (int i = 0; i < 256; i++) {
    trie_delete(n->children[i]);
  }

  // free the node itself
  trie_node_delete(n);
}

//
// Returns a pointer to the child TrieNode reprsenting the symbol sym.
// If the symbol doesn't exist, NULL is returned.
//
// n:       TrieNode to step from.
// sym:     Symbol to check for.
// returns: Pointer to the TrieNode representing the symbol.
//
TrieNode *trie_step(TrieNode *n, uint8_t sym) {
  // If null, return null
  if (n->children[sym] == NULL) {
    return NULL;
  } else { // Else, return pointer to the child of that symbol
    return n->children[sym];
  }
}

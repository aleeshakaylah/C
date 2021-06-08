#include "hs.h"

//
//	Constructor for a HatterSpeak Node
//
//	old = oldspeak words being read in
//	hatter = hatterspeak words being read in
//
HatterSpeak *hs_create(char *old, char *hatter) {
  HatterSpeak *gs = (HatterSpeak *)calloc(1, sizeof(HatterSpeak));

  if (old != NULL) {
    gs->oldspeak = strcpy(malloc(strlen(old) + 1), old);
    if (hatter != NULL) {
      gs->hatterspeak = strcpy(malloc(strlen(hatter) + 1), hatter);
    }
  }
  return gs;
}

//
//  Destructor for a HatterSpeak node.
//
//	gs:	The HatterSpeak node.
//
void hs_delete(HatterSpeak *gs) {
  free(gs->oldspeak);
  if (gs->hatterspeak != NULL) {
    free(gs->hatterspeak);
  }
  free(gs);
}

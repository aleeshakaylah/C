#ifndef __HS_H__
#define __HS_H__

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//create struct
typedef struct HatterSpeak {
  char *oldspeak;
  char *hatterspeak;
} HatterSpeak;

//
//	Constructor for a HatterSpeak Node
//
//	old = oldspeak words being read in
//	hatter = hatterspeak words being read in
//
HatterSpeak *hs_create(char *old, char *hatter);

//
//  Destructor for a HatterSpeak node.
//
//	gs:	The HatterSpeak node.
//
void hs_delete(HatterSpeak *gs);

#endif

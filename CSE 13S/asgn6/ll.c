#include "ll.h"

extern bool move_to_front;
extern double seeks, links, links_searched;

//
//	Constructor for a ListNode.
//
//	gs: HatterSpeak struct containing oldspeak and its hatterspeak translation.
//
ListNode *ll_node_create(HatterSpeak *gs) {
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  node->gs = gs;
  node->next = NULL;
  return node;
}

//
//	Destructor for a ListNode.
//
//	n: The ListNode to free.
//
void ll_node_delete(ListNode *n) {
  hs_delete(n->gs);
  free(n);
}

//
//	Destructor for a linked list of ListNodes.
//
// 	head:	The head of the linked list.
//
void ll_delete(ListNode *head) {
  ListNode *curr, *temp;
  curr = head;
  while (curr != NULL) {
    temp = curr->next;
    ll_node_delete(curr);
    curr = temp;
  }
}

//
// 	Creates  and  inserts a ListNode  into a linked  list.
//
// 	head:   The  head of the  linked  list to  insert  in.
// 	gs:     HatterSpeak  struct.
//
ListNode *ll_insert(ListNode **head, HatterSpeak *gs) {
  if (ll_lookup(head, gs->oldspeak)) {
    hs_delete(gs);
    return *head;
  } else {
    if (*head == NULL) {
      *head = ll_node_create(gs);
      links++;
      return *head;
    } else {
      ListNode *n = ll_node_create(gs);
      n->next = *head;
      *head = n;
      links++;
      return *head;
    }
  }
}

//
//  Searches  for a specific  key in a linked  list.
//  Returns  the  ListNode  if found  and  NULL  otherwise.
//
// 	head:    The  head of the  linked  list to  search  in.
// 	key:     The key to  search  for.
ListNode *ll_lookup(ListNode **head, char *key) {
  seeks++;
  ListNode *curr, *prev;
  curr = *head;
  prev = NULL;

  while (curr != NULL) {
    if (strcmp(curr->gs->oldspeak, key) == 0) {
      if (move_to_front && prev != NULL) {
        prev->next = curr->next;
        curr->next = *head;
        *head = curr;
        links_searched++;
        return *head;
      }
      links_searched++;
      return curr;
    }
    prev = curr;
    curr = curr->next;
  }
  // If you reach the end of the list and strcmp != 0, return NULL
  return NULL;
}

void ll_print(ListNode *head) {
  ListNode *curr, *temp;
  curr = head;
  while (curr != NULL) {
    temp = curr->next;
    if (curr->gs->hatterspeak == NULL) {
      printf("%s\n", curr->gs->oldspeak);
    } else {
      printf("%s -> %s\n", curr->gs->oldspeak, curr->gs->hatterspeak);
    }
    curr = temp;
  }
}

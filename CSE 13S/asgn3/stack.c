
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack *stack_create(int capacity, char name) {
  // Memory allocation for stack
  Stack *s = (Stack *)malloc(sizeof(Stack));

  if (!s) {
    return 0; //Did not get memory allocated for stack
  }
  if (capacity < 1) {
    capacity = 1; // Intializing capacity if no disks are placed
  }

  // Initializing capacity, name, and top
  s->capacity = capacity;
  s->name = name;
  s->top = 0;

  // Memory allocation for items
  s->items = (int *)(malloc(sizeof(int) * capacity));

  if (!s->items) {
    return 0; //Did not get memory allocated for items
  }

  // Return name
  return s;
}

void stack_delete(Stack *s) {
  // Free memory for items and stack
  free(s->items);
  free(s);
  return;
}

bool stack_empty(Stack *s) {
  // If top equals 0, stack is empty
  return (s->top == 0);
}

int stack_pop(Stack *s) {
  if (!s) {
    return -1; // Stack doesn't exist
  }

  // If there is a disk present, top of stack is top - 1
  if (s->top > 0) {
    s->top -= 1;
    return s->items[s->top];
  } else {
    return -1;
  }
}

int stack_peek(Stack *s) {
  // Returns top of the stack
  return s->items[s->top - 1];
}

void stack_push(Stack *s, int item) {
  if (!s) {
    return; // Stack doesn't exist
  }

  // If top of stack is at capacity, increase capacity and reallocate memory
  if (s->top == s->capacity) {
    s->capacity *= 2;
    s->items = (int *)realloc(s->items, s->capacity * sizeof(int));
  }

  // If there an item being pushed, increase top interval
  if (s->items) {
    s->items[s->top] = item;
    s->top += 1;
  }
  return;
}

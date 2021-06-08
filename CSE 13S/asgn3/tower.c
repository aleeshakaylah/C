#include "stack.h"
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int count;

// Recursive Implementation
void hanoi_recursion(int n, char start_rod, char end_rod, char temp_rod) {
  // If one disk remaining, move to end rod
  if (n == 1) {
    count = count + 1;
    printf("Move disk %d from peg %c to peg %c \n", n, start_rod, end_rod);
    return;
  }

  // Recursive calls decrementing disks as they are being moved
  hanoi_recursion(n - 1, start_rod, temp_rod, end_rod);
  count = count + 1;
  printf("Move disk %d from peg %c to peg %c \n", n, start_rod, end_rod);
  hanoi_recursion(n - 1, temp_rod, end_rod, start_rod);
}

// Stack implementation
int hanoi_stack(int n) {
  // Create all Rods (A, B, and C)
  Stack *A = stack_create(n, 'A');
  Stack *B = stack_create(n, 'B');
  Stack *C = stack_create(n, 'C');

  // Push the disks to starting rod (A)
  for (int i = n; i >= 1; i--) {
    stack_push(A, i);
  }

  int item_moved; // Keeps track of which disk is being popped
  int moves = 0;
  int max_moves = pow(2, n) - 1;

  if (n % 2 == 1) { // Odd number
    while (moves != max_moves) {

      // Check if rod B is empty or if the disk on rod A is less than rod B
      if (stack_empty(B)
          || (!stack_empty(A) && stack_peek(A) < stack_peek(B))) {
        item_moved = stack_pop(A);
        stack_push(B, item_moved);
        printf("Move disk %d from peg %c to peg %c \n", item_moved, 'A', 'B');
      } else {
        item_moved = stack_pop(B);
        stack_push(A, item_moved);
        printf("Move disk %d from peg %c to peg %c \n", item_moved, 'B', 'A');
      }

      // Increment moves and check if max_moves has been met
      moves++;
      if (moves == max_moves) {
        break;
      }

      // Check if rod C is empty or if the disk on rod A is less than rod C
      if (stack_empty(C)
          || (!stack_empty(A) && stack_peek(A) < stack_peek(C))) {
        item_moved = stack_pop(A);
        stack_push(C, item_moved);
        printf("Move disk %d from peg %c to peg %c \n", item_moved, 'A', 'C');
      } else {
        item_moved = stack_pop(C);
        stack_push(A, item_moved);
        printf("Move disk %d from peg %c to peg %c \n", item_moved, 'C', 'A');
      }

      // Increment moves and check if max_moves has been met
      moves++;
      if (moves == max_moves) {
        break;
      }

      // Check if rod C is empty or if the disk on rod B is less than rod C
      if (stack_empty(C)
          || (!stack_empty(B) && stack_peek(B) < stack_peek(C))) {
        item_moved = stack_pop(B);
        stack_push(C, item_moved);
        printf("Move disk %d from peg %c to peg %c \n", item_moved, 'B', 'C');
      } else {
        item_moved = stack_pop(C);
        stack_push(B, item_moved);
        printf("Move disk %d from peg %c to peg %c \n", item_moved, 'C', 'B');
      }

      // Increment moves
      moves++;
    }
  } else { // Even number
    while (moves != max_moves) {

      // Check if rod C is empty or if the disk on rod A is less than rod C
      if (stack_empty(C)
          || (!stack_empty(A) && stack_peek(A) < stack_peek(C))) {
        item_moved = stack_pop(A);
        stack_push(C, item_moved);
        printf("Move disk %d from peg %c to peg %c \n", item_moved, 'A', 'C');
      } else {
        item_moved = stack_pop(C);
        stack_push(A, item_moved);
        printf("Move disk %d from peg %c to peg %c \n", item_moved, 'C', 'A');
      }

      // Increment moves and check if max_moves has been met
      moves++;
      if (moves == max_moves) {
        break;
      }

      // Check if rod B is empty or if the disk on rod A is less than rod B
      if (stack_empty(B)
          || (!stack_empty(A) && stack_peek(A) < stack_peek(B))) {
        item_moved = stack_pop(A);
        stack_push(B, item_moved);
        printf("Move disk %d from peg %c to peg %c \n", item_moved, 'A', 'B');
      } else {
        item_moved = stack_pop(B);
        stack_push(A, item_moved);
        printf("Move disk %d from peg %c to peg %c \n", item_moved, 'B', 'A');
      }

      // Increment moves and check if max_moves has been met
      moves++;
      if (moves == max_moves) {
        break;
      }

      // Check if rod B is empty or if the disk on rod C is less than rod B
      if (stack_empty(B)
          || (!stack_empty(C) && stack_peek(C) < stack_peek(B))) {
        item_moved = stack_pop(C);
        stack_push(B, item_moved);
        printf("Move disk %d from peg %c to peg %c \n", item_moved, 'C', 'B');
      } else {
        item_moved = stack_pop(B);
        stack_push(C, item_moved);
        printf("Move disk %d from peg %c to peg %c \n", item_moved, 'B', 'C');
      }

      // Increment moves
      moves++;
    }
  }

  // Free Stacks & Items
  stack_delete(A);
  stack_delete(B);
  stack_delete(C);

  return moves;
}

int main(int argc, char **argv) {
  int c = 0, n = 5;
  int stack = 0, recursion = 0;

  while ((c = getopt(argc, argv, "srn:")) != -1) {
    switch (c) {
    case 's':
      stack = 1;
      break;

    case 'r':
      recursion = 1;
      break;

    case 'n':
      n = atoi(optarg);
      break;
    }
  }

  if (stack == 1) {
    // Stack implementation
    printf("================================\n");
    printf("----------   STACKS   ----------\n");
    printf("================================\n");
    count = hanoi_stack(n);
    printf("\nNumber of moves: %d\n", count);
  }

  if (recursion == 1) {
    // Recursive implementation
    count = 0;
    printf("===============================\n");
    printf("---------- RECURSION ----------\n");
    printf("===============================\n");
    hanoi_recursion(n, 'A', 'B', 'C');
    printf("\nNumber of moves: %d\n", count);
  }
  return 0;
}

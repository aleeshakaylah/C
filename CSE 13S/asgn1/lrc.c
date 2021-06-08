//
//  lrc.c
//  CSE 13S
//
//  Created by Aleesha Nageer
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum faciem { LEFT,
                      RIGHT,
                      CENTER,
                      PASS } faces;
faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS};

const char *names[] = {"Happy", "Sleepy", "Sneezy", "Dopey", "Bashful", "Grumpy", "Doc", "Mirror Mirror", "Snow White", "Wicked Queen"};

//Function for moving positon to the left
uint32_t left(uint32_t pos, uint32_t players) {
  return ((pos + players - 1) % players);
}

//Function for moving positon to the right
uint32_t right(uint32_t pos, uint32_t players) {
  return ((pos + 1) % players);
}

//Function for checking if there is one player with money left
uint32_t hasEnd(uint32_t balance[], uint32_t num_players) {
  uint32_t count = 0;
  for (uint32_t i = 0; i < num_players; i++) {
    if (balance[i] > 0) {
      count++;
    }
  }
    //Returns T/F flag for main to know someone has won
    if (count == 1){
        return (1);
    } else{
        return(0);
    }
}

int main(void) {
  uint32_t seed, num_players, init_balance = 3;

  //Getting User Input for Seed
  printf("Random Seed: ");
  scanf("%d", &seed);

  //Getting User Input for Number of Players
  printf("How many players? ");
  scanf("%d", &num_players);

  //Error Checking: If input is less than 2 or greater than 10, it is invalid.
  while (num_players < 2 || num_players > 10) {
    printf("Invalid Input\n");
    printf("How many players? ");
    scanf("%d", &num_players);
  }

  uint32_t balance[num_players];

  //Initializing each Player's Balance to $3
  for (uint32_t i = 0; i < num_players; i++) {
    balance[i] = init_balance;
  }

  srand(seed);

  uint32_t curr = 0, pot = 0, prev = 0;

  while (1) {
      printf("%s rolls... ", names[curr]);
      
      //If-Else Block checks for number of rolls (Shorthand)
      //https://stackoverflow.com/questions/18646190/if-else-statement-shortcut-in-c
      uint32_t roll = balance[curr] > 3 ? 3 : balance[curr];
      for (uint32_t i = 0; i < roll; i++) {
          uint32_t a = rand() % 6;
          if (die[a] == LEFT) {
              balance[left(curr, num_players)]++;
              balance[curr]--;
              printf("gives $1 to %s ", names[left(curr, num_players)]);
          } else if (die[a] == RIGHT) {
            balance[right(curr, num_players)]++;
            balance[curr]--;
            printf("gives $1 to %s ", names[right(curr, num_players)]);
          } else if (die[a] == CENTER) {
            pot++;
            balance[curr]--;
            printf("puts $1 in the pot ");
          } else {
            printf("gets a pass ");
          }
      }
      printf("\n");
      prev = curr;
      do {
          curr = (curr + 1) % num_players;
      } while (curr != prev && balance[curr] == 0);

      if (hasEnd(balance, num_players) == 1) {
          break;
      }
  }

  printf("%s wins the $%d pot with $%d left in the bank\n", names[curr], pot, balance[curr]);

  return 0;
}

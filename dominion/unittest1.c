#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main (int argc, char** argv) {
  struct gameState G;

  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute, smithy};

  printf ("Testing endTurn.\n");
  
  int r = initializeGame(2, k, atoi(argv[1]), &G);

  assert (r == 0);

  int player1 = whoseTurn(&G);
  printf("It is initially player %d's turn\n", player1);
  
  endTurn(&G);
  player2 = whoseTurn(&G);
  assert(player2!=player1);
  
  printf("After endTurn() it is player %d's turn\n", player1);

  return 0;
}
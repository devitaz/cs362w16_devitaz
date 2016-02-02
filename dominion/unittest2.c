#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main (int argc, char** argv) {
  struct gameState G;

  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute, smithy};

  printf ("Testing updateCoins.\n");
  
  int r = initializeGame(2, k, atoi(argv[1]), &G);
  assert (r == 0);
  
  int player = whoseTurn(&G);
  G.handCount(player) = 3;
  
  G.coins=0;
  G.hand[player][0] == copper;
  updateCoins(player,&G,0);
  assert(G.coins==1);

  G.hand[player][1] == gold;
  updateCoins(player,&G,0);
  assert(G.coins==4);

  G.hand[player][2] == silver;
  updateCoins(player,&G,0);
  assert(G.coins==6);

  updateCoins(player,&G,0);
  assert(G.coins==6);

  updateCoins(player,&G,5);
  assert(G.coins==11);

  return 0;
}
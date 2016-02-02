#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"

static int passed=0;
int massert(int b, char* s) 
{
  if (!b) 
  {
    passed=1;
    printf ("ASSERTION FAILURE: %s\n", s);
  }
  return 0;
}
int main (int argc, char** argv) {
  struct gameState G;

  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
         sea_hag, tribute, smithy};

  printf ("Testing updateCoins.\n");
  
  int r = initializeGame(2, k, 5, &G);
  massert(r == 0,"initializeGame failed\n");
  
  int player = whoseTurn(&G);
  G.coins=0;

  G.handCount[player] = 1;
  G.hand[player][0] = copper;
  updateCoins(player,&G,0);
  massert(G.coins==1,"incorrect value for coins\n");

  G.handCount[player]++;
  G.hand[player][1] = gold;
  updateCoins(player,&G,0);
  massert(G.coins==4,"incorrect value for coins\n");

  G.handCount[player]++;
  G.hand[player][2] = silver;
  updateCoins(player,&G,0);
  massert(G.coins==6,"incorrect value for coins\n");

  updateCoins(player,&G,0);
  massert(G.coins==6,"incorrect value for coins\n");

  updateCoins(player,&G,5);
  massert(G.coins==11,"incorrect value for coins\n");

  if(passed==0)
      printf("---Test Passed!\n");

  return 0;
}
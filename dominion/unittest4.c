#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

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

  printf ("Testing discardCard.\n");
  
  int r = initializeGame(2, k, 5, &G);
  massert(r == 0,"initializeGame failed\n");

  int player = whoseTurn(&G);
  int handPos=1;
  int handTemp=G.handCount[player]=3;
  G.hand[player][0] = k[0];
  G.hand[player][1] = k[1];
  G.hand[player][2] = k[2];

  int card = handCard(handPos, &G);
  massert(card==k[1],"error: card != gardens\n");

  discardCard(handPos,player,&G,0);
  massert(G.handCount[player]==handTemp-1,"incorrect value for handCount\n");
  massert(G.hand[player][1]!=k[3],"incorrect card in hand\n");
  massert(G.hand[player][1]==k[2],"incorrect card in hand\n");
  massert(G.hand[player][0]==k[0],"incorrect card in hand\n");
	
  if(passed==0)
      printf("---Test Passed!\n");

  return 0;
}
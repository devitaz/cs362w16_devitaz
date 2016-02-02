#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main (int argc, char** argv) {
  struct gameState G;

  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute, smithy};

  printf ("Testing discardCard.\n");
  
  int r = initializeGame(2, k, atoi(argv[1]), &G);
  assert (r == 0);

  int handPos=2;
  G.hand[player][0] == k[0];
  G.hand[player][1] == K[1];
  G.hand[player][2] == K[2];

  int player = whoseTurn(&G);
  int num_cards=G.handCount[player];
  assert(num_cards==3);

  card = handCard(handPos, &G);
  assert(card==2);

  discardCard(handPos,player,&G,0);
  assert(G.handCount[player]==num_cards-1);
  if(whoseTurn(&G)!=player)
  	endTurn(&G);

  int i=0;
  printf("card \"embargo\" should not be in hand\n");
  while(i<numHandCards(&G))
	{
	      printf("card %d: %d\n",i+1,G.hand[Player][i]);
	}
	

  return 0;
}
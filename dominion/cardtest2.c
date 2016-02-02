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
int main(int argc, int argv[])
{
	  struct gameState G;
  	struct gameState *p=&G;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
         sea_hag, tribute, smithy};

  	printf ("Testing village card.\n");
  
  	int r = initializeGame(2, k, 5, p);
  	massert (r == 0,"initializeGame failed\n");

  	int player = whoseTurn(p);
  	int handPos = 1;
  	int coin_bonus=0;

  	G.handCount[player]=4;
  	G.hand[player][0]=council_room;
  	G.hand[player][1]=village;
  	G.hand[player][2]=minion;
    G.hand[player][3]=mine;

  	G.numActions=0;

  	int card = handCard(handPos,p);
  	massert(card>=adventurer&&card<=treasure_map,"invalid card\n");
    massert(card==village,"incorrect card\n");

  	int test=cardEffect(card,-1,-1,-1,p,handPos,&coin_bonus);
  	massert(test==0,"cardEffect failed\n");
    massert(G.handCount[player]==4,"incorrect had count\n");
    massert(G.numActions==2,"incorrect numActions value\n");
  	massert(G.hand[player][1]!=village,"village is not discarded\n");

    if(passed==0)
  	   printf("---Test Passed!\n");

    return 0;
}
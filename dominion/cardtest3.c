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

  	printf ("Testing embargo card.\n");
  
  	int r = initializeGame(2, k, 5, p);
  	assert (r == 0);

  	int player = whoseTurn(p);
    int handPos = 2;
    int coin_bonus=0;
    G.coins=0;

  	G.handCount[player]=4;
  	G.hand[player][0]=council_room;
  	G.hand[player][1]=village;
  	G.hand[player][2]=embargo;
    G.hand[player][3]=mine;

    int cardSupply=G.hand[player][0];
    G.supplyCount[cardSupply]=3;
    G.embargoTokens[cardSupply]=0;

  	int card = handCard(handPos,p);
  	massert(card>=adventurer&&card<=treasure_map,"invalid handCard\n");
    massert(card==embargo,"error: card != embargo\n");
    
  	int test=cardEffect(card,cardSupply,-1,-1,p,handPos,&coin_bonus);
  	massert(test==0,"cardEffect returned error\n");
  	massert(G.handCount[player]==3,"incorrect value for handCount\n");
    massert(G.coins==2,"incorrect value for coins\n");
    massert(G.embargoTokens[cardSupply]==1,"incorrect value for embargoTokens\n");
    massert(G.hand[player][2]!=embargo,"embargo card was not discarded\n");

    if(passed==0)
  	   printf("---Test Passed!\n");

    return 0;
}
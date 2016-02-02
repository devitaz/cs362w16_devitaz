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

  	printf ("Testing mine card.\n");
  
  	int r = initializeGame(2, k, 5, p);
  	massert(r == 0,"initializeGame failed\n");

  	int player = whoseTurn(p);
  	int handPos = 2;
  	int coin_bonus=0;

  	G.handCount[player]=4;
  	G.hand[player][0]=copper;
  	G.hand[player][1]=silver;
  	G.hand[player][2]=mine;
  	G.hand[player][3]=mine;

  	int card = handCard(handPos,p);
  	massert(card>=adventurer&&card<=treasure_map,"invalid handCard\n");
  	massert(card==mine,"error: card != mine\n");
    // testing effect of invalid choice2 data
  	int test=cardEffect(card,G.hand[player][0],gold,-1,p,handPos,&coin_bonus);
  	massert(test==-1,"cardEffect did not return error with invalid data\n");    // finds bug
    // test1: proper use of function, increasing value of treasure
    test=cardEffect(card,G.hand[player][0],silver,-1,p,handPos,&coin_bonus);
    massert(test==0,"cardEffect returned error\n");
    massert(G.hand[player][0]==silver,"mine card returned incorrect card");

    test=cardEffect(card,G.hand[player][0],gold,-1,p,handPos,&coin_bonus);
    massert(test==0,"cardEffect returned error\n");
    massert(G.hand[player][0]==gold,"mine card returned incorrect card");
    // test2: proper use of function, decreasing value of treasure
    card = handCard(++handPos,p);

    test=cardEffect(card,G.hand[player][1],copper,-1,p,handPos,&coin_bonus);
    massert(test==0,"cardEffect returned error\n");
    massert(G.hand[player][1]==copper,"mine card returned incorrect card");
  	massert(G.handCount[player]==4,"incorrect handCount");
    
    if(passed==0)
  	   printf("---Test Passed!\n");

    return 0;
}
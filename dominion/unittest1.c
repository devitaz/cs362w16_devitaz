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
  struct gameState *p=&G;

  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute, smithy};

  printf ("Testing scoreFor.\n");
  
  int r = initializeGame(2, k, 5, p);
  massert(r == 0,"initializeGame failed\n");

  G.handCount[0]=1;
  G.hand[0][0]=duchy;
  int score=scoreFor(0,p);
  massert(score==3,"incorrect value for scoreFor\n");

  G.handCount[0]=2;
  G.hand[0][1]=curse;
  score=scoreFor(0,p);
  massert(score==2,"incorrect value for scoreFor\n");
  
  G.discardCount[0]=1;
  G.discard[0][0]=province;
  score=scoreFor(0,p);
  massert(score==8,"incorrect value for scoreFor\n");

  G.discardCount[0]=2;
  G.discard[0][1]=curse;
  score=scoreFor(0,p);
  massert(score==7,"incorrect value for scoreFor\n");

  G.deckCount[0]=1;				// found bug
  G.deck[0][0]=great_hall;
  score=scoreFor(0,p);
  massert(score==8,"incorrect value for scoreFor\n");

  G.deckCount[0]=2;
  G.deck[0][1]=estate;
  score=scoreFor(0,p);
  massert(score==7,"incorrect value for scoreFor\n");

  if(passed==0)
  		printf("---Test Passed!\n");

  return 0;
}
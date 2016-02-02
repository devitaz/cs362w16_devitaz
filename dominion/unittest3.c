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

  printf ("Testing gainCard.\n");
  
  int r = initializeGame(2, k, 5, &G);
  massert(r == 0,"initializeGame failed\n");
  
  int player=whoseTurn(&G);
  int supplyPos=3;
  int flag1=1;
  int flag2=2;
  int flag3=-293587678;
  
  int deck_count=G.deckCount[player]=3;
  int hand_count=G.handCount[player]=4;
  int discard_count=G.discardCount[player]=5;
  
  int gain_card=gainCard(supplyPos,&G,flag1,player);
  massert(gain_card==0,"incorrect value for gainCard\n");
  massert(G.deckCount[player]==deck_count+1,"incorrect value for deckCount\n");

  gain_card=gainCard(++supplyPos,&G,flag2,player);
  massert(gain_card==0,"incorrect value for gainCard\n");
  massert(G.handCount[player]==hand_count+1,"incorrect value for handCount\n");

  gain_card=gainCard(++supplyPos,&G,flag3,player);
  massert(gain_card==0,"incorrect value for gainCard\n");
  massert(G.discardCount[player]==discard_count+1,"incorrect value for discardCount\n");

  if(passed==0)
      printf("---Test Passed!\n");

  return 0;
}
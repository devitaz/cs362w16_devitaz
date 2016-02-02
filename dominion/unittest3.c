#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int main (int argc, char** argv) {
  struct gameState G;

  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute, smithy};

  printf ("Testing gainCard.\n");
  
  int r = initializeGame(2, k, atoi(argv[1]), &G);
  assert (r == 0);
  
  int supplyPos=8;
  int flag1=1;
  int flag2=2;
  int flag3=293587678;
  int player=1;
  int deck_count=G.deckCount[player];
  int hand_count=G.handCount[player];
  int discard_count=G.discardCount[player];
  int supply_count=G.supplyCount[supplyPos];

  

  int gain_card=gainCard(supplyPos,&G,flag1,player);
  assert(gain_card==0);
  assert(G.deckCount[player]==deck_count+1);
  assert(G.supplyCount[supplyPos]==supply_count-1);

  gain_card=gainCard(supplyPos,&G,flag2,player);
  assert(gain_card==0);
  assert(G.handCount[player]==hand_count+1);
  assert(G.supplyCount[supplyPos]==supply_count-2);

  gain_card=gainCard(supplyPos,&G,flag3,player);
  assert(gain_card==0);
  assert(G.discardCount[player]==discard_count+1);
  assert(G.supplyCount[supplyPos]==supply_count-3);




  return 0;
}
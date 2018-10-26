/*
 * Sonam Kindy
 * CS362
 * Unit Test 1: compare
 * Created: 10/25/18

 If required to use:
 int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed,
    struct gameState * state)
 struct gameState state;
 initializeGame(2, k, atoi(argv[1]), &state); 
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>

#define FUNCTION    "compare"

void testCompare()
{
    int num1 = 1;
    int* a = &num1;
    int num2 = 0;
    int* b = &num2;

    printf("TEST 1: a > b\n");
    if (compare((void*)a, (void*)b) == 1)
        printf("compare(): PASSED when testing a > b\n\n");
    else
        printf("compare(): FAIL when testing a > b\n\n");

    num1 = 0;
    a = &num1;
    num2 = 1;
    b = &num2;

    printf("TEST 2: a < b\n");
    if (compare((void*)a, (void*)b) == -1)
        printf("compare(): PASSED when testing a < b\n\n");
    else
        printf("compare(): FAIL when testing a < b\n\n");

    num1 = 1;
    a = &num1;
    num2 = 1;
    b = &num2;
    
    printf("TEST 2: a == b\n");
    if (compare((void*)a, (void*)b) == 0)
        printf("compare(): PASSED when testing a == b\n\n");
    else
        printf("compare(): FAIL when testing a == b\n\n");
    
}

int main(int argc, char *argv[])
{
    printf("----------------- Unit testing fn %s ----------------\n\n", FUNCTION);
    testCompare();
    printf(">>>>>> SUCCESS: Unit testing complete of fn %s <<<<<<\n\n", FUNCTION);
    
    return 0;
}

CFLAGS= -Wall -fpic -coverage -lm -std=c99
CC = gcc
NUMBERS = 1 2 3 4
OUT_FILE = unittestresults.out

rngs.o: rngs.h rngs.c
	$(CC) -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	$(CC) -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	$(CC) -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	$(CC)  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	$(CC) -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	$(CC) -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	$(CC) -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	$(CC) -c interface.c -g  $(CFLAGS)

unittests: unittest1.c unittest2.c unittest3.c unittest4.c \
	cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	$(foreach el,$(NUMBERS),$(CC) $(CFLAGS) unittest$(el).c dominion.o rngs.o -o unittest$(el);)
	$(foreach el,$(NUMBERS),$(CC) $(CFLAGS) cardtest$(el).c dominion.o rngs.o -o cardtest$(el);)
	
runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults: unittests
	echo "Result for running unit tests:" > $(OUT_FILE)
	$(foreach el,$(NUMBERS),echo "unittest$(el).c" >> $(OUT_FILE);./unittest$(el) >> $(OUT_FILE);gcov -f dominion.c >> $(OUT_FILE);)
	$(foreach el,$(NUMBERS),echo "cardtest$(el).c" >> $(OUT_FILE);./cardtest$(el) >> $(OUT_FILE);gcov -f dominion.c >> $(OUT_FILE);)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out \
	testDrawCard testDrawCard.exe \
	unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 # remove unittestX later

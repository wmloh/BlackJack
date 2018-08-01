#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameEngine.h"

static char *hit = "hit";
static char *stand = "stand";
static char *dble = "double";
static char *split = "split";
static char *quit = "quit";

// checkBusted(player, curValue) return true if and only if the cards
//   at hand exceeds 21
// effect: mutates curValue
static bool checkBusted(struct Player *player, int *curValue) {

	int sum = 0;
	int numAces = 0;
	int len = getNum(player);

	for(int i = 0; i < len; ++i) {
		char c = (getCardsAtHand(player))[i][0];
		if ('2' <= c && c <= '9') {
			sum += c - 48;
		} else if (c == '1' || c == 'J' || c == 'Q' || c == 'K') {
			sum += 10;
		} else {
			numAces++;
		}
	}

	if(numAces) {
		for(int i = 0; i < numAces; ++i) {
			if ((len == 2) && (sum + 11 == 21)) {
				sum = 21;
			} else if (sum + 11 <= 21) {
				sum += 11;
			} else {
				sum++;
			}
		}
	}

	*curValue = sum;

	if (sum <= 21) {
		return false;
	}
	return true;
}

// placeAllBets(players, bets, numPlayers) places bets for all players and returns
//   the total amount of bets
// require: len(players) == len(bets)
// effect: mutates the money and currBet of each player
static int placeAllBets(struct Player **players, int *bets, int numPlayers) {
	int totalBets = 0;
	#pragma omp parallel for
		for(int i = 0; i < numPlayers; ++i) {
			placeBets(players[i], bets[i]);
			totalBets += bets[i];
		}
	return totalBets;
}

// commandLine(endTurn, player, deck, round) provides a command line interface and
//   returns false if and only if the command is "quit"
// effect: mutates endTurn, player, deck
static bool commandLine(bool *endTurn, struct Player *player, struct Deck *deck, int round) {
	char *input = getInput();
	if (!strcmp(input, quit)) {
		return false;
	} else if (!strcmp(input, hit)) {
		hitCard(player, deck);
		displayCards(player);
	} else if (!strcmp(input, stand)) {
		updateActionSeq(player, stand);
		*endTurn = true;
	} else if (!strcmp(input, dble)) {
		if(round == 1) {

		} else {
			printf("Double command can only be done in the first round\n");
		}
	} else if (!strcmp(input, split)) {
		if(round == 1) {
			char **cards = getCardsAtHand(player);
			if(cards[0][0] == cards[1][0]) {

			} else {
				printf("Split can only be used when the denomination of the cards are the same\n");
			}
		} else {
			printf("Split command can only be done in the first round\n");
		}
	} else if (!strcmp(input, "-help")) {
		printf("Commands:\n *%s\n *%s\n *quit\n", hit, stand);
	} else {
		printf("Invalid command. Type -help for more information.\n");
	}
	free(input);
	return true;
}

void initRound(struct Player **players, int numPlayers, int *bets, struct Player *dealer) {

	struct Deck *deck = initDeck();

	placeAllBets(players, bets, numPlayers);

	bool *busted = malloc(sizeof(bool) * numPlayers);
	int *curValue = malloc(sizeof(int) * numPlayers);

	bool dealerBusted = false;
	int dealerCurValue;

	#pragma omp parallel for
	for(int i = 0; i < numPlayers; ++i) {
		hitCard(players[i], deck);
		hitCard(players[i], deck);
		busted[i] = false;
	}
	hitCard(dealer, deck);
	hitCard(dealer, deck);

	struct Player *player;
	bool endTurn;
	int round;

	for(int i = 0; i < numPlayers; ++i) {
		round = 1;
		player = players[i];
		printf("\nvvvvvv %s vvvvvv\n", getName(player));
		displayCards(player);
		endTurn = false;
		while(!endTurn) {
			
			if (checkBusted(player, &(curValue[i]))) {
				endTurn = true;
				busted[i] = true;
				printf("%s is busted\n", getName(player));
				continue;
			} else {
				printf("Current sum: %i\n", curValue[i]);
			}
			
			if(!commandLine(&endTurn, player, deck, round)) {
				goto quickEnd;
			}
			round++;

		}
		printf("^^^^^^^^^^^^\n");
	}

	round = 1;
	printf("\nvvvvvv %s vvvvvv\n", getName(dealer));
	displayCards(dealer);
	endTurn = false;
	while(!endTurn) {
		if(checkBusted(dealer, &dealerCurValue)) {
			endTurn = true;
			dealerBusted = true;
			break;
			printf("%s is busted\n", getName(dealer));
		} else {
			printf("Current sum: %i\n", dealerCurValue);
		}

		if(!commandLine(&endTurn, dealer, deck, round)) {
			goto quickEnd;
		}
		round++;
	}
	printf("^^^^^^^^^^^^\n");

	for(int i = 0; i < numPlayers; ++i) {
		if (dealerBusted && !busted[i]) {
			winBet(players[i], dealer);
		} else if(!busted[i]) {
			if (curValue[i] > dealerCurValue) {
				winBet(players[i], dealer);
			} else if (curValue[i] < dealerCurValue) {
				loseBet(players[i], dealer);
			} else {
				drawBet(players[i], dealer);
			}
		} else {
			loseBet(players[i], dealer);
		}
	}

	quickEnd:
	freeDeck(deck);
	free(busted);
	free(curValue);
}
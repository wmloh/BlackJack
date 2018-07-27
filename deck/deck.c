#include <time.h>
#include <stdlib.h>
#include "deck.h"
#include <assert.h>
#include <stdio.h>

char *drawCard(struct Deck *deck) {
	srand(time(NULL));

	int rollSuit;
	int rollNum;

	char *hand = NULL;

	do {
		rollSuit = rand() % 4;
		rollNum = rand() % 13;
	} while (!updateCard(deck, &hand, rollSuit, rollNum));

	return hand;
}

static bool updateCard(struct Deck *deck, char **hand, int suit, int num) {

	char *card = getCard(deck, suit, num);
	char **allCards = getAllCards(deck);
	if (card) {
		*hand = card;
		allCards[13 * suit + num] = NULL;

		return true;
	}	
	return false;
}
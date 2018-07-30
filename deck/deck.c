#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "deck.h"

#define SUITSIZE 13
#define NUMSUIT 4

struct Deck {
	char **cards;
	int *cardsLeft;
};

struct Deck *initDeck(void) {
	struct Deck *deck = malloc(sizeof(struct Deck));
	char **cards = malloc(sizeof(char *) * SUITSIZE * NUMSUIT);
	char *array[] = {"AC", "2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C", "10C", "JC", "QC", "KC","AD", "2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "10D", "JD", "QD", "KD","AH", "2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "10H", "JH", "QH", "KH","AS", "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", "10S", "JS", "QS", "KS"};
	int len = SUITSIZE * NUMSUIT;
	#pragma omp parallel for
		for (int i = 0; i < len; ++i) {
			cards[i] = array[i];
		}
	
	int *cardsLeft = malloc(sizeof(int) * NUMSUIT);

	#pragma omp parallel for
		for(int i = 0; i < NUMSUIT; ++i) {
			cardsLeft[i] = SUITSIZE;
		}

	deck->cards = cards;
	deck->cardsLeft = cardsLeft;
	return deck;
}

void freeDeck(struct Deck *deck) {
	free(deck->cards);
	free(deck->cardsLeft);
	free(deck);
}

char **getAllCards(struct Deck *deck) {
	return deck->cards;
}


int *getCardsLeft(struct Deck *deck) {
	return deck->cardsLeft;
}

char *getCard(struct Deck *deck, int suit, int num) {
	return deck->cards[SUITSIZE * suit + num];
}

// updateCard(deck, hand, suit, num) return true if and only if card 
//   specified by suit and num exists in the deck
// effects: mutates hand to the card drawn if successful
//          mutates the card drawn from array of cards in deck to NULL
static bool updateCard(struct Deck *deck, char **hand, int suit, int num) {

	char *card = getCard(deck, suit, num);
	char **allCards = getAllCards(deck);
	if (card) {
		*hand = card;
		allCards[SUITSIZE * suit + num] = NULL;
		return true;
	}	
	return false;
}

char *drawCard(struct Deck *deck) {
	srand(time(NULL));

	int rollSuit;
	int rollNum;

	char *hand = NULL;

	do {
		rollSuit = rand() % NUMSUIT;
		rollNum = rand() % SUITSIZE;
	} while (!updateCard(deck, &hand, rollSuit, rollNum));
	(deck->cardsLeft)[rollSuit]--;
	return hand;
}


#include <stdlib.h>
#include <stdio.h>
#include "../data_struct/data_struct.h"
#include <omp.h>
#include <pthread.h>
#include "data_struct.h"

#define SIZE 13

struct Deck {
	char **cards;
	int *cardsLeft;
};

struct Deck *initDeck(void) {
	struct Deck *deck = malloc(sizeof(struct Deck));
	char **cards = malloc(sizeof(char *) * SIZE * 4);
	char *array[] = {"AC", "2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C", "10C", "JC", "QC", "KC","AD", "2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "10D", "JD", "QD", "KD","AH", "2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "10H", "JH", "QH", "KH","AS", "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", "10S", "JS", "QS", "KS"};
	int len = SIZE * 4;
	#pragma omp parallel for
		for (int i = 0; i < len; ++i) {
			cards[i] = array[i];
		}
	
	int *cardsLeft = malloc(sizeof(int) * 4);

	#pragma omp parallel for
		for(int i = 0; i < 4; ++i) {
			cardsLeft[i] = 13;
		}

	deck->cards = cards;
	deck->cardsLeft = cardsLeft;
	return deck;
}

char **getAllCards(struct Deck *deck) {
	return deck->cards;
}

char *getCard(struct Deck *deck, int suit, int num) {
	return deck->cards[SIZE * suit + num];
}

int *getCardsLeft(struct Deck *deck) {
	return deck->cardsLeft;
}


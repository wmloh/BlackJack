#include <omp.h>
#include <pthread.h>
#include <stdbool.h>

struct Deck;

// initDeck() returns a pointer to the struct Deck and initiatizes
//   all standard cards and arrays of number of cards left
struct Deck *initDeck(void);

// freeDeck(deck) frees all allocated memory associated to deck
void freeDeck(struct Deck *deck);

// getAllCards(deck) returns an array of card strings
char **getAllCards(struct Deck *deck);

// getCardsLeft(deck) returns an array of number of cards left
int *getCardsLeft(struct Deck *deck);

// getCard(deck, suit, num) returns a string that corresponds to
//   the suit and num of the card
char *getCard(struct Deck *deck, int suit, int num); 

// drawCard(deck) randomly draws a valid card from deck and returns
//   the string of card drawn
// effects: mutates the card drawn from array of cards in deck to NULL
char *drawCard(struct Deck *deck);

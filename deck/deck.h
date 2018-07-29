#include <omp.h>
#include <pthread.h>
#include <stdbool.h>

struct Deck *initDeck(void);

void freeDeck(struct Deck *deck);

char **getAllCards(struct Deck *deck);

int *getCardsLeft(struct Deck *deck);

char *getCard(struct Deck *deck, int suit, int num); 

char *drawCard(struct Deck *deck);

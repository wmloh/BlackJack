#include <stdbool.h>

struct Deck *initDeck(void);

char **getAllCards(struct Deck *deck);

int *getCardsLeft(struct Deck *deck);

char *getCard(struct Deck *deck, int suit, int num); 
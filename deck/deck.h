#include "../data_struct/data_struct.h"

char *drawCard(struct Deck *deck);

static bool updateCard(struct Deck *deck, char **hand, int suit, int num);
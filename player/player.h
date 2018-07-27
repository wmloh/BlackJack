struct Player;

struct Player *initPlayer(void);

void updateCardsAtHand(struct Player *player, char *card);

void updateActionSeq(struct Player *player, char *action);

int updateNum(struct Player *player);

void displayCards(struct Player *player);
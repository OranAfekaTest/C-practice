#ifndef __DECK_H__
#define __DECK_H__

#include "Card.h"
#include "Status.h"
#include "MyVector.h"
#include <time.h>
#include <stdlib.h>/* for random shuffeling*/
#define CARDS_IN_DECK 52
#define TIMES_TO_SHUFFLE 3

typedef struct Deck Deck;

Deck* CreateDeck(void);
void DestroyDeck(Deck** _deck);
Status ShuffleDeck(Deck* _deck, int _times);
Status DrawCard(Deck* _deck, Card** _card);
Status ReturnCardToDeck(Deck* _deck, Card* _card);
int PrintDeck(Deck* _deck);

#endif /* __DECK_H__ */
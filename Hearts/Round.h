#ifndef __ROUND_H__
#define __ROUND_H__
#include "Deck.h"
#include "Card.h"
#include "Status.h"
#include "Player.h"
#define PLAYERS_IN_GAME 4

typedef struct Round Round;

Round* CreateRound(void);
void DestroyRound(Round** _round);
Status StartRound(Round* _round, Vector* _players);
Card* Strategy(Vector* _cards, int* _legalIndexes, size_t _legalIndexesSize, void* _tCon);
int Rules(Card* _card, void* _tCon);
size_t GetNumOfPlayers(Round* _round);

#endif /* __ROUND_H__ */
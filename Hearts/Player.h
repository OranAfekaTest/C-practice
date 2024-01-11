#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "Card.h"
#include "Status.h"
#include "MyVector.h"
#include <stdlib.h> /* free */
#include <stddef.h> /* NULL */

typedef struct Player Player;

Player* CreatePlayer(int _isHuman, char* _name);
void DestroyPlayer(void** _player);
Status PlayCard(Player* _player, Card** _toTable, Card* (*_fpStrategy)(Vector* _cards, int* _legalIndexes, size_t _legalIndexesSize, void* _context), int (*_fpRules)(Card* _card, void* _context), void* _tContext);
int PrintAllHands(void* _player, size_t _index, void* _context);
int TakeCardFromDeck(void* _player, size_t _index, void* _deck);
int SortHand(void* _player, size_t _index, void* _context);
int WhoHasTwoOfSpades(void* _player, size_t _index, void* _context);
Status AddCardToHand(Player* _player, Card* _card);
Status AddPoints(Player* _player, int _points);
int PlayerHasSuitInHand(Player* _player, Suit _suit);
int CheckForWinner(void* _player, size_t _index, void* _context);
int PrintScore(void* _player, size_t _index, void* _context);
int	WinComparator(const void* _itemA, const void* _itemB);
char* GetPlayerName(Player* _player);
Status PrintHand(Player* _player);
int PlayerOnlyHasHeartsInHand(Player* _player);
int GetPlayerScore(Player* _player);

#endif /* __PLAYER_H__ */
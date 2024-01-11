#ifndef __UI_H__
#define __UI_H__
#include "Player.h"
#include "Card.h"
#include <stddef.h>

typedef struct UI UI;

void CardPlay(Player* _player, Card* _card);
int ChooseCard(void);
char* InsertPlayerName(size_t _num);
int InsertIsHuman(void);
void AnounceWinner(Player* _winner);
void TrickDetermination(Player* _leadPlayer, Card* _leadCard);
int PrintCard(void* _card, size_t _index, void* _context);
void PrintScores(Vector* _players);
void PreGiftStage(void);
void PrintTrickNumber(size_t _num);
void PrintRoundStart(size_t _num);




#endif /* __UI_H__ */
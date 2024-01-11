#ifndef __CARD_H__
#define __CARD_H__
#include <stdlib.h> /*malloc*/
#include <stddef.h> /*NULL*/
#include <string.h> /*strcat*/
#define FALSE 0
#define TRUE 1

static const char* SuitNames[] = {"Spades", "Diamonds", "Clubs", "Hearts", "4"};
static const char* RankNames[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Damma", "King", 
"Ace", "13"};

enum {  SPADES,
        DIAMONDS,
        CLUBS,
        HEARTS, 
        NUM_OF_SUITS} typedef Suit;

enum {  TWO, 
        THREE, 
        FOUR, 
        FIVE, 
        SIX, 
        SEVEN, 
        EIGHT, 
        NINE,
        TEN,
        JACK, 
        DAMMA, 
        KING, 
        ACE, 
        NUM_OF_RANKS} typedef Rank;

typedef struct Card Card;

Card* CreateCard(Suit _suit, Rank _rank);
void DestroyCard(void** _card);
char* GetCardName(Card* _card);
int PrintCard(void* _card, size_t _index, void* _context);
int CardCriteria(const Card* _a, const Card* _b);
int GetCardRank(Card* _card);
int GetCardSuit(Card* _card);
int FindCard(void* _card, size_t _index, void* _context);

#endif /* __CARD_H__ */
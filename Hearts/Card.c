#include "Card.h"
#include <stdio.h>

struct Card
{
    Suit m_suit;
    Rank m_rank;
};

Card* CreateCard(Suit _suit, Rank _rank)
{
    Card* card = malloc(sizeof(Card));
    if(!card)
    {
        return NULL;
    }
    if(_suit < 0 || _rank < 0 || NUM_OF_SUITS < _suit || NUM_OF_RANKS < _rank)
    {
        free(card);
        return NULL;
    }
    
    card->m_suit = _suit;
    card->m_rank = _rank;

    return card;
}

void DestroyCard(void** _card)
{
    Card** card = (Card**)_card;
    if(*card)
    {
        free(*card);
        *card = NULL;
    }
}

int FindCard(void* _card, size_t _index, void* _context)
{
    if(((Card*)_card)->m_rank == ((Card*)_context)->m_rank && ((Card*)_card)->m_suit == ((Card*)_context)->m_suit)
    {
        return 0;
    }
    return 1;
}

int GetCardRank(Card* _card)
{
    if(!_card)
    {
        return -1;
    }
    return _card->m_rank;
}

int GetCardSuit(Card* _card)
{
    if(!_card)
    {
        return -1;
    }
    return _card->m_suit;
}

char* GetCardName(Card* _card)
{
    char name[32];
    if(!_card)
    {
        return NULL;
    }
    /*name = strcat(strcat(strcpy(name, RankNames[_card->m_rank]), " of "), SuitNames[_card->m_suit]);*/
    strcpy(name, RankNames[_card->m_rank]);
    strcat(name, " of ");
    return strcat(name, SuitNames[_card->m_suit]);
}

int CardCriteria(const Card* _a, const Card* _b)
{
    if(_a->m_suit < _b->m_suit)
    {
        return 1;
    }
    else if(_a->m_suit == _b->m_suit)
    {
        if(_a->m_rank < _b->m_rank)
        {
            return 1;
        }
    }
    return 0;
}

int GetHighestRank(const void* _itemA, const void* _itemB)
{
    if(((Card*)_itemA)->m_rank < ((Card*)_itemB)->m_rank)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
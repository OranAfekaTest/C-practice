#include "Deck.h"

struct Deck
{
    Vector* m_cards;

};

static Status InitDeck(Deck* _deck);

Deck* CreateDeck(void)
{
    Deck* deck = malloc(sizeof(Deck));
    Status status;
    if(!deck)
    {
        return NULL;
    }
    deck->m_cards = VectorCreate(CARDS_IN_DECK, 0);
    status = InitDeck(deck);
    if(status != OK)
    {
        StatusHandler(status, "from InitDeck in CreateDeck"); /* __func__ in c99 */
    }
    status = ShuffleDeck(deck, TIMES_TO_SHUFFLE);
    if(status != OK)
    {
        StatusHandler(status, "from ShuffleDeck in CreateDeck"); /* __func__ in c99 */
    }
    return deck;
}

Status ReturnCardToDeck(Deck* _deck, Card* _card)
{
    if(!_deck || !_card)
    {
        return NOT_INITIALIZED;
    }
    VectorAppend(_deck->m_cards, (void*)_card);
    return OK;
}

void DestroyDeck(Deck** _deck)
{
    if(*_deck)
    {
        VectorDestroy(&((*_deck)->m_cards), DestroyCard);
        free(*_deck);
        *_deck = NULL;
    }
}

Status InitDeck(Deck* _deck)
{
    int suit, rank;
    Card* card;
    for(suit = 0; suit < NUM_OF_SUITS; suit++)
    {
        for(rank = 0; rank < NUM_OF_RANKS; rank++)
        {
            card = CreateCard(suit, rank);
            if(!card)
            {
                return ALLOCATION_FAILED;
            }
            VectorAppend(_deck->m_cards, (void*)card);
        }
    }
    return OK;
}

Status ShuffleDeck(Deck* _deck, int _times)
{
    int i, shuffle, deckSize;
    Card* currentCard = NULL, *swapCard = NULL;
    if(!_deck)
    {
        return NOT_INITIALIZED;
    }
    srand(time(NULL));
    deckSize = VectorSize(_deck->m_cards);
    while(0 <_times--)
    {
        for(i = 0; i < deckSize; i++)
        {
            shuffle = (i + ((rand() + 1) % (CARDS_IN_DECK - 1))) % VectorSize(_deck->m_cards);
            VectorGet(_deck->m_cards, i , (void**)&currentCard);
            VectorGet(_deck->m_cards, shuffle , (void**)&swapCard);
            VectorSet(_deck->m_cards, shuffle , (void*)currentCard);
            VectorSet(_deck->m_cards, i , (void*)swapCard);
        }
    }
    return OK;
}

Status DrawCard(Deck* _deck, Card** _card)
{
    if(!_deck || !_card)
    {
        return NOT_INITIALIZED;
    }
    if(VectorSize(_deck->m_cards) <= 0)
    {
        return EMPTY_DECK;
    }
    VectorRemove(_deck->m_cards, (void**)_card);
    return OK;
}

int PrintDeck(Deck* _deck)
{
    return (int)VectorForEach(_deck->m_cards, PrintCard, NULL);
}


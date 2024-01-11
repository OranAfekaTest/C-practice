#include "Player.h"
#define INITIALIZE_HAND 5
#define NAMESIZE 16

struct Player
{
    Vector* m_hand;
    char m_name[NAMESIZE];
    int m_isHuman;
    int m_score;
};

static size_t partition(Vector* _vec, size_t _start, size_t _end);
static void QuickRec(Vector* _vec, size_t _start, size_t _end);
static void QuickSort(Vector* _vec);
static int CheckforHeartsInHand(void* _card, size_t _index, void* _suit);

Player* CreatePlayer(int _isHuman, char* _name)
{
    Player* player = malloc(sizeof(Player));
    if(!player || !_name)
    {
        return NULL;
    }
    player->m_hand = VectorCreate(INITIALIZE_HAND, INITIALIZE_HAND);
    if(!(player->m_hand))
    {
        free(player);
        return NULL;
    }
    player->m_isHuman = _isHuman;
    player->m_score = 0;
    /*player->m_name = */strcpy(player->m_name, _name);
    return player;
}

void DestroyPlayer(void** _player)
{
    Player** player = (Player**) _player;
    if(*player)
    {
        VectorDestroy(&((*player)->m_hand), DestroyCard);
        free(*player);
        *player = NULL;
    }
}

Status AddCardToHand(Player* _player, Card* _card)
{
    if(!_player || !_card)
    {
        return NOT_INITIALIZED;
    }
    VectorAppend(_player->m_hand, _card);
    return OK;
}

int TakeCardFromDeck(void* _player, size_t _index, void* _deck)
{
    Card* card = NULL;
    Status status;
    status = DrawCard(_deck, &card);
    if(status != OK)
    {
        StatusHandler(status, "failed to DrawCard at TakeCardFromDeck");
        return status;
    }
    VectorAppend(((Player*)_player)->m_hand, (void*)card);
    return 1;
}

int PrintAllHands(void* _player, size_t _index, void* _context)
{
    StatusHandler(PrintHand((Player*)_player), "at PrintHands");
    return 1;
}

Status PrintHand(Player* _player)
{
    if(!_player)
    {
        return NOT_INITIALIZED;
    }
    if(_player->m_isHuman)
    {
        puts("Player's hand");
        VectorForEach(_player->m_hand, PrintCard, NULL);
    }
    return OK;
}

int SortHand(void* _player, size_t _index, void* _context)
{
    QuickSort(((Player*)_player)->m_hand);
    return 1;
}

void QuickSort(Vector* _vec)
{
	size_t start = 0, end;
	end = VectorSize(_vec);
	QuickRec(_vec, start, end - 1);
}

void QuickRec(Vector* _vec, size_t _start, size_t _end)
{
	size_t pivot;
	if(_start < _end)
	{
		pivot = partition(_vec, _start, _end);
		if(0 < pivot)
		{
			QuickRec(_vec, _start, pivot - 1);
		}
		QuickRec(_vec, pivot + 1, _end);
	}
}

size_t partition(Vector* _vec, size_t _start, size_t _end)
{
	size_t smallIndex = _start + 1, i;
    Card* pivot, *itemA, *itemB;
	VectorGet(_vec, _start, (void**)&pivot);
	for(i = _start + 1; i <= _end; i++)
	{
		VectorGet(_vec, i, (void**)&itemA);
		if(CardCriteria(itemA, pivot))
		{
			VectorGet(_vec, smallIndex, (void**)&itemB);
			VectorSet(_vec, smallIndex, itemA);
			VectorSet(_vec, i, itemB);
			smallIndex++;
		}
	}
	VectorGet(_vec, smallIndex - 1, (void**)&itemB);
	VectorSet(_vec, smallIndex - 1, pivot);
	VectorSet(_vec, _start, itemB);

	return smallIndex - 1;
}

Status PlayCard(Player* _player, Card** _toTable, Card* (*_fpStrategy)(Vector* _cards, int* _legalIndexes, size_t _legalIndexesSize, void* _context), int (*_fpRules)(Card* _card, void* _context), void* _tContext)
{
    Card* card = NULL;
    size_t i, legalCardsSize = 0, size = VectorSize(_player->m_hand);
    if(_player->m_isHuman)
    {
        do
        {
            i = ChooseCard();
            HandleVectorResult(VectorGet(_player->m_hand, i, (void**)&card));
        } while (!_fpRules(card, _tContext));
        HandleVectorResult(VectorRemoveByIndex(_player->m_hand, i, (void**)&card));
        *_toTable = card;
    }
    else
    {
        int* legalCards = malloc(sizeof(int) * size);
        if(!size)
        {
            return EMPTY_HAND;
        }

        for(i = 0; i < size; i++)
        {
            HandleVectorResult(VectorGet(_player->m_hand, i, (void**)&card));
            if(!card)
            {
                return NOT_INITIALIZED;
            }
            if(_fpRules(card, _tContext))
            {
                legalCards[legalCardsSize] = i;
                legalCardsSize++;
            }
        }
        *_toTable = _fpStrategy(_player->m_hand, legalCards, legalCardsSize, _tContext);
        if(!_fpRules(*_toTable, _tContext))
        {
            printf("%s chosen by %s is illegal\n", GetCardName(*_toTable), _player->m_name);
        }
        free(legalCards);
    }  
    return OK;
}

int WhoHasTwoOfSpades(void* _player, size_t _index, void* _context)
{
    Card* card = NULL;
    size_t i, size = VectorSize(((Player*)_player)->m_hand);
    for(i = 0; i < size; i++)
    {
        VectorGet(((Player*)_player)->m_hand, i, (void**)&card);
        if(GetCardRank(card) == TWO && GetCardSuit(card) == SPADES)
        {
            return 0;
        }
    }
    return 1;
}

Status AddPoints(Player* _player, int _points)
{
    if(!_player)
    {
        return NOT_INITIALIZED;
    }
    _player->m_score += _points;
    return OK;
}

int PlayerHasSuitInHand(Player* _player, Suit _suit)
{
    Card* card = NULL;
    size_t i, size;
    if(!_player)
    {
        puts("UNINITIALIZED POINTER at PlayerHasSuitInHand");
        return 0;
    }
    if(_suit < 0 || NUM_OF_SUITS <= _suit)
    {
        puts("ILLIGAL SUIT NUMBER at PlayerHasSuitInHand");
        return 0;
    }
    size = VectorSize(_player->m_hand);
    for(i = 0; i < size; i++)
    {
        HandleVectorResult(VectorGet(((Player*)_player)->m_hand, i, (void**)&card));
        if(GetCardSuit(card) == _suit)
        {
            return 1;
        }
    }
    return 0;
}

int PlayerOnlyHasHeartsInHand(Player* _player)
{
    size_t size;
    if(!_player)
    {
        puts("UNINITIALIZED POINTER at PlayerHasSuitInHand");
        return 0;
    }
    size = VectorSize(_player->m_hand);
    if(size == VectorForEach(_player->m_hand, CheckforHeartsInHand, NULL))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int CheckforHeartsInHand(void* _card, size_t _index, void* _suit)
{
    if(!_card)
    {
        puts("UNINITIALIZED POINTER at PlayerHasSuitInHand");
        return 0;
    }
    if(GetCardSuit(_card) != HEARTS)
    {
        return 0;
    }
    return 1;
}

/*
int PlayerHasSuitInHand(void* _card, size_t _index, void* _suit)
{
    if(!_card || !_suit)
    {
        puts("UNINITIALIZED POINTER at PlayerHasSuitInHand");
        return 0;
    }
    if(*_suit < 0 || NUM_OF_SUITS <= *_suit)
    {
        puts("ILLIGAL SIUT NUMBER at PlayerHasSuitInHand");
        return 0;
    }
    if(GetCardSuit((Card*)_card) == *_suit)
    {
        return 0;
    }
    return 1;
}
*/

int	WinComparator(const void* _itemA, const void* _itemB)
{
    if(((Player*)_itemB)->m_score < ((Player*)_itemA)->m_score)
    {
        return 1;
    }
    return 0;
}

int CheckForWinner(void* _player, size_t _index, void* _goalScore)
{
    if(*(int*)_goalScore <= ((Player*)_player)->m_score)
    {
        return 0;
    }
    return 1;
}

char* GetPlayerName(Player* _player)
{
    if(!_player)
    {
        puts("can't get NULL Player's name");
        return NULL;
    }
    return _player->m_name;
}

int GetPlayerScore(Player* _player)
{
    if(!_player)
    {
        puts("can't get NULL Player's score");
        return -1;
    }
    return _player->m_score;
}